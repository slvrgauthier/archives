#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h> // pour cos() et sin()
#define PI 3.14159265

using namespace std;

int const n=20;

void AffichagePoints(int n, int sommet[][2]){
  //Affichage de n points dont les coordonnees sont donnees dans sommet[n][2]
  //Un fichier Points.ps est cree, visualisable avec un afficheur postscript (ex: ggv, kghostview...)
   ofstream output;
   output.open("Points.ps");//
   output << "%!PS-Adobe-3.0" << endl;
   output << endl;  
   for(int i=0;i<n;i++){
     output << sommet[i][0] << " " << sommet[i][1] << " 2 0 360 arc" <<endl;
     output << "0 setgray" <<endl;
     output << "fill" <<endl;
     output << sommet[i][0]+2 << " " << sommet[i][1] << " moveto" <<endl;
     output << "/Courier findfont 15 scalefont setfont" << endl;
     output << "("<< i << ")" << " show" << endl;
     output << "stroke" << endl;
     output << endl;
   }
   output << endl;
   output.close();
}

void AffichageEnvConv(int n, int sommet[][2], int envconv[]){
  //Affichage de n points dont les coordonnees sont donnees dans sommet[n][2] et de leur
  //enveloppe convexe donnee sous forme de liste cyclique: un tableau de taille n+1 listant les
  //indices des sommets de l'enveloppe convexe. Le premier sommet est repete en fin de liste et le
  //tableau est complete par la valeur -1.
  //Un fichier EnvConv.ps est cree
   ofstream output;
   output.open("EnvConvJarvis.ps");//
   output << "%!PS-Adobe-3.0" << endl;
   output << endl;  
   for(int i=0;i<n;i++){
     output << sommet[i][0] << " " << sommet[i][1] << " 2 0 360 arc" <<endl;
     output << "0 setgray" <<endl;
     output << "fill" <<endl;
     output << sommet[i][0]+2 << " " << sommet[i][1] << " moveto" <<endl;
     output << "/Courier findfont 15 scalefont setfont" << endl;
     output << "("<< i << ")" << " show" << endl;
     output << "stroke" << endl;
     output << endl;
   }
   output << endl;
   int i=0;
   while(envconv[i+1]!=-1){
      output << sommet[envconv[i]][0] << " " << sommet[envconv[i]][1] 
 	    << " moveto"  << endl;
      output << sommet[envconv[i+1]][0] << " " << sommet[envconv[i+1]][1] 
 	    << " lineto"  << endl;
      output << "stroke" << endl;
      output << endl;
      i++;
   }
    output.close();
}


//Generation au hasard de l'ensemble des points consideres
void PointAuHasard(int n,int sommet[][2]){
  srand(time(NULL));
  for(int i=0;i<n;i++) {
    sommet[i][0] = 300+250*cos(rand());
    sommet[i][1] = 400+250*sin(rand());
  }
}

//Renvoie Vrai si p2 est strictement a droite de la droite p_0p_1
bool AnglePolaireInferieur(int p0[2], int p1[2], int p2[2]){
  
  return (((p1[0]-p0[0])*(p2[1]-p0[1])-(p2[0]-p0[0])*(p1[1]-p0[1])) < 0);
}

//Parcours de Jarvis
void Jarvis(int n, int sommet[][2],int envconv[]){
  int pmin = 0;
  for(int i=1;i<n;i++) {
    if(sommet[pmin][1] > sommet[i][1]) {
      pmin = i;
    }
  }
  
  int pcourant = pmin;
  envconv[0] = pmin;
  //indice courant d'ajout à la liste
  int indice = 1;
  
  do {
    int p, i=0;
    //erreur ssi tous les points sont confondus
    while(sommet[i][0] == sommet[pcourant][0] && sommet[i][1] == sommet[pcourant][1]) {
      i++;
    }
    p = i;
    
    for(i=0;i<n;i++) {
      if(AnglePolaireInferieur(sommet[pcourant],sommet[p],sommet[i])) {
	p = i;
      }
    }
    
    envconv[indice] = p;
    indice++;
    
    pcourant = p;
    
  }while(pcourant != pmin);
}

int main(){
  int sommet[n][2];
  int envconv[n+1];
  for(int i=0;i<n+1;i++){envconv[i]=-1;}
  PointAuHasard(n,sommet);

sommet[0][0]=123;
sommet[0][1]=523;
sommet[1][0]=259;
sommet[1][1]=476;
sommet[2][0]=411;
sommet[2][1]=280;
sommet[3][0]=60;
sommet[3][1]=400;
sommet[4][0]=187;
sommet[4][1]=544;
sommet[5][0]=447;
sommet[5][1]=381;
sommet[6][0]=296;
sommet[6][1]=194;
sommet[7][0]=273;
sommet[7][1]=614;
sommet[8][0]=130;
sommet[8][1]=250;
sommet[9][0]=212;
sommet[9][1]=587;
sommet[10][0]=500;
sommet[10][1]=400;
sommet[11][0]=280;
sommet[11][1]=170;
sommet[12][0]=280;
sommet[12][1]=630;
sommet[13][0]=311;
sommet[13][1]=233;
sommet[14][0]=345;
sommet[14][1]=512;
sommet[15][0]=130;
sommet[15][1]=550;
sommet[16][0]=430;
sommet[16][1]=250;
sommet[17][0]=211;
sommet[17][1]=317;
sommet[18][0]=430;
sommet[18][1]=550;
sommet[19][0]=431;
sommet[19][1]=450;
  AffichagePoints(n,sommet);
  Jarvis(n,sommet,envconv);
  AffichageEnvConv(n,sommet,envconv);
}
