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
   output.open("EnvConvGraham.ps");//
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
    for(int i=0;i<n;i++){
      if(envconv[i+1]!=-1){
      output << sommet[envconv[i]][0] << " " << sommet[envconv[i]][1] 
 	    << " moveto"  << endl;
      output << sommet[envconv[i+1]][0] << " " << sommet[envconv[i+1]][1] 
 	    << " lineto"  << endl;
      output << "stroke" << endl;
      output << endl;
    }
    }
    output.close();
}


//Renvoie Vrai si p2 est strictement a droite de la droite oriente p_0p_1
bool AnglePolaireInferieur(int p0[2], int p1[2], int p2[2]){
  
  return (((p1[0]-p0[0])*(p2[1]-p0[1])-(p2[0]-p0[0])*(p1[1]-p0[1])) < 0);
}



void TriRapidePolaire(int min, int n, int sommet[][2], int t, int TriPolaire[]){
  // En entree, les parametres sont min: l'indice du sommet autour duquel les autres sont tries par
  // ordre polaire croissant, n: le nombre de sommet, TriPolaire le tableau contenant la liste des
  // indices des sommets a trier, donc au debut, tous sauf min, et enfin t: la taille de TriPolaire
  // donc, a l'appel initial, t vaut n-1.
  // L'algo modifie TriPolaire et le retourne trie par angle polaire croissant par rapport au sommet 
  // d'indice min.
  if(t>1){
    int pivot=TriPolaire[0]; //indice du sommet pivot
    int d=0; // nombre de sommets a droite de min_pivot
    for(int i=1;i<t;i++){//On compte (on ne tient pas compte de pivot)
      if(AnglePolaireInferieur(sommet[min],sommet[pivot],sommet[TriPolaire[i]])){d++;}
    }
    int Tg[t-d-1];
    int Td[d];
    int indice_gauche=0; //indice d'insertion dans Tg
    int indice_droit=0; //indice d'insertion dans Td

    for(int i=1;i<t;i++){ //Remplissage de Tg et Td (on ne tient pas compte de pivot)
      if(AnglePolaireInferieur(sommet[min],sommet[pivot],sommet[TriPolaire[i]])){//A droite
      Td[indice_droit]=TriPolaire[i];
      indice_droit++;}
      else{//A gauche
      Tg[indice_gauche]=TriPolaire[i];
      indice_gauche++;}}

    //On trie Td et Tg
    if(d>0){TriRapidePolaire(min,n,sommet,d,Td);}
    if(t-d-1>0){TriRapidePolaire(min,n,sommet,t-d-1,Tg);}
    //Fusion dans TriPolaire
    for(int i=0;i<t;i++){
      if(i<d){TriPolaire[i]=Td[i];}
      if(i==d){TriPolaire[i]=pivot;}
      if(i>d){TriPolaire[i]=Tg[i-d-1];}
    }
  }
}



void PointAuHasard(int n,int sommet[][2]){
  srand(time(NULL));
  for(int i=0;i<n;i++) {
	int r = rand();
	int ray = rand()%250;
    sommet[i][0] = 300+ray*cos(r);
    sommet[i][1] = 400+ray*sin(r);
  }
}

void Graham(int n, int sommet[][2],int envconv[]){
  int pmin = 0;
  for(int i=1;i<n;i++) {
    if(sommet[pmin][1] > sommet[i][1]) {
      pmin = i;
    }
  }
  
  int Tri[n-1], i=0, j=0;
  while(i<n) {
    if(j == pmin) {
      j++;
    }
    else {
      Tri[i] = j;
      i++; j++;
    }
  }
  
  TriRapidePolaire(pmin, n, sommet, n-1, Tri);
  
  int indice = 0; envconv[indice] = pmin; 
  indice++; envconv[indice] = Tri[0];
  indice++; envconv[indice] = Tri[1];
  
  for(i=2;i<n-1;i++) {
    while(AnglePolaireInferieur(sommet[envconv[indice-1]],sommet[envconv[indice]],sommet[Tri[i]])) {
      envconv[indice] = -1; indice--;
    }
    indice++; envconv[indice] = Tri[i];
  }
  
  indice++; envconv[indice] = pmin;
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
  Graham(n,sommet,envconv);
  AffichageEnvConv(n,sommet,envconv);
}
