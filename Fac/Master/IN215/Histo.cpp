#include "ImageBase.h"
#include <iostream>
#include <fstream>
#include <math.h>

int fRound(double d){   
  if (d<0){ if (d-ceil(d) > -0.5) return ceil(d); else return floor(d); }
  else{ if (d-floor(d)< 0.5) return floor(d); else return ceil(d); }
}

//Spectre
#define TAILLE 256

//Seuils
#define sR1 70
#define sR2 215
#define sG1 0
#define sG2 230
#define sB1 0
#define sB2 130

//Debug
#define DEBUG false

using namespace std;

ImageBase imIn;

void init(int* histo, int size);
void Histogramme(int* histo, int size, char* datname);
void Expansion(int* histo, int size, int min, int max, char* outname, char* datname);
void Seuillage(int* histo, int size, char* outname, char* datname);
double* Egalisation(int* histo, int size, int min, int max, char* outname, char* datname);
void Specification(int* histo, int size, int min, int max, double* R, char* outname1, char* datname1, char* outname2, char* datname2);

int main (int argc, char** argv) {
  
  if(argc < 1) {
    printf("Usage : \n");
    return 1;
  }
  
  cout<<"============="<<endl<<"| black.pgm |"<<endl<<"============="<<endl;
  imIn.load("in/black.pgm");
  
  int histo[TAILLE] = {0};
  Histogramme(histo, TAILLE, "his/blackBase.dat");
  Expansion(histo, TAILLE, 0, TAILLE-1, "out/blackExpansion.pgm", "his/blackExpansion.dat");
  
  
  cout<<endl<<endl<<"============="<<endl<<"| black.ppm |"<<endl<<"============="<<endl;
  imIn.load("in/black.ppm");
  
  int histoRGB[3*TAILLE] = {0};
  Histogramme(histoRGB, 3*TAILLE, "his/blackBaseRGB.dat");
  Expansion(histoRGB, 3*TAILLE, 0, TAILLE-1, "out/blackExpansion.ppm", "his/blackExpansionRGB.dat");
  
  
  cout<<endl<<endl<<"==============="<<endl<<"| peppers.ppm |"<<endl<<"==============="<<endl;
  imIn.load("in/peppers.ppm");
  
  init(histoRGB, 3*TAILLE);
  Histogramme(histoRGB, 3*TAILLE, "his/peppersBaseRGB.dat");
  Seuillage(histoRGB, 3*TAILLE, "out/peppersSeuillage.ppm", "his/peppersSeuillageRGB.dat");
  Expansion(histoRGB, 3*TAILLE, 0, TAILLE-1, "out/peppersExpansion.ppm", "his/peppersExpansionRGB.dat");
  
  
  cout<<endl<<endl<<"==============="<<endl<<"| tiffany.pgm |"<<endl<<"==============="<<endl;
  imIn.load("in/tiffany.pgm");
  
  init(histo, TAILLE);
  Histogramme(histo, TAILLE, "his/tiffanyBase.dat");
  Egalisation(histo, TAILLE, 0, TAILLE-1, "out/tiffanyEgalisation.pgm", "his/tiffanyEgalisation.dat");
  
  
  cout<<endl<<endl<<"=========="<<endl<<"| 13.pgm |"<<endl<<"=========="<<endl;

  //Reference
  imIn.load("in/lena.pgm");
  double* R = Egalisation(histo, TAILLE, 0, TAILLE-1, NULL, NULL);

  init(histo, TAILLE);
  Histogramme(histo, TAILLE, "his/lena.dat");
    
  imIn.load("in/tiffany.pgm");
  
  init(histo, TAILLE);
  Histogramme(histo, TAILLE, "his/13Base.dat");
  Specification(histo, TAILLE, 0, TAILLE-1, R, "out/13Egalisation.pgm", "his/13Egalisation.dat", "out/13Specification.pgm", "his/13Specification.dat");
  
  return 0;
}


void init(int* histo, int size) {
  for(int i=0;i<size;i++)
    histo[i] = 0;
}

void Histogramme(int* histo, int size, char* datname) {
  
  cout<<endl<<"Histogramme"<<endl;
  
  if(!imIn.getColor()) {
    
    //Image en niveaux de gris
    
    if(size < TAILLE) {
      cout<<"Erreur : histo doit être de size "<<TAILLE<<" en .pgm - Histogramme"<<endl;
      exit(EXIT_FAILURE);
    }
    
    for(int x=0;x<imIn.getWidth();x++)
      for(int y=0; y<imIn.getHeight();y++)
	histo[(int)imIn[y][x]]++;
      
      ofstream his(datname);
    for(int i=0;i<TAILLE;i++) {
      if(DEBUG)
	cout<<"\t"<<i<<" : "<<histo[i]<<endl;
      his<<histo[i]<<endl;
    }
    his.close();
    
  }
  else {
    
    //Image en couleurs RGB
    
    if(size < TAILLE*3) {
      cout<<"Erreur : histo doit être de size "<<TAILLE<<"*3 en .ppm - Histogramme"<<endl;
      exit(EXIT_FAILURE);
    }
    
    for(int x=0;x<imIn.getWidth();x+=3) {
      for(int y=0; y<imIn.getHeight();y++) {
	histo[3*((int)imIn[y*3][x*3])]++;
	histo[3*((int)imIn[y*3][x*3+1])+1]++;
	histo[3*((int)imIn[y*3][x*3+2])+2]++;
      }
    }
    
    ofstream his(datname);
    for(int i=0;i<TAILLE;i++)
      his<<i<<" "<<histo[3*i]<<" "<<histo[3*i+1]<<" "<<histo[3*i+2]<<endl;
    his.close();
    
  }
  
}

void Expansion(int* histo, int size, int min, int max, char* outname, char* datname) {
  
  cout<<endl<<"Expansion dynamique"<<endl;
  
  if(!imIn.getColor()) {
    
    //Image en niveaux de gris
    
    if(size < TAILLE) {
      cout<<"Erreur : histo doit être de size "<<TAILLE<<" en .pgm - Expansion"<<endl;
      exit(EXIT_FAILURE);
    }
    
    int a0=0,a1=TAILLE-1;
    
    int ind = 0;
    while(ind < TAILLE && histo[ind] == 0) 
      ind++;
    a0 = ind; 
    
    ind = TAILLE-1;
    while(ind >= 0 && histo[ind] == 0) 
      ind--;
    a1 = ind;
    
    double alpha = (min*a1-max*a0)/(a1-a0), beta = (double)(max-min)/(double)(a1-a0);
    cout<<"  Gris : a0 = "<<a0<<", a1 = "<<a1<<", alpha = "<<alpha<<", beta = "<<beta<<endl;
    
    init(histo,TAILLE);
    
    for(int x=0;x<imIn.getWidth();x++) {
      for(int y=0; y<imIn.getHeight();y++) {
	imIn[y][x] = (char)alpha+beta*imIn[y][x];
      }
    }
    
    if(outname != NULL) imIn.save(outname);
    if(datname != NULL) Histogramme(histo, TAILLE, datname);
    
  }
  else{
    
    //Image en couleurs RGB
    
    if(size < TAILLE*3) {
      cout<<"Erreur : histo doit être de size "<<TAILLE<<"*3 en .ppm - Expansion"<<endl;
      exit(EXIT_FAILURE);
    }
    
    //ROUGE
    int a0=0,a1=TAILLE-1;
    
    int ind=0;
    while(ind < TAILLE && histo[3*ind] == 0) 
      ind++;
    a0 = ind; 
    
    ind = TAILLE-1;
    while(ind >= 0 && histo[3*ind] == 0) 
      ind--;
    a1 = ind;
    
    double alphaR = (min*a1-max*a0)/(a1-a0), betaR = (double)(max-min)/(double)(a1-a0);
    cout<<"  Rouge : a0 = "<<a0<<", a1 = "<<a1<<", alphaR = "<<alphaR<<", betaR = "<<betaR<<endl;
    
    //VERT
    a0=0,a1=TAILLE-1;
    
    ind=0;
    while(ind < TAILLE && histo[3*ind+1] == 0) 
      ind++;
    a0 = ind; 
    
    ind = TAILLE-1;
    while(ind >= 0 && histo[3*ind+1] == 0) 
      ind--;
    a1 = ind;
    
    double alphaG = (min*a1-max*a0)/(a1-a0), betaG = (double)(max-min)/(double)(a1-a0);
    cout<<"  Vert : a0 = "<<a0<<", a1 = "<<a1<<", alphaG = "<<alphaG<<", betaG = "<<betaG<<endl;
    
    //BLEU
    a0=0,a1=TAILLE-1;
    
    ind=0;
    while(ind < TAILLE && histo[3*ind+2] == 0) 
      ind++;
    a0 = ind; 
    
    ind = TAILLE-1;
    while(ind >= 0 && histo[3*ind+2] == 0) 
      ind--;
    a1 = ind;
    
    double alphaB = (min*a1-max*a0)/(a1-a0), betaB = (double)(max-min)/(double)(a1-a0);
    cout<<"  Bleu : a0 = "<<a0<<", a1 = "<<a1<<", alphaB = "<<alphaB<<", betaB = "<<betaB<<endl;
    
    //Histogramme
    init(histo, TAILLE*3);
    
    for(int x=0;x<imIn.getWidth();x++) {
      for(int y=0; y<imIn.getHeight();y++) {
	//R
	imIn[3*y][3*x] = (char)(alphaR+betaR*imIn[3*y][3*x]);
	//G
	imIn[3*y][3*x+1] = (char)(alphaG+betaG*imIn[3*y][3*x+1]);
	//B
	imIn[3*y][3*x+2] = (char)(alphaB+betaB*imIn[3*y][3*x+2]);
      }
    }
    
    if(outname != NULL) imIn.save(outname);
    if(datname != NULL) Histogramme(histo, TAILLE*3, datname);
    
  }
}

void Seuillage(int* histo, int size, char* outname, char* datname) {
  
  cout<<endl<<"Seuillage"<<endl;
  
  if(!imIn.getColor()) {
    
    //Image en niveaux de gris
    
    if(size < TAILLE) {
      cout<<"Erreur : histo doit être de size "<<TAILLE<<" en .pgm - Seuillage"<<endl;
      exit(EXIT_FAILURE);
    }
    
    cout<<"Non implémenté en .pgm"<<endl;
    
  }
  else{
    
    //Image en couleurs RGB
    
    if(size < TAILLE*3) {
      cout<<"Erreur : histo doit être de size "<<TAILLE<<"*3 en .ppm - Seuillage"<<endl;
      exit(EXIT_FAILURE);
    }
    
  }
  
  //Histogramme
  init(histo, 3*TAILLE);
  
  for(int x=0;x<imIn.getWidth();x++) {
    for(int y=0; y<imIn.getHeight();y++) {
      //R
      if(imIn[3*y][3*x]<sR1) imIn[3*y][3*x]=sR1;
      if(imIn[3*y][3*x]>sR2) imIn[3*y][3*x]=sR2;
      //G
      if(imIn[3*y][3*x+1]<sG1) imIn[3*y][3*x+1]=sG1;
      if(imIn[3*y][3*x+1]>sG2) imIn[3*y][3*x+1]=sG2;
      //B
      if(imIn[3*y][3*x+2]<sB1) imIn[3*y][3*x+2]=sB1;
      if(imIn[3*y][3*x+2]>sB2) imIn[3*y][3*x+2]=sB2;
    }
  }
  
  if(outname != NULL) imIn.save(outname);
  if(datname != NULL) Histogramme(histo, TAILLE*3, datname);
  
}

double* Egalisation(int* histo, int size, int min, int max, char* outname, char* datname) {
  
  cout<<endl<<"Egalisation"<<endl;
  
  if(!imIn.getColor()) {
    
    //Image en niveaux de gris
    
    if(size < TAILLE) {
      cout<<"Erreur : histo doit être de size "<<TAILLE<<" en .pgm - Egalisation"<<endl;
      exit(EXIT_FAILURE);
    }
    
    int N = imIn.getTotalSize();
    
    double ddp[TAILLE];
    for(int i=0;i<TAILLE;i++)
      ddp[i] = (double)histo[i]/N;
    
    ofstream Os1("his/ddp.dat");
    for(int i=0;i<TAILLE;i++) {
      if(DEBUG)
	cout<<"\t"<<i<<" : "<<ddp[i]<<endl;
      Os1<<ddp[i]<<endl;
    }
    Os1.close();
    
    double F[TAILLE] = {0};
    F[0] = ddp[0];
    for(int i=1;i<TAILLE;i++)
      F[i] = F[i-1]+ddp[i];
    
    ofstream Os2("his/courbe de F(a).dat");
    for(int i=0;i<TAILLE;i++) {
      if(DEBUG)
	cout<<"\t"<<i<<" : "<<F[i]<<endl;
      Os2<<F[i]<<endl;
    }
    Os2.close();
    
    double T[TAILLE] = {0};
    for(int i=0;i<TAILLE;i++)
      T[i] = (max-min)*F[i]+min;
    
    //Histogramme
    init(histo, TAILLE);
    
    for(int x=0;x<imIn.getWidth();x++) {
      for(int y=0; y<imIn.getHeight();y++) {
	imIn[y][x] = (char)T[imIn[y][x]];
      }
    }
    
    if(outname != NULL) imIn.save(outname);
    if(datname != NULL) Histogramme(histo, TAILLE*3, datname);
    
    return T;
    
  }
  else{
    
    //Image en couleurs RGB
    
    if(size < TAILLE*3) {
      cout<<"Erreur : histo doit être de size "<<TAILLE<<"*3 en .ppm - Egalisation"<<endl;
      exit(EXIT_FAILURE);
    }
    
    cout<<"Non implémenté en .ppm"<<endl;
    return NULL;
  }
  
}

void Specification(int* histo, int size, int min, int max, double* R, char* outname1, char* datname1, char* outname2, char* datname2) {
  
  cout<<endl<<"Specification"<<endl;
  
  if(!imIn.getColor()) {
    
    //Image en niveaux de gris
    
    if(size < TAILLE) {
      cout<<"Erreur : histo doit être de size "<<TAILLE<<" en .pgm - Specification"<<endl;
      exit(EXIT_FAILURE);
    }
    
    Egalisation(histo, TAILLE, 0, TAILLE-1, outname1, datname1);
    
    init(histo, TAILLE);
    
    for(int x=0;x<imIn.getWidth();x++)
      for(int y=0; y<imIn.getHeight();y++)
	for(int i=0;i<TAILLE;i++)
	  if(imIn[y][x] == (char)fRound(R[i]))
	    imIn[y][x] = i;
    
    if(outname2 != NULL) imIn.save(outname2);
    if(datname2 != NULL) Histogramme(histo, TAILLE*3, datname2);
    
  }
  else{
    
    //Image en couleurs RGB
    
    if(size < TAILLE*3) {
      cout<<"Erreur : histo doit être de size "<<TAILLE<<"*3 en .ppm - Specification"<<endl;
      exit(EXIT_FAILURE);
    }
    
    cout<<"Non implémenté en .ppm"<<endl;
    
  }
  
}
