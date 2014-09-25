#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "ARN.h"

using namespace std;

int const n=10;


typedef struct {
  int  abscisse;
  int  ordonnee;
} point;


//Le tableau des segments: segments[2*i] et segments[2*i+1] sont les 
// extremites du segments i

point segments[2*n];

//********************************************//

bool ClesEgales(int cle1, int cle2){
  if(cle1==cle2){
    return true;
  }
  else{
    return false;}
}

//********************************************//
//Renvoie vrai ssi le premier point du segment cle2
//est a gauche du segment cle1 (segment cle1 < segment cle2)

bool CleInferieure(int cle1, int cle2){

  //conversion en long long pour eviter un depacement d'int.

  //Segment p1p2
  long long x1=(long long) segments[2*cle1].abscisse;
  long long y1=(long long) segments[2*cle1].ordonnee;
  long long x2=(long long) segments[2*cle1+1].abscisse;
  long long y2=(long long) segments[2*cle1+1].ordonnee;

  //Point p3 du segment p3p4
  long long x3=(long long) segments[2*cle2].abscisse;
  long long y3=(long long) segments[2*cle2].ordonnee;

  return (((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1)) > 0);

}


//********************************************//

void AffichageSegments(int n, point segments[]){
  //Affichage de n segments dont les coordonnees sont donnees dans segments[n]
  //Un fichier Segments.ps est cree, visualisable avec un afficheur postscript (ex: ggv, kghostview...)
  ofstream output;
  output.open("Segments.ps");//
  output << "%!PS-Adobe-3.0" << endl;
  output << endl;
  for(int i=0;i<n;i++){
    output << segments[2*i].abscisse << " " << segments[2*i].ordonnee << " 2 0 360 arc" <<endl;
    output << "0 setgray" <<endl;
    output << "fill" <<endl;

    output << segments[2*i+1].abscisse << " " << segments[2*i+1].ordonnee << " 2 0 360 arc" <<endl;
    output << "0 setgray" <<endl;
    output << "fill" <<endl;

    output << segments[2*i].abscisse << " " << segments[2*i].ordonnee << " moveto"  << endl;
    output << segments[2*i+1].abscisse << " " << segments[2*i+1].ordonnee << " lineto"  << endl;
    output << "stroke" << endl;

    output << segments[2*i].abscisse-20 << " " << segments[2*i].ordonnee << " moveto" <<endl;
    output << "/Courier findfont 15 scalefont setfont" << endl;
    output << "("<< i << ")" << " show" << endl;
    output << "stroke" << endl;
    output << endl;
  }
  output << endl;

  output.close();
}


//********************************************//

//Generation au hasard de l'ensemble des segments consideres
//Le premier sommet est celui d'abscisse minimale, on refusera des segments verticaux:
//Choisir segments[2*i].abscisse (=x) dans [20,400] et segments[2*i].ordonnee (=y) dans [100,700]
//Choisir segments[2*i+1].abscisse dans [x+1,x+100] et segments[2*i+1].ordonnee dans [y-50,y+50]

void SegmentsAuHasard(int n,point segments[]){
  srand(time(NULL));
  for(int i=0;i<n;i++){
    point p1,p2;
    p1.abscisse = 20+rand()%380;
    p1.ordonnee = 100+rand()%700;
    segments[2*i] = p1;
    p2.abscisse = p1.abscisse+1+rand()%100;
    p2.ordonnee = p1.ordonnee-50+rand()%100;
    segments[2*i+1] = p2;
  }
}


//********************************************//

//Renvoie Vrai si les deux segments p1p2 et p3p4 s'intersectent
//Dans un premier temps, on pourra supposer que deux segments ne sont jamais
//portes par une meme droite


bool Intersectent(point p1, point p2, point p3, point p4){

  //conversion en long long pour eviter un depacement d'int.

  long long x1= (long long) p1.abscisse;
  long long x2= (long long) p2.abscisse;
  long long x3= (long long) p3.abscisse;
  long long x4= (long long) p4.abscisse;

  long long y1= (long long) p1.ordonnee;
  long long y2= (long long) p2.ordonnee;
  long long y3= (long long) p3.ordonnee;
  long long y4= (long long) p4.ordonnee;
	
  long long det3 = (x2-x1)*(y3-y1)-(x3-x1)*(y2-y1), det4 = (x2-x1)*(y4-y1)-(x4-x1)*(y2-y1);
  if((det3 < 0 && det4 < 0) || (det3 > 0 && det4 > 0))
    return false;
  
  long long det1 = (x4-x3)*(y1-y3)-(x1-x3)*(y4-y3), det2 = (x4-x3)*(y2-y3)-(x2-x3)*(y4-y3);
  if((det1 < 0 && det2 < 0) || (det1 > 0 && det2 > 0))
    return false;
  
  return true;
}

//********************************************//

void TriLexicographique(point segments[], int t, int Tri[]){
  //En entree, Tri, tableau de taille 2*n, contient les indices dans 'segments' des sommets a trier, 
  //a l'initialisation Tri[i]=i, et t est la taille de Tri, donc t=2*n pour le premier appel.
  //En sorti, Tri contient les indices des sommets tries par ordre lexicographique croissant. 
  if(t>1){
    int pivot=Tri[0]; //indice du sommet pivot
    int d=0; // nombre de sommets a droite de min_pivot
    for(int i=1;i<t;i++){//On compte (on ne tient pas compte de pivot)
      if((segments[Tri[0]].abscisse<segments[Tri[i]].abscisse)||
	 ((segments[Tri[0]].abscisse==segments[Tri[i]].abscisse)&&
	  (segments[Tri[0]].ordonnee<segments[Tri[i]].ordonnee))){d++;}
    }
    int Tg[t-d-1];
    int Td[d];
    int indice_gauche=0; //indice d'insertion dans Tg
    int indice_droit=0; //indice d'insertion dans Td
    for(int i=1;i<t;i++){ //Remplissage de Tg et Td (on ne tient pas compte de pivot)
      if((segments[Tri[0]].abscisse<segments[Tri[i]].abscisse)||
	 ((segments[Tri[0]].abscisse==segments[Tri[i]].abscisse)&&
	  (segments[Tri[0]].ordonnee<segments[Tri[i]].ordonnee))){//A droite
	Td[indice_droit]=Tri[i];
	indice_droit++;}
      else{//A gauche
	Tg[indice_gauche]=Tri[i];
	indice_gauche++;}}

    //On trie Td et Tg
    if(d>0){TriLexicographique(segments,d,Td);}
    if(t-d-1>0){TriLexicographique(segments,t-d-1,Tg);}
    //Fusion dans Tri
    for(int i=0;i<t;i++){
      if(i<t-d-1){Tri[i]=Tg[i];}
      if(i==t-d-1){Tri[i]=pivot;}
      if(i>t-d-1){Tri[i]=Td[i-t+d];}
    }
  }
}

//********************************************//

//Algo d'intersection
//Renvoie vrai si il existe 2 segments qui s'intersectent, faux sinon
//Fonctionne en nlog n

bool Intersection(int n, point segments[]){

  bool result = false;

  //Tri contient les abscisses des extremites des segments, c'est l'echeancier
  int Tri[2*n];
  for(int i=0;i<2*n;i++){
    Tri[i]=i;
  }

  TriLexicographique(segments,2*n,Tri);

  ARN ordre(&ClesEgales,&CleInferieure);

  for(int i=0; i<2*n; i++){
    int j=Tri[i];
    if(Tri[i]%2 == 0) {
      //gauche
      ordre.Insere(j);
      int p = ordre.Predecesseur(j), s = ordre.Successeur(j);
      if(p!=-1 && Intersectent(segments[p], segments[p+1], segments[j], segments[j+1])) {
		cout<<p/2<<" intersecte "<<j/2<<endl;
		result = true;
	  }
	  if(s!=-1 && Intersectent(segments[s], segments[s+1], segments[j], segments[j+1])) {
		cout<<s/2<<" intersecte "<<j/2<<endl;
		result = true;
	  }
    }
    else {
      //droite
      int p = ordre.Predecesseur(j), s = ordre.Successeur(j);
      if(p!=-1 && s!=-1 && Intersectent(segments[p], segments[p+1], segments[s], segments[s+1])) {
		cout<<p/2<<" intersecte "<<s/2<<endl;
		result = true;
	  }
      ordre.Supprime(j);
    }
  }

  return result;

}

//********************************************//

int main(){

  if(false) {
    point p1,p2,p3,p4;
    p1.abscisse = 2;
    p1.ordonnee = 2;
    p2.abscisse = 5;
    p2.ordonnee = 2;
    p3.abscisse = 6;
    p3.ordonnee = 3;
    p4.abscisse = 6;
    p4.ordonnee = 1;
    
    cout<<"Test 1 : ";
    if(Intersectent(p1,p2,p3,p4))
      cout<<"true";
    else
      cout<<"false";
    cout<<endl;
  }
  
  SegmentsAuHasard(n,segments);
segments[0].abscisse=202;
segments[0].ordonnee=203;
segments[1].abscisse=351;
segments[1].ordonnee=223;
segments[2].abscisse=52;
segments[2].ordonnee=616;
segments[3].abscisse=235;
segments[3].ordonnee=647;
segments[4].abscisse=250;
segments[4].ordonnee=100;
segments[5].abscisse=381;
segments[5].ordonnee=246;
segments[6].abscisse=332;
segments[6].ordonnee=124;
segments[7].abscisse=453;
segments[7].ordonnee=77;
segments[8].abscisse=318;
segments[8].ordonnee=613;
segments[9].abscisse=485;
segments[9].ordonnee=649;
segments[10].abscisse=206;
segments[10].ordonnee=146;
segments[11].abscisse=258;
segments[11].ordonnee=159;
segments[12].abscisse=24;
segments[12].ordonnee=287;
segments[13].abscisse=221;
segments[13].ordonnee=331;
segments[14].abscisse=26;
segments[14].ordonnee=267;
segments[15].abscisse=115;
segments[15].ordonnee=288;
segments[16].abscisse=75;
segments[16].ordonnee=114;
segments[17].abscisse=174;
segments[17].ordonnee=130;
segments[18].abscisse=246;
segments[18].ordonnee=242;
segments[19].abscisse=510;
segments[19].ordonnee=225;
  AffichageSegments(n,segments);

  /*if(Intersection(n,segments)){
    cout << "Il y a une intersection." << endl;
  }else{
    cout <<"Il n'y a pas d'intersection." << endl;
  }*/

  for(int i=0; i<2*n; i+=2){
  	for(int j=i+2; j<2*n; j+=2){
      if(Intersectent(segments[i], segments[i+1], segments[j], segments[j+1])) {
		cout<<i/2<<" intersecte "<<j/2<<endl;
	  }
    }
  }
}


//********************************************//
