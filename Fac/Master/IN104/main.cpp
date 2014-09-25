#include <cstdlib>
#include <iostream>

using namespace std;
#include "Wave.hpp"
#include <math.h>
#include "string.h"

#define Pi2 2*M_PI
#define COEF (fe/7) // coef pour avoir de belles notes

// actions à activer/désactiver
#define ENABLE_TESTS 0
#define ENABLE_DFT 1
#define ENABLE_DECALAGE_DFT 0
#define ENABLE_AFFICHE_DFT 0
#define ENABLE_GAMME 0 //Gamme et filtrages fréquentiels
#define ENABLE_ACCORDS 0

// fréquences des différentes notes :
#define LA 440.0
#define SI 494.0
#define DO 523.0
#define RE 587.0
#define MI 659.0
#define FA 698.5
#define SOL 784.0

char fileName[200]; // Fichier wave

void DFT(double *signal, double *partie_reelle, double *partie_imaginaire, int N);
void IDFT(double *signal, double *partie_reelle, double *partie_imaginaire, int N);

//==============================================================================
void printUsage(char* name) {

  cout << "\nUsage : "
       <<name
       <<" fichier.wav\n";
  exit(-1);
}

//==============================================================================
void processOptionsInLine(int argc, char** argv){  
  if (argc > 1) {
    //RECOPIE DU NOM DE L'IMAGE DANS LA VARIABLE seqName
    strcpy(fileName, argv[1]);  
  }
}

int main(int argc, char *argv[]) {

  processOptionsInLine(argc, argv);

  if(strcmp("La.wav", fileName) == 0) {
    cout<<endl<<"Création de la tonalité :"<<endl;
    int fe = 44100;
    int s = 6; // 6 secondes
    long int N = fe*s; 
    unsigned char data8[N];

    for(int i=0;i<N;i++) {
      data8[i] = (unsigned char)((sin(LA*i/COEF)+1)*127.0); 
    }

    Wave* fichier = new Wave(data8, N, (short)1, fe);
    fichier->write(fileName);
    cout<<endl;
  }

//Création du La avec DFT - IDFT -----------------------------------------------
  if(ENABLE_DFT == 1) {
    int fe = 10000;
    int s = 1;
    int N = fe*s;
    unsigned char data[N];

    double signal[N]; double reelle[N]; double imaginaire[N];
 
    cout<<endl<<"La initial :"<<endl;
    for(int i=0;i<N;i++) {
        signal[i] = (double)((sin(LA*i/COEF)+1)*127.0);
        data[i] = (unsigned char)signal[i];
    }
    if(ENABLE_AFFICHE_DFT == 1) {
      cout<<"signal | reelle | imaginaire"<<endl;
      for(int k=0;k<N;k++) {
        cout<<"  "<<signal[k]<<" | "<<reelle[k]<<" | "<<imaginaire[k]<<endl;
      }
    }
    Wave* fichier = new Wave(data, N, (short)1, fe);
    fichier->write(strcpy(fileName,"La initial"));

    cout<<endl;
    DFT(signal,reelle,imaginaire,N);
      for(int j = (LA-100)*fe/N;j<(LA+100)*fe/N;j++) {
        reelle[j] = imaginaire[j] = reelle[(N-j)%N] = imaginaire[(N-j)%N] = signal[j] = signal[(N-j)%N] = 0.0;
      }
    for(int i=0;i<N;i++) {
        data[i] = (unsigned char)(signal[i]/N); //on divise par N pour l'affichage dans audacity (wav)
	//cout<<i<<" : "<<signal[i]<<endl;
    }
    if(ENABLE_AFFICHE_DFT == 1) {
      cout<<"signal | reelle | imaginaire"<<endl;
      for(int k=0;k<N;k++) {
        cout<<"  "<<signal[k]<<" | "<<reelle[k]<<" | "<<imaginaire[k]<<endl;
      }
    }
  
    fichier = new Wave(data, N, (short)1, fe);
    fichier->write(strcpy(fileName,"La DFT"));
  
    cout<<endl;
    IDFT(signal,reelle,imaginaire,N);
    for(int i=0;i<N;i++) {
        data[i] = (unsigned char)signal[i];
    }
    if(ENABLE_AFFICHE_DFT == 1) {
      cout<<"signal | reelle | imaginaire"<<endl;
      for(int k=0;k<N;k++) {
        cout<<"  "<<signal[k]<<" | "<<reelle[k]<<" | "<<imaginaire[k]<<endl;
      }
    }
  
    fichier = new Wave(data, N, (short)1, fe);
    fichier->write(strcpy(fileName,"La IDFT"));
    cout<<endl;
  }
  
//Création de la gamme de La -----------------------------------------------
  if(ENABLE_GAMME == 1) {
    cout<<endl<<"Création de la gamme de La :"<<endl;
    int fe = 7000;
    double s = 1; // 0.5 seconde pour chaque note
    int N = (int)fe * s; 
    unsigned char data[N];
    for(int note=0;note<7;note++) {
      for(int i=0;i<N/7;i++) { //N/7 : taille de chaque note
        switch(note) { //note*N/7 : position dans le tableau
          case 0 :
            data[note*N/7+i] = (unsigned char)((sin(LA*i/COEF)+1)*127.0);
            break;
          case 1 :
            data[note*N/7+i] = (unsigned char)((sin(SI*i/COEF)+1)*127.0);
            break;
          case 2 :
            data[note*N/7+i] = (unsigned char)((sin(DO*i/COEF)+1)*127.0);
            break;
          case 3 :
            data[note*N/7+i] = (unsigned char)((sin(RE*i/COEF)+1)*127.0);
            break;
          case 4 :
            data[note*N/7+i] = (unsigned char)((sin(MI*i/COEF)+1)*127.0);
            break;
          case 5 :
            data[note*N/7+i] = (unsigned char)((sin(FA*i/COEF)+1)*127.0);
            break;
          case 6 :
            data[note*N/7+i] = (unsigned char)((sin(SOL*i/COEF)+1)*127.0);
            break;
        }
      }
    }
    
    Wave* fichier = new Wave(data, N, (short)1, fe);
    fichier->write(strcpy(fileName,"Gamme La"));
    cout<<endl;

//Filtrages fréquentiels --------------------------------------------------- //a bidouiller http://www.developpez.net/forums/d688102/autres-langages/algorithmes/contribuez/java-filtrage-passe-bas-d-signal-1d/
    unsigned char tmpData[N];
    double signal[N/7]; double reelle[N/7]; double imaginaire[N/7];
    for(int w=0;w<7;w++) {
      for(int i=0;i<N/7;i++) {
        signal[i] = (double)data[w*(N/7)+i]/127-1; //obtenir une sinusoide parfaite entre -1 et 1
      }
      DFT(signal,reelle,imaginaire,N/7);
      for(int j = (LA-50)*fe/N;j<(LA+50)*fe/N;j++) {
        reelle[j] = imaginaire[j] = reelle[(N-j)%N] = imaginaire[(N-j)%N] = 0.0;
      }
      IDFT(signal,reelle,imaginaire,N/7);
      for(int i=0;i<N/7;i++) {
        tmpData[w*(N/7)+i] = (unsigned char)((signal[i]+1)*127);
      }
    }
    fichier = new Wave(tmpData, N, (short)1, fe);
    fichier->write(strcpy(fileName,"Gamme La sans La"));
    cout<<endl;
    
  }

//Butterworth

//Création des accords de Do -----------------------------------------------
  if(ENABLE_ACCORDS == 1) {
    cout<<endl<<"Création des Do majeur et mineur :"<<endl;
    int fe = 44100;
    int s = 2; // 2 secondes (1 pour chaque accord)
    int N = fe * s; 
    unsigned char data[N];
    for(int accord=0;accord<2;accord++) {
      for(int i=0;i<N/2;i++) { //N/2 : taille de chaque note
        switch(accord) {       //note*N/2 : position dans le tableau
          case 0 :
            data[accord*N/2+i] = (unsigned char)((sin((DO+MI+SOL)/3*i/COEF)+1)*127.0); 
            break; //ajout des fréquences pour accord, /3 pour un son plus grave
          case 1 :
            data[accord*N/2+i] = (unsigned char)((sin((LA+DO+MI)/3*i/COEF)+1)*127.0);
            break;
        }
      }
    }
    
    Wave* fichier = new Wave(data, N, (short)1, fe);
    fichier->write(strcpy(fileName,"Accords"));
    cout<<endl;
  }

//Tests DFT - IDFT -----------------------------------------------
  if(ENABLE_TESTS == 1) {
    int N = 44100, fe = N;
    unsigned char data[N];

    double signal[N]; double reelle[N]; double imaginaire[N];
    cout<<endl<<"Tests :"<<endl;
    for(int i=0;i<N;i++) {
        data[i] = (unsigned char)((cos(i)+1)*127.0);
        signal[i] = (double)cos(i);
        cout<<signal[i]<<" ; "<<reelle[i]<<" ; "<<imaginaire[i]<<" ; "<<(int)data[i]<<endl; 
    }
    Wave* fichier = new Wave(data, N, (short)1, fe);
    fichier->write(strcpy(fileName,"Test initial"));
    cout<<endl;
  
    DFT(signal,reelle,imaginaire,N);
    for(int i=0;i<N;i++) {
        data[i] = (unsigned char)(signal[i]+1)*127;
        cout<<signal[i]<<" ; "<<reelle[i]<<" ; "<<imaginaire[i]<<" ; "<<(int)data[i]<<endl; 
    }
    fichier = new Wave(data, N, (short)1, N);
    fichier->write(strcpy(fileName,"Test DFT"));
    cout<<endl;
  
    IDFT(signal,reelle,imaginaire,N);
    for(int i=0;i<N;i++) {
        data[i] = (unsigned char)(signal[i]+1)*127;
        cout<<signal[i]<<" ; "<<reelle[i]<<" ; "<<imaginaire[i]<<" ; "<<(int)data[i]<<endl; 
    }
    fichier = new Wave(data, N, (short)1, N);
    fichier->write(strcpy(fileName,"Test IDFT"));
    cout<<endl;
  }
}

void DFT(double *signal, double *partie_reelle, double *partie_imaginaire, int N) {
  int percent = 0;
  //cout<<"DFT en cours :\t"<<percent<<"%"<<flush;
  
  double a, b;
  for(int k=0;k<N;k++) {
    a = 0.0;
    b = 0.0;
    for(int n=0;n<N;n++) {
      a += signal[n] * cos(Pi2*k*n/N);
      b += signal[n] * sin(Pi2*k*n/N);
    }
    partie_reelle[k] = a;
    partie_imaginaire[k] = -b;
    
    //affichage
    if(100*k/N >= percent+1) {
      percent = (int)100*k/N;
      cout<<"\r"<<"DFT en cours :\t"<<percent<<"%"<<flush;
    }
  }
  for(int k=0;k<N;k++) {
    if(ENABLE_DECALAGE_DFT == 1) {
      signal[(k+N/2)%N] = partie_reelle[k] + partie_imaginaire[k];
    }
    else {
      signal[k] = partie_reelle[k] + partie_imaginaire[k];
    }
  }
  cout<<"\r"<<"DFT terminée :\t100%"<<endl;
}

void IDFT(double *signal, double *partie_reelle, double *partie_imaginaire, int N) {
  int percent = 0;
  double tmpR[N], tmpI[N];
  cout<<"IDFT en cours :\t"<<percent<<"%"<<flush;
  
  double x, y;
  for(int n=0;n<N;n++) {
    x = 0.0;
    y = 0.0;
    for(int k=0;k<N;k++) {
      x += partie_reelle[k]*cos(Pi2*k*n/N) - partie_imaginaire[k]*sin(Pi2*k*n/N);
      y += partie_reelle[k]*sin(Pi2*k*n/N) + partie_imaginaire[k]*cos(Pi2*k*n/N);
    }
    tmpR[n] = x/N;
    tmpI[n] = y/N;
    
    //affichage
    if(100*n/N >= percent+1) {
      percent = (int)100*n/N;
      cout<<"\r"<<"IDFT en cours :\t"<<percent<<"%"<<flush;
    }
  }
  for(int k=0;k<N;k++) {
    partie_reelle[k] = tmpR[k];
    partie_imaginaire[k] = tmpI[k];
    signal[k] = partie_reelle[k] + partie_imaginaire[k];
  }
  cout<<"\r"<<"IDFT terminée :\t100%"<<endl;
}


