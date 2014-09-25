#include <iostream>
#include <fstream>
#include <math.h> // pour cos() et sin()
#define PI 3.14159265
#include <stdlib.h>
//#include "Echantillon2.h"


using namespace std;
const int n=1000;
int sommet[n][2];

/*******************************************************************/
// Structure triangle
/*******************************************************************/

//structure triangle, pour une variable triangle  T, ses sommets sont accessibles par
//T.a, T.b et T.c

typedef struct {
  int a;
  int b;
  int c;
} triangle;

/*******************************************************************/
//Petites fonctions arithmetiques ou geometriques
/*******************************************************************/


int det(int p0[2], int p1[2], int p2[2],int p3[2]){

//Renvoie le determinant de p0p1,p2p3

  return (p1[0]-p0[0])*(p3[1]-p2[1])-(p1[1]-p0[1])*(p3[0]-p2[0]);
}

//------------------------------

int ProduitScalaire(int p0[2], int p1[2], int p2[2],int p3[2]){

//Renvoie le produit scalaire de p0p1,p2p3

  return (p1[0]-p0[0])*(p3[0]-p2[0])+(p1[1]-p0[1])*(p3[1]-p2[1]);
}

//------------------------------

int Carre(int x){
  return x*x;}

//-----------------------------

int NormeAuCarre(int p1[2],int p2[2]){

  //Calcul la norme au carre de p1p2

  return Carre(p1[1]-p2[1])+Carre(p1[0]-p2[0]);
}


//------------------------------

bool EstADroite(int A[2], int B[2], int C[2]){
  //Renvoie vrai si C est strictement a droite de (AB) oriente de A vers B.
  if(det(A,B,A,C)>=0){return false;}
  else{return true;}
}



/*******************************************************************/
//Calcul du rayon du cercle circonscrit a un triangle
/*******************************************************************/

int CentreCercleCirconscrit(int A[2], int B[2],int C[2], double O[3]){

  //Stocke dans O les coordonnees du centre du cercle circonscrit a A, B et C
    //Renvoie 1 si ces 3 points sont alignes, 0 sinon et fait le calcul dans ce cas

    if(det(A,B,A,C)==0){return 1;}
   int xa=A[0]; int ya=A[1];
   int xb=B[0]; int yb=B[1];
   int xc=C[0]; int yc=C[1];
   O[0]=((double)((yc-yb)*(xb*xb+yb*yb-xa*xa-ya*ya)-(yb-ya)*(xc*xc+yc*yc-xb*xb-yb*yb))/(double)(2*det(A,B,B,C)));
   O[1]=((double)((xc-xb)*(xb*xb+yb*yb-xa*xa-ya*ya)-(xb-xa)*(xc*xc+yc*yc-xb*xb-yb*yb))/(double)(2*det(B,C,A,B)));
   return 0;
}

double distance(double O[2], int p[2]) {
	return pow(O[1]-p[1], 2)+pow(O[0]-p[0], 2);
}
//-----------------------------

double RayonCercleCirconscrit(int A[2], int B[2],int C[2]){
  //Renvoie le rayon du cercle circonscrit a ABC
  double O[2];
  if(CentreCercleCirconscrit(A,B,C,O) == 0) {
	  return distance(O,A);
  }
  else {
	  return 0;
  }
}







/*******************************************************************/
//Fonctions d'affichage
/*******************************************************************/

void AffichagePoints(int n, int sommet[][2]){

  //Affichage de n points dont les coordonnees sont dans sommet[n][2]
  //Un fichier Points.ps est cree, visualisable avec un afficheur postscript (ex: ggv, kghostview)

  ofstream output;
   output.open("Points.ps");//
   output << "%!PS-Adobe-3.0" << endl;
   output << endl;  
   for(int i=0;i<n;i++){
     output << sommet[i][0] << " " << sommet[i][1] << " 2 0 360 arc" <<endl;
     output << "0 setgray" <<endl;
     output << "fill" <<endl;
       output << "stroke" << endl;
     output << endl;
   }
   output << endl;
   output.close();
}

//-------------------------------------

void AffichageTriangulation(int n, int sommet[][2], int t, triangle T[]){

  //Affichage des n points du plan dont les coordonnees sont dans sommet[][2] et d'une triangulation
  //en t triangles stockes dans T, tableau de taille t.

   ofstream output;
   output.open("AlphaShape.ps");
   output << "%!PS-Adobe-3.0" << endl;
   output << endl;  
   for(int i=0;i<n;i++){
     output << sommet[i][0] << " " << sommet[i][1] << " 2 0 360 arc" <<endl;
     output << "0 setgray" <<endl;
     output << "fill" <<endl;
       output << "stroke" << endl;
     output << endl;
   }
   output << endl;
    for(int i=0;i<t;i++){
      output << sommet[T[i].a][0] << " " << sommet[T[i].a][1] 
 	    << " moveto"  << endl;
      output << sommet[T[i].b][0] << " " << sommet[T[i].b][1]
 	    << " lineto"  << endl;
      output << sommet[T[i].b][0] << " " << sommet[T[i].b][1] 
 	    << " moveto"  << endl;
      output << sommet[T[i].c][0] << " " << sommet[T[i].c][1]
 	    << " lineto"  << endl;
      output << sommet[T[i].c][0] << " " << sommet[T[i].c][1] 
 	    << " moveto"  << endl;
      output << sommet[T[i].a][0] << " " << sommet[T[i].a][1]
 	    << " lineto"  << endl;
      output << "stroke" << endl;
      output << endl;
    }
    output.close();
}

/*******************************************************************/
// Triangulation de Delaunay, celle de votre tp3 ou a recuperer avec
// les fonctions qui vont avec...
//
/*******************************************************************/

bool MemeCote(int A[2], int B[2], int C[2], int D[2]){

  //Renvoie vrai si C et D sont du meme cote de (AB).

  if((det(A,B,A,C)*det(A,B,A,D))>0){return true;}
  else{return false;}
}

//----------------------------------------

bool StrictementDansLeCercleCirconscritMemeCote(int A[2], int B[2], int C[2], int D[2]){

  //Renvoie vrai si D est strictement dans le cercle circonscrit de ABC.
  //On suppose C et D du meme cote de (AB).
  //Faire un test entier

  int ACB = (int)acos(ProduitScalaire(C,A,C,B)/sqrt(NormeAuCarre(C,A)*NormeAuCarre(C,B)));
  int ADB = (int)acos(ProduitScalaire(D,A,D,B)/sqrt(NormeAuCarre(D,A)*NormeAuCarre(D,B)));

  return (ADB > ACB);
}

//----------------------------------

bool StrictementDansLeCercleCirconscrit(int A[2], int B[2], int C[2], int D[2]){
  double O[2];
  if(CentreCercleCirconscrit(A,B,C,O) == 0) {
	  return ((long long)distance(O,A) > (long long)distance(O,D));
  }
  else {
	  return false;
  }
}

//----------------------------------


void TriLexicographique(int n, int sommet[][2], int t, int Tri[]){
  if(t>1){
    int pivot=Tri[0]; //indice du sommet pivot
    int d=0; // nombre de sommets a droite de min_pivot
    for(int i=1;i<t;i++){//On compte (on ne tient pas compte de pivot)
      if((sommet[Tri[0]][0]<sommet[Tri[i]][0])||
	 ((sommet[Tri[0]][0]==sommet[Tri[i]][0])&&
	  (sommet[Tri[0]][1]<sommet[Tri[i]][1]))){d++;}
    }
    int Tg[t-d-1];
    int Td[d];
    int indice_gauche=0; //indice d'insertion dans Tg
    int indice_droit=0; //indice d'insertion dans Td
    for(int i=1;i<t;i++){ //Remplissage de Tg et Td (on ne tient pas compte de pivot)
      if((sommet[Tri[0]][0]<sommet[Tri[i]][0])||
	 ((sommet[Tri[0]][0]==sommet[Tri[i]][0])&&
	  (sommet[Tri[0]][1]<sommet[Tri[i]][1]))){//A droite
      Td[indice_droit]=Tri[i];
      indice_droit++;}
      else{//A gauche
      Tg[indice_gauche]=Tri[i];
      indice_gauche++;}}

    //On trie Td et Tg
    if(d>0){TriLexicographique(n,sommet,d,Td);}
    if(t-d-1>0){TriLexicographique(n,sommet,t-d-1,Tg);}
    //Fusion dans Tri
    for(int i=0;i<t;i++){
      if(i<t-d-1){Tri[i]=Tg[i];}
      if(i==t-d-1){Tri[i]=pivot;}
      if(i>t-d-1){Tri[i]=Td[i-t+d];}
    }
  }
}

//----------------------------------


int TriangulIncrementale(int n, int sommet[][2], int tri[], triangle T[]){
	int envconv[n+1];
	int taille_envconv=3;
	int nbre_triangle=0;
	
	//Creation du premier triangle de sommets tri[0], tri[1] et tri[1].
	
	triangle t;
	if(EstADroite(sommet[tri[2]], sommet[tri[1]], sommet[tri[0]])) {
		t.a = envconv[1] = tri[0];
		t.b = envconv[2] = tri[1];
	}
	else {
		t.a = envconv[1] = tri[1];
		t.b = envconv[2] = tri[0];
	}
	t.c = envconv[0] = envconv[3] = tri[2];
	T[nbre_triangle] = t;
	++nbre_triangle;
	//cout<<"ajout triangle "<<t.a<<" "<<t.b<<" "<<t.c<<endl;
	
	
	//Deroulement de l'algorithme
	for(int i=3;i<n;i++){//insertion de tri[i]
		if(sommet[tri[i]][0]==sommet[envconv[0]][0] && sommet[tri[i]][1]==sommet[envconv[0]][1]){
			continue;
		}//Si on a 2 points confondus, la maj de l'env conv peut bugger!
		
		//t.a = tri[i];
		
		int j = 0;
		
		//Recherche de kdroite, l'indice du sommet dans envconv le plus loin dans le sens direct visible depuis tri[i]
		while(j < n && det(sommet[tri[i]], sommet[envconv[j]], sommet[tri[i]], sommet[envconv[j+1]]) < 0) {
			t.a = envconv[j];
			t.b = envconv[j+1];
			t.c = tri[i];
			T[nbre_triangle] = t;
			++nbre_triangle;
			++j;
		}
		if(j < n) {
			int kdroite = j;
			//t.b = envconv[kdroite];
			j = taille_envconv;
			
			//Recherche de kgauche, l'indice du sommet dans envconv le plus loin dans le sens indirect visible depuis tri[i]
			while(j > 0 && det(sommet[tri[i]], sommet[envconv[j]], sommet[tri[i]], sommet[envconv[j-1]]) > 0) {
				t.a = envconv[j];
				t.b = envconv[j-1];
				t.c = tri[i];
				T[nbre_triangle] = t;
				++nbre_triangle;
				--j;
			}
			if(j > 0) {
				int kgauche = j;
				//t.c = envconv[kgauche];
				//T[nbre_triangle] = t;
				//++nbre_triangle;
				/*
				cout<<"envconv = ";
				for(int k(0) ; k <= taille_envconv ; ++k) {
					cout<<envconv[k]<<" ";
				}
				cout<<"    ---> k+1 : "<<taille_envconv<<endl;
				cout<<"ajout triangle "<<t.a<<" "<<t.b<<" "<<t.c<<endl;
				cout<<"  -> kdroite : "<<envconv[kdroite]<<", kgauche : "<<envconv[kgauche]<<endl<<endl;
				*/
				//Mise a jour de envconv, on peut utiliser une copie temporaire
				int tmp[n+1], indice=1;
				for(int k(kdroite) ; k <= kgauche ; ++k) {
					tmp[indice] = envconv[k];
					indice++;
				}
				taille_envconv = indice;
				tmp[0] = tmp[taille_envconv] = tri[i];
				
				for(int k(0) ; k <= taille_envconv ; ++k) {
					envconv[k] = tmp[k];
				}
			}
			else {
				cout << "erreur : j <= 0" << endl;
			}
		}
		else {
			cout << "erreur : j >= n" << endl;
		}
		
	}
	
	return nbre_triangle;
}

bool TrianglesAdjacents(triangle s, triangle t){

  //renvoie vrai si s et t ont une arete en commun

  int sommet_commun=0;
  if((s.a==t.a)||(s.a==t.b)||(s.a==t.c)){sommet_commun++;}
  if((s.b==t.a)||(s.b==t.b)||(s.b==t.c)){sommet_commun++;}
  if((s.c==t.a)||(s.c==t.b)||(s.c==t.c)){sommet_commun++;}
  if(sommet_commun>=2){return true;}
  return false;
}

//-------------------------------------------

void TrianglesVoisins(int t, triangle T[], int voisin[][3]){
 
  //Calcul pour chaque triangle les indices des triangles qui lui sont adjacents

  for(int i=0;i<t;i++){
    for(int j=0;j<i;j++){
      if(TrianglesAdjacents(T[i],T[j])){
	int case_libre;
	if(voisin[i][0]==-1){case_libre=0;}
	   else{if(voisin[i][1]==-1){case_libre=1;}
	   else{case_libre=2;}}
	voisin[i][case_libre]=j;
	if(voisin[j][0]==-1){case_libre=0;}
	else{if(voisin[j][1]==-1){case_libre=1;}
	else{case_libre=2;}}
	voisin[j][case_libre]=i;
      }
    }
  }
}
     
//-------------------------------------------

int TroisiemePoint(triangle s, triangle t){

  //Renvoie l'indice du point de s qui n'est pas dans t

  if((s.a!=t.a)&&(s.a!=t.b)&&(s.a!=t.c)){return s.a;}
  if((s.b!=t.a)&&(s.b!=t.b)&&(s.b!=t.c)){return s.b;}
  if((s.c!=t.a)&&(s.c!=t.b)&&(s.c!=t.c)){return s.c;}
  return -1;
}

//---------------------------------------------

int TriangleArete(int i, int x, int y, triangle T[], int voisin[][3]){

  //Renvoie le second triangle de T ayant xy comme arete (T[i] etant le premier)

  for(int k=0;k<3;k++){
    if(voisin[i][k]==-1){continue;}//on tape de l'autre cote de l'enveloppe convexe
    if((T[voisin[i][k]].a == x) && ((T[voisin[i][k]].b == y) || (T[voisin[i][k]].c == y))){
      return voisin[i][k];}
    if((T[voisin[i][k]].b == x) && ((T[voisin[i][k]].a == y) || (T[voisin[i][k]].c == y))){
      return voisin[i][k];}
    if((T[voisin[i][k]].c == x) && ((T[voisin[i][k]].b == y) || (T[voisin[i][k]].a == y))){
      return voisin[i][k];}
  }
  return -1;

}



//---------------------------------------------

void Flip(int i, int j, int t, triangle T[], int voisin[][3]){

  //Effectue un 'flip' entre les triangles T[i] et T[j]
  //t est la taille du tableau T et voisin, tableau calcule
  //par la fonction TrianglesVoisins, sera mis-a-jour

  int vieux_voisins_Ti[3]={voisin[i][0],voisin[i][1],voisin[i][2]};
  int vieux_voisins_Tj[3]={voisin[j][0],voisin[j][1],voisin[j][2]};
  int x=TroisiemePoint(T[i],T[j]);// On nomme les 4 sommets
  int y=TroisiemePoint(T[j],T[i]);
  int z;
  int w;
  if(T[i].a==x){z=T[i].b; w=T[i].c;}
  if(T[i].b==x){z=T[i].a; w=T[i].c;}
  if(T[i].c==x){z=T[i].a; w=T[i].b;}
 

  //mise a jour des voisins, faire un dessin...

  int Tiz= TriangleArete(i,x,z,T,voisin);
  int Tiw= TriangleArete(i,x,w,T,voisin);
  int Tjz= TriangleArete(j,y,z,T,voisin);
  int Tjw= TriangleArete(j,y,w,T,voisin);

  T[i].a=z;T[i].b=x;T[i].c=y;  // mise a jour de Ti et Tj
  T[j].a=w;T[j].b=x;T[j].c=y;

  voisin[i][0]=j; voisin[i][1]=Tiz; voisin[i][2]=Tjz; //mise a jour voisins de i
  voisin[j][0]=i; voisin[j][1]=Tiw; voisin[j][2]=Tjw; //mise a jour voisins de j

  if(Tiw!=-1){//mise a jour voisins Tiw
    if(voisin[Tiw][0]==i){voisin[Tiw][0]=j;}
    if(voisin[Tiw][1]==i){voisin[Tiw][1]=j;}
    if(voisin[Tiw][2]==i){voisin[Tiw][2]=j;}
  }

  if(Tjz!=-1){//mise a jour voisins Tjz
    if(voisin[Tjz][0]==j){voisin[Tjz][0]=i;}
    if(voisin[Tjz][1]==j){voisin[Tjz][1]=i;}
    if(voisin[Tjz][2]==j){voisin[Tjz][2]=i;}
  }
}


//----------------------------------
 

int Delaunay(int n, int sommet[][2],int t, triangle T[]){
	int cpt = 0;
  int flag=1;
  int voisin[t][3]; // Creation et initialisation de voisin
  for(int i=0;i<t;i++){
    voisin[i][0]=-1;
    voisin[i][1]=-1;
    voisin[i][2]=-1;
  }
  TrianglesVoisins(t,T,voisin);

  while(flag == 1) {
	flag = 0;
	for(int i(0) ; i<t ; ++i) {
		for(int j(0) ; j<3 ; ++j) {
			if(voisin[i][j] != -1) {
				int p1 = TroisiemePoint(T[voisin[i][j]],T[i]);
				int p2 = TroisiemePoint(T[i],T[voisin[i][j]]);
				if(p1 != -1 && StrictementDansLeCercleCirconscrit(sommet[T[i].a], sommet[T[i].b], sommet[T[i].c], sommet[p1])) {
					//cout<<tp<<" dans le circonscrit de "<<T[i].a<<" "<<T[i].b<<" "<<T[i].c<<endl;
					//cout<<"Flip "<<T[i].a<<" "<<T[i].b<<" "<<T[i].c<<" avec "<<T[voisin[i][j]].a<<" "<<T[voisin[i][j]].b<<" "<<T[voisin[i][j]].c<<endl;
					Flip(i,voisin[i][j],t,T,voisin);
					flag = 1;
					cout<<"flip "<<i<<" et "<<j<<endl;
					break;
				}
				else if(p2 != -1 && StrictementDansLeCercleCirconscrit(sommet[T[voisin[i][j]].a], sommet[T[voisin[i][j]].b], sommet[T[voisin[i][j]].c], sommet[p2])) {
					//cout<<tp<<" dans le circonscrit de "<<T[i].a<<" "<<T[i].b<<" "<<T[i].c<<endl;
					//cout<<"Flip "<<T[i].a<<" "<<T[i].b<<" "<<T[i].c<<" avec "<<T[voisin[i][j]].a<<" "<<T[voisin[i][j]].b<<" "<<T[voisin[i][j]].c<<endl;
					Flip(voisin[i][j],i,t,T,voisin);
					flag = 1;
					cout<<"flip "<<i<<" et "<<j<<endl;
					break;
				}
			}
		}
	}
  }

    return 0;
}

/*******************************************************************/
//main
/*******************************************************************/


int main(){

sommet[0][0]=127;
sommet[0][1]=176;
sommet[1][0]=155;
sommet[1][1]=306;
sommet[2][0]=82;
sommet[2][1]=296;
sommet[3][0]=139;
sommet[3][1]=254;
sommet[4][0]=133;
sommet[4][1]=178;
sommet[5][0]=348;
sommet[5][1]=264;
sommet[6][0]=139;
sommet[6][1]=366;
sommet[7][0]=562;
sommet[7][1]=242;
sommet[8][0]=27;
sommet[8][1]=208;
sommet[9][0]=192;
sommet[9][1]=246;
sommet[10][0]=188;
sommet[10][1]=206;
sommet[11][0]=105;
sommet[11][1]=456;
sommet[12][0]=387;
sommet[12][1]=226;
sommet[13][0]=209;
sommet[13][1]=258;
sommet[14][0]=128;
sommet[14][1]=182;
sommet[15][0]=136;
sommet[15][1]=468;
sommet[16][0]=565;
sommet[16][1]=478;
sommet[17][0]=30;
sommet[17][1]=228;
sommet[18][0]=37;
sommet[18][1]=284;
sommet[19][0]=417;
sommet[19][1]=164;
sommet[20][0]=445;
sommet[20][1]=288;
sommet[21][0]=112;
sommet[21][1]=430;
sommet[22][0]=51;
sommet[22][1]=368;
sommet[23][0]=425;
sommet[23][1]=372;
sommet[24][0]=281;
sommet[24][1]=422;
sommet[25][0]=381;
sommet[25][1]=254;
sommet[26][0]=295;
sommet[26][1]=196;
sommet[27][0]=416;
sommet[27][1]=176;
sommet[28][0]=193;
sommet[28][1]=160;
sommet[29][0]=166;
sommet[29][1]=260;
sommet[30][0]=396;
sommet[30][1]=220;
sommet[31][0]=134;
sommet[31][1]=170;
sommet[32][0]=131;
sommet[32][1]=316;
sommet[33][0]=182;
sommet[33][1]=292;
sommet[34][0]=275;
sommet[34][1]=468;
sommet[35][0]=275;
sommet[35][1]=410;
sommet[36][0]=179;
sommet[36][1]=230;
sommet[37][0]=57;
sommet[37][1]=172;
sommet[38][0]=162;
sommet[38][1]=344;
sommet[39][0]=261;
sommet[39][1]=450;
sommet[40][0]=45;
sommet[40][1]=380;
sommet[41][0]=407;
sommet[41][1]=156;
sommet[42][0]=272;
sommet[42][1]=448;
sommet[43][0]=450;
sommet[43][1]=318;
sommet[44][0]=274;
sommet[44][1]=250;
sommet[45][0]=273;
sommet[45][1]=334;
sommet[46][0]=119;
sommet[46][1]=232;
sommet[47][0]=31;
sommet[47][1]=346;
sommet[48][0]=213;
sommet[48][1]=300;
sommet[49][0]=237;
sommet[49][1]=216;
sommet[50][0]=322;
sommet[50][1]=352;
sommet[51][0]=274;
sommet[51][1]=472;
sommet[52][0]=347;
sommet[52][1]=436;
sommet[53][0]=32;
sommet[53][1]=402;
sommet[54][0]=426;
sommet[54][1]=264;
sommet[55][0]=177;
sommet[55][1]=164;
sommet[56][0]=55;
sommet[56][1]=306;
sommet[57][0]=260;
sommet[57][1]=366;
sommet[58][0]=263;
sommet[58][1]=292;
sommet[59][0]=276;
sommet[59][1]=470;
sommet[60][0]=160;
sommet[60][1]=326;
sommet[61][0]=340;
sommet[61][1]=160;
sommet[62][0]=406;
sommet[62][1]=190;
sommet[63][0]=317;
sommet[63][1]=150;
sommet[64][0]=294;
sommet[64][1]=406;
sommet[65][0]=35;
sommet[65][1]=464;
sommet[66][0]=255;
sommet[66][1]=346;
sommet[67][0]=576;
sommet[67][1]=172;
sommet[68][0]=589;
sommet[68][1]=440;
sommet[69][0]=564;
sommet[69][1]=324;
sommet[70][0]=329;
sommet[70][1]=216;
sommet[71][0]=272;
sommet[71][1]=284;
sommet[72][0]=178;
sommet[72][1]=166;
sommet[73][0]=309;
sommet[73][1]=216;
sommet[74][0]=92;
sommet[74][1]=306;
sommet[75][0]=327;
sommet[75][1]=432;
sommet[76][0]=346;
sommet[76][1]=370;
sommet[77][0]=89;
sommet[77][1]=296;
sommet[78][0]=175;
sommet[78][1]=374;
sommet[79][0]=345;
sommet[79][1]=348;
sommet[80][0]=409;
sommet[80][1]=220;
sommet[81][0]=36;
sommet[81][1]=232;
sommet[82][0]=427;
sommet[82][1]=160;
sommet[83][0]=565;
sommet[83][1]=344;
sommet[84][0]=417;
sommet[84][1]=282;
sommet[85][0]=323;
sommet[85][1]=470;
sommet[86][0]=173;
sommet[86][1]=232;
sommet[87][0]=32;
sommet[87][1]=398;
sommet[88][0]=127;
sommet[88][1]=360;
sommet[89][0]=582;
sommet[89][1]=466;
sommet[90][0]=425;
sommet[90][1]=316;
sommet[91][0]=585;
sommet[91][1]=274;
sommet[92][0]=556;
sommet[92][1]=300;
sommet[93][0]=320;
sommet[93][1]=184;
sommet[94][0]=45;
sommet[94][1]=400;
sommet[95][0]=125;
sommet[95][1]=298;
sommet[96][0]=115;
sommet[96][1]=250;
sommet[97][0]=189;
sommet[97][1]=154;
sommet[98][0]=61;
sommet[98][1]=318;
sommet[99][0]=431;
sommet[99][1]=272;
sommet[100][0]=552;
sommet[100][1]=444;
sommet[101][0]=43;
sommet[101][1]=376;
sommet[102][0]=441;
sommet[102][1]=224;
sommet[103][0]=106;
sommet[103][1]=346;
sommet[104][0]=106;
sommet[104][1]=328;
sommet[105][0]=295;
sommet[105][1]=166;
sommet[106][0]=57;
sommet[106][1]=376;
sommet[107][0]=156;
sommet[107][1]=340;
sommet[108][0]=127;
sommet[108][1]=184;
sommet[109][0]=328;
sommet[109][1]=194;
sommet[110][0]=29;
sommet[110][1]=326;
sommet[111][0]=296;
sommet[111][1]=440;
sommet[112][0]=212;
sommet[112][1]=342;
sommet[113][0]=31;
sommet[113][1]=262;
sommet[114][0]=184;
sommet[114][1]=320;
sommet[115][0]=121;
sommet[115][1]=320;
sommet[116][0]=429;
sommet[116][1]=248;
sommet[117][0]=273;
sommet[117][1]=246;
sommet[118][0]=238;
sommet[118][1]=308;
sommet[119][0]=133;
sommet[119][1]=442;
sommet[120][0]=336;
sommet[120][1]=428;
sommet[121][0]=274;
sommet[121][1]=466;
sommet[122][0]=566;
sommet[122][1]=240;
sommet[123][0]=40;
sommet[123][1]=422;
sommet[124][0]=41;
sommet[124][1]=390;
sommet[125][0]=561;
sommet[125][1]=410;
sommet[126][0]=295;
sommet[126][1]=154;
sommet[127][0]=581;
sommet[127][1]=270;
sommet[128][0]=214;
sommet[128][1]=158;
sommet[129][0]=111;
sommet[129][1]=228;
sommet[130][0]=49;
sommet[130][1]=248;
sommet[131][0]=582;
sommet[131][1]=170;
sommet[132][0]=102;
sommet[132][1]=334;
sommet[133][0]=583;
sommet[133][1]=470;
sommet[134][0]=265;
sommet[134][1]=298;
sommet[135][0]=389;
sommet[135][1]=364;
sommet[136][0]=110;
sommet[136][1]=366;
sommet[137][0]=240;
sommet[137][1]=198;
sommet[138][0]=335;
sommet[138][1]=462;
sommet[139][0]=42;
sommet[139][1]=384;
sommet[140][0]=63;
sommet[140][1]=348;
sommet[141][0]=432;
sommet[141][1]=376;
sommet[142][0]=347;
sommet[142][1]=370;
sommet[143][0]=336;
sommet[143][1]=280;
sommet[144][0]=559;
sommet[144][1]=274;
sommet[145][0]=588;
sommet[145][1]=326;
sommet[146][0]=182;
sommet[146][1]=276;
sommet[147][0]=566;
sommet[147][1]=326;
sommet[148][0]=125;
sommet[148][1]=374;
sommet[149][0]=40;
sommet[149][1]=400;
sommet[150][0]=113;
sommet[150][1]=412;
sommet[151][0]=89;
sommet[151][1]=278;
sommet[152][0]=289;
sommet[152][1]=234;
sommet[153][0]=126;
sommet[153][1]=474;
sommet[154][0]=566;
sommet[154][1]=168;
sommet[155][0]=588;
sommet[155][1]=394;
sommet[156][0]=348;
sommet[156][1]=312;
sommet[157][0]=265;
sommet[157][1]=470;
sommet[158][0]=69;
sommet[158][1]=464;
sommet[159][0]=329;
sommet[159][1]=438;
sommet[160][0]=57;
sommet[160][1]=216;
sommet[161][0]=122;
sommet[161][1]=158;
sommet[162][0]=349;
sommet[162][1]=356;
sommet[163][0]=108;
sommet[163][1]=200;
sommet[164][0]=258;
sommet[164][1]=252;
sommet[165][0]=320;
sommet[165][1]=462;
sommet[166][0]=339;
sommet[166][1]=168;
sommet[167][0]=42;
sommet[167][1]=446;
sommet[168][0]=402;
sommet[168][1]=190;
sommet[169][0]=586;
sommet[169][1]=430;
sommet[170][0]=227;
sommet[170][1]=320;
sommet[171][0]=112;
sommet[171][1]=234;
sommet[172][0]=562;
sommet[172][1]=190;
sommet[173][0]=338;
sommet[173][1]=144;
sommet[174][0]=87;
sommet[174][1]=304;
sommet[175][0]=394;
sommet[175][1]=380;
sommet[176][0]=420;
sommet[176][1]=172;
sommet[177][0]=384;
sommet[177][1]=238;
sommet[178][0]=441;
sommet[178][1]=280;
sommet[179][0]=181;
sommet[179][1]=226;
sommet[180][0]=202;
sommet[180][1]=372;
sommet[181][0]=336;
sommet[181][1]=446;
sommet[182][0]=123;
sommet[182][1]=270;
sommet[183][0]=283;
sommet[183][1]=262;
sommet[184][0]=179;
sommet[184][1]=290;
sommet[185][0]=437;
sommet[185][1]=226;
sommet[186][0]=191;
sommet[186][1]=266;
sommet[187][0]=54;
sommet[187][1]=378;
sommet[188][0]=166;
sommet[188][1]=182;
sommet[189][0]=573;
sommet[189][1]=434;
sommet[190][0]=390;
sommet[190][1]=202;
sommet[191][0]=345;
sommet[191][1]=338;
sommet[192][0]=47;
sommet[192][1]=146;
sommet[193][0]=318;
sommet[193][1]=330;
sommet[194][0]=413;
sommet[194][1]=230;
sommet[195][0]=179;
sommet[195][1]=212;
sommet[196][0]=132;
sommet[196][1]=238;
sommet[197][0]=62;
sommet[197][1]=354;
sommet[198][0]=154;
sommet[198][1]=318;
sommet[199][0]=577;
sommet[199][1]=244;
sommet[200][0]=132;
sommet[200][1]=270;
sommet[201][0]=582;
sommet[201][1]=252;
sommet[202][0]=270;
sommet[202][1]=468;
sommet[203][0]=423;
sommet[203][1]=266;
sommet[204][0]=382;
sommet[204][1]=170;
sommet[205][0]=552;
sommet[205][1]=458;
sommet[206][0]=393;
sommet[206][1]=194;
sommet[207][0]=64;
sommet[207][1]=320;
sommet[208][0]=135;
sommet[208][1]=236;
sommet[209][0]=586;
sommet[209][1]=248;
sommet[210][0]=314;
sommet[210][1]=204;
sommet[211][0]=310;
sommet[211][1]=194;
sommet[212][0]=365;
sommet[212][1]=230;
sommet[213][0]=164;
sommet[213][1]=310;
sommet[214][0]=335;
sommet[214][1]=208;
sommet[215][0]=115;
sommet[215][1]=248;
sommet[216][0]=446;
sommet[216][1]=280;
sommet[217][0]=120;
sommet[217][1]=436;
sommet[218][0]=336;
sommet[218][1]=206;
sommet[219][0]=225;
sommet[219][1]=372;
sommet[220][0]=170;
sommet[220][1]=176;
sommet[221][0]=374;
sommet[221][1]=282;
sommet[222][0]=321;
sommet[222][1]=382;
sommet[223][0]=208;
sommet[223][1]=254;
sommet[224][0]=366;
sommet[224][1]=228;
sommet[225][0]=108;
sommet[225][1]=330;
sommet[226][0]=55;
sommet[226][1]=306;
sommet[227][0]=552;
sommet[227][1]=456;
sommet[228][0]=228;
sommet[228][1]=342;
sommet[229][0]=233;
sommet[229][1]=274;
sommet[230][0]=407;
sommet[230][1]=170;
sommet[231][0]=182;
sommet[231][1]=178;
sommet[232][0]=581;
sommet[232][1]=260;
sommet[233][0]=63;
sommet[233][1]=224;
sommet[234][0]=268;
sommet[234][1]=172;
sommet[235][0]=373;
sommet[235][1]=234;
sommet[236][0]=430;
sommet[236][1]=340;
sommet[237][0]=267;
sommet[237][1]=466;
sommet[238][0]=238;
sommet[238][1]=224;
sommet[239][0]=271;
sommet[239][1]=204;
sommet[240][0]=420;
sommet[240][1]=300;
sommet[241][0]=294;
sommet[241][1]=340;
sommet[242][0]=138;
sommet[242][1]=276;
sommet[243][0]=372;
sommet[243][1]=308;
sommet[244][0]=214;
sommet[244][1]=158;
sommet[245][0]=65;
sommet[245][1]=344;
sommet[246][0]=342;
sommet[246][1]=202;
sommet[247][0]=338;
sommet[247][1]=464;
sommet[248][0]=167;
sommet[248][1]=228;
sommet[249][0]=581;
sommet[249][1]=400;
sommet[250][0]=82;
sommet[250][1]=322;
sommet[251][0]=225;
sommet[251][1]=358;
sommet[252][0]=310;
sommet[252][1]=164;
sommet[253][0]=158;
sommet[253][1]=234;
sommet[254][0]=319;
sommet[254][1]=364;
sommet[255][0]=30;
sommet[255][1]=362;
sommet[256][0]=565;
sommet[256][1]=280;
sommet[257][0]=387;
sommet[257][1]=350;
sommet[258][0]=268;
sommet[258][1]=258;
sommet[259][0]=566;
sommet[259][1]=464;
sommet[260][0]=113;
sommet[260][1]=380;
sommet[261][0]=58;
sommet[261][1]=214;
sommet[262][0]=397;
sommet[262][1]=378;
sommet[263][0]=334;
sommet[263][1]=210;
sommet[264][0]=418;
sommet[264][1]=350;
sommet[265][0]=550;
sommet[265][1]=342;
sommet[266][0]=42;
sommet[266][1]=168;
sommet[267][0]=589;
sommet[267][1]=428;
sommet[268][0]=33;
sommet[268][1]=266;
sommet[269][0]=130;
sommet[269][1]=338;
sommet[270][0]=122;
sommet[270][1]=400;
sommet[271][0]=583;
sommet[271][1]=252;
sommet[272][0]=67;
sommet[272][1]=314;
sommet[273][0]=565;
sommet[273][1]=192;
sommet[274][0]=40;
sommet[274][1]=310;
sommet[275][0]=105;
sommet[275][1]=454;
sommet[276][0]=329;
sommet[276][1]=206;
sommet[277][0]=56;
sommet[277][1]=310;
sommet[278][0]=424;
sommet[278][1]=330;
sommet[279][0]=365;
sommet[279][1]=236;
sommet[280][0]=127;
sommet[280][1]=404;
sommet[281][0]=414;
sommet[281][1]=390;
sommet[282][0]=109;
sommet[282][1]=448;
sommet[283][0]=584;
sommet[283][1]=294;
sommet[284][0]=561;
sommet[284][1]=462;
sommet[285][0]=431;
sommet[285][1]=316;
sommet[286][0]=246;
sommet[286][1]=196;
sommet[287][0]=371;
sommet[287][1]=282;
sommet[288][0]=44;
sommet[288][1]=310;
sommet[289][0]=385;
sommet[289][1]=178;
sommet[290][0]=268;
sommet[290][1]=152;
sommet[291][0]=94;
sommet[291][1]=316;
sommet[292][0]=119;
sommet[292][1]=350;
sommet[293][0]=399;
sommet[293][1]=166;
sommet[294][0]=262;
sommet[294][1]=352;
sommet[295][0]=108;
sommet[295][1]=160;
sommet[296][0]=126;
sommet[296][1]=454;
sommet[297][0]=118;
sommet[297][1]=360;
sommet[298][0]=323;
sommet[298][1]=168;
sommet[299][0]=268;
sommet[299][1]=446;
sommet[300][0]=73;
sommet[300][1]=220;
sommet[301][0]=309;
sommet[301][1]=238;
sommet[302][0]=194;
sommet[302][1]=328;
sommet[303][0]=267;
sommet[303][1]=282;
sommet[304][0]=565;
sommet[304][1]=136;
sommet[305][0]=555;
sommet[305][1]=418;
sommet[306][0]=36;
sommet[306][1]=434;
sommet[307][0]=313;
sommet[307][1]=182;
sommet[308][0]=562;
sommet[308][1]=408;
sommet[309][0]=327;
sommet[309][1]=390;
sommet[310][0]=227;
sommet[310][1]=212;
sommet[311][0]=125;
sommet[311][1]=334;
sommet[312][0]=576;
sommet[312][1]=330;
sommet[313][0]=579;
sommet[313][1]=278;
sommet[314][0]=199;
sommet[314][1]=254;
sommet[315][0]=230;
sommet[315][1]=200;
sommet[316][0]=336;
sommet[316][1]=454;
sommet[317][0]=204;
sommet[317][1]=198;
sommet[318][0]=61;
sommet[318][1]=220;
sommet[319][0]=95;
sommet[319][1]=234;
sommet[320][0]=429;
sommet[320][1]=246;
sommet[321][0]=289;
sommet[321][1]=406;
sommet[322][0]=385;
sommet[322][1]=158;
sommet[323][0]=192;
sommet[323][1]=332;
sommet[324][0]=79;
sommet[324][1]=330;
sommet[325][0]=196;
sommet[325][1]=158;
sommet[326][0]=230;
sommet[326][1]=316;
sommet[327][0]=325;
sommet[327][1]=364;
sommet[328][0]=99;
sommet[328][1]=368;
sommet[329][0]=276;
sommet[329][1]=374;
sommet[330][0]=344;
sommet[330][1]=302;
sommet[331][0]=292;
sommet[331][1]=458;
sommet[332][0]=189;
sommet[332][1]=206;
sommet[333][0]=307;
sommet[333][1]=440;
sommet[334][0]=338;
sommet[334][1]=310;
sommet[335][0]=559;
sommet[335][1]=416;
sommet[336][0]=39;
sommet[336][1]=326;
sommet[337][0]=141;
sommet[337][1]=246;
sommet[338][0]=184;
sommet[338][1]=180;
sommet[339][0]=339;
sommet[339][1]=390;
sommet[340][0]=564;
sommet[340][1]=278;
sommet[341][0]=258;
sommet[341][1]=204;
sommet[342][0]=139;
sommet[342][1]=186;
sommet[343][0]=345;
sommet[343][1]=180;
sommet[344][0]=368;
sommet[344][1]=314;
sommet[345][0]=116;
sommet[345][1]=232;
sommet[346][0]=262;
sommet[346][1]=408;
sommet[347][0]=430;
sommet[347][1]=246;
sommet[348][0]=344;
sommet[348][1]=298;
sommet[349][0]=216;
sommet[349][1]=338;
sommet[350][0]=118;
sommet[350][1]=450;
sommet[351][0]=89;
sommet[351][1]=306;
sommet[352][0]=372;
sommet[352][1]=278;
sommet[353][0]=158;
sommet[353][1]=204;
sommet[354][0]=59;
sommet[354][1]=412;
sommet[355][0]=309;
sommet[355][1]=272;
sommet[356][0]=226;
sommet[356][1]=336;
sommet[357][0]=425;
sommet[357][1]=300;
sommet[358][0]=129;
sommet[358][1]=230;
sommet[359][0]=126;
sommet[359][1]=400;
sommet[360][0]=399;
sommet[360][1]=326;
sommet[361][0]=274;
sommet[361][1]=146;
sommet[362][0]=64;
sommet[362][1]=466;
sommet[363][0]=112;
sommet[363][1]=364;
sommet[364][0]=212;
sommet[364][1]=274;
sommet[365][0]=571;
sommet[365][1]=366;
sommet[366][0]=27;
sommet[366][1]=350;
sommet[367][0]=577;
sommet[367][1]=402;
sommet[368][0]=311;
sommet[368][1]=440;
sommet[369][0]=291;
sommet[369][1]=278;
sommet[370][0]=101;
sommet[370][1]=212;
sommet[371][0]=268;
sommet[371][1]=324;
sommet[372][0]=141;
sommet[372][1]=160;
sommet[373][0]=126;
sommet[373][1]=300;
sommet[374][0]=424;
sommet[374][1]=248;
sommet[375][0]=269;
sommet[375][1]=400;
sommet[376][0]=114;
sommet[376][1]=314;
sommet[377][0]=106;
sommet[377][1]=198;
sommet[378][0]=413;
sommet[378][1]=150;
sommet[379][0]=333;
sommet[379][1]=238;
sommet[380][0]=216;
sommet[380][1]=294;
sommet[381][0]=77;
sommet[381][1]=266;
sommet[382][0]=272;
sommet[382][1]=438;
sommet[383][0]=258;
sommet[383][1]=388;
sommet[384][0]=317;
sommet[384][1]=436;
sommet[385][0]=34;
sommet[385][1]=304;
sommet[386][0]=201;
sommet[386][1]=246;
sommet[387][0]=200;
sommet[387][1]=344;
sommet[388][0]=47;
sommet[388][1]=218;
sommet[389][0]=115;
sommet[389][1]=444;
sommet[390][0]=119;
sommet[390][1]=436;
sommet[391][0]=127;
sommet[391][1]=234;
sommet[392][0]=29;
sommet[392][1]=202;
sommet[393][0]=284;
sommet[393][1]=298;
sommet[394][0]=332;
sommet[394][1]=212;
sommet[395][0]=372;
sommet[395][1]=222;
sommet[396][0]=61;
sommet[396][1]=350;
sommet[397][0]=263;
sommet[397][1]=326;
sommet[398][0]=189;
sommet[398][1]=152;
sommet[399][0]=319;
sommet[399][1]=292;
sommet[400][0]=283;
sommet[400][1]=272;
sommet[401][0]=138;
sommet[401][1]=344;
sommet[402][0]=141;
sommet[402][1]=366;
sommet[403][0]=132;
sommet[403][1]=340;
sommet[404][0]=69;
sommet[404][1]=280;
sommet[405][0]=388;
sommet[405][1]=256;
sommet[406][0]=222;
sommet[406][1]=264;
sommet[407][0]=116;
sommet[407][1]=328;
sommet[408][0]=368;
sommet[408][1]=218;
sommet[409][0]=430;
sommet[409][1]=176;
sommet[410][0]=401;
sommet[410][1]=352;
sommet[411][0]=103;
sommet[411][1]=434;
sommet[412][0]=74;
sommet[412][1]=318;
sommet[413][0]=399;
sommet[413][1]=200;
sommet[414][0]=346;
sommet[414][1]=190;
sommet[415][0]=291;
sommet[415][1]=236;
sommet[416][0]=239;
sommet[416][1]=214;
sommet[417][0]=102;
sommet[417][1]=388;
sommet[418][0]=257;
sommet[418][1]=270;
sommet[419][0]=396;
sommet[419][1]=368;
sommet[420][0]=36;
sommet[420][1]=224;
sommet[421][0]=565;
sommet[421][1]=446;
sommet[422][0]=587;
sommet[422][1]=386;
sommet[423][0]=62;
sommet[423][1]=346;
sommet[424][0]=260;
sommet[424][1]=154;
sommet[425][0]=339;
sommet[425][1]=262;
sommet[426][0]=238;
sommet[426][1]=182;
sommet[427][0]=366;
sommet[427][1]=194;
sommet[428][0]=296;
sommet[428][1]=206;
sommet[429][0]=322;
sommet[429][1]=468;
sommet[430][0]=383;
sommet[430][1]=194;
sommet[431][0]=436;
sommet[431][1]=272;
sommet[432][0]=79;
sommet[432][1]=276;
sommet[433][0]=157;
sommet[433][1]=340;
sommet[434][0]=131;
sommet[434][1]=354;
sommet[435][0]=66;
sommet[435][1]=210;
sommet[436][0]=121;
sommet[436][1]=456;
sommet[437][0]=28;
sommet[437][1]=196;
sommet[438][0]=551;
sommet[438][1]=308;
sommet[439][0]=439;
sommet[439][1]=202;
sommet[440][0]=574;
sommet[440][1]=446;
sommet[441][0]=583;
sommet[441][1]=330;
sommet[442][0]=271;
sommet[442][1]=270;
sommet[443][0]=132;
sommet[443][1]=214;
sommet[444][0]=167;
sommet[444][1]=322;
sommet[445][0]=261;
sommet[445][1]=460;
sommet[446][0]=215;
sommet[446][1]=156;
sommet[447][0]=64;
sommet[447][1]=444;
sommet[448][0]=113;
sommet[448][1]=360;
sommet[449][0]=315;
sommet[449][1]=282;
sommet[450][0]=261;
sommet[450][1]=310;
sommet[451][0]=134;
sommet[451][1]=252;
sommet[452][0]=68;
sommet[452][1]=434;
sommet[453][0]=116;
sommet[453][1]=232;
sommet[454][0]=366;
sommet[454][1]=244;
sommet[455][0]=216;
sommet[455][1]=358;
sommet[456][0]=88;
sommet[456][1]=296;
sommet[457][0]=182;
sommet[457][1]=236;
sommet[458][0]=419;
sommet[458][1]=200;
sommet[459][0]=324;
sommet[459][1]=452;
sommet[460][0]=164;
sommet[460][1]=344;
sommet[461][0]=429;
sommet[461][1]=312;
sommet[462][0]=43;
sommet[462][1]=200;
sommet[463][0]=577;
sommet[463][1]=446;
sommet[464][0]=378;
sommet[464][1]=202;
sommet[465][0]=98;
sommet[465][1]=398;
sommet[466][0]=53;
sommet[466][1]=208;
sommet[467][0]=44;
sommet[467][1]=282;
sommet[468][0]=318;
sommet[468][1]=224;
sommet[469][0]=34;
sommet[469][1]=414;
sommet[470][0]=258;
sommet[470][1]=266;
sommet[471][0]=266;
sommet[471][1]=284;
sommet[472][0]=345;
sommet[472][1]=184;
sommet[473][0]=112;
sommet[473][1]=246;
sommet[474][0]=430;
sommet[474][1]=274;
sommet[475][0]=35;
sommet[475][1]=388;
sommet[476][0]=28;
sommet[476][1]=154;
sommet[477][0]=136;
sommet[477][1]=314;
sommet[478][0]=405;
sommet[478][1]=336;
sommet[479][0]=311;
sommet[479][1]=456;
sommet[480][0]=62;
sommet[480][1]=178;
sommet[481][0]=581;
sommet[481][1]=250;
sommet[482][0]=65;
sommet[482][1]=224;
sommet[483][0]=172;
sommet[483][1]=288;
sommet[484][0]=127;
sommet[484][1]=340;
sommet[485][0]=106;
sommet[485][1]=202;
sommet[486][0]=281;
sommet[486][1]=160;
sommet[487][0]=135;
sommet[487][1]=224;
sommet[488][0]=260;
sommet[488][1]=312;
sommet[489][0]=339;
sommet[489][1]=446;
sommet[490][0]=214;
sommet[490][1]=274;
sommet[491][0]=48;
sommet[491][1]=196;
sommet[492][0]=330;
sommet[492][1]=248;
sommet[493][0]=339;
sommet[493][1]=288;
sommet[494][0]=198;
sommet[494][1]=178;
sommet[495][0]=294;
sommet[495][1]=446;
sommet[496][0]=195;
sommet[496][1]=168;
sommet[497][0]=315;
sommet[497][1]=374;
sommet[498][0]=566;
sommet[498][1]=290;
sommet[499][0]=203;
sommet[499][1]=382;
sommet[500][0]=235;
sommet[500][1]=168;
sommet[501][0]=448;
sommet[501][1]=292;
sommet[502][0]=295;
sommet[502][1]=164;
sommet[503][0]=404;
sommet[503][1]=188;
sommet[504][0]=175;
sommet[504][1]=186;
sommet[505][0]=333;
sommet[505][1]=202;
sommet[506][0]=287;
sommet[506][1]=434;
sommet[507][0]=341;
sommet[507][1]=330;
sommet[508][0]=329;
sommet[508][1]=226;
sommet[509][0]=100;
sommet[509][1]=360;
sommet[510][0]=28;
sommet[510][1]=356;
sommet[511][0]=445;
sommet[511][1]=316;
sommet[512][0]=222;
sommet[512][1]=334;
sommet[513][0]=54;
sommet[513][1]=146;
sommet[514][0]=377;
sommet[514][1]=250;
sommet[515][0]=327;
sommet[515][1]=404;
sommet[516][0]=57;
sommet[516][1]=258;
sommet[517][0]=190;
sommet[517][1]=386;
sommet[518][0]=293;
sommet[518][1]=296;
sommet[519][0]=590;
sommet[519][1]=428;
sommet[520][0]=366;
sommet[520][1]=244;
sommet[521][0]=57;
sommet[521][1]=392;
sommet[522][0]=440;
sommet[522][1]=234;
sommet[523][0]=556;
sommet[523][1]=304;
sommet[524][0]=277;
sommet[524][1]=254;
sommet[525][0]=327;
sommet[525][1]=186;
sommet[526][0]=283;
sommet[526][1]=328;
sommet[527][0]=78;
sommet[527][1]=274;
sommet[528][0]=169;
sommet[528][1]=174;
sommet[529][0]=68;
sommet[529][1]=422;
sommet[530][0]=585;
sommet[530][1]=336;
sommet[531][0]=125;
sommet[531][1]=240;
sommet[532][0]=62;
sommet[532][1]=324;
sommet[533][0]=75;
sommet[533][1]=294;
sommet[534][0]=100;
sommet[534][1]=386;
sommet[535][0]=582;
sommet[535][1]=350;
sommet[536][0]=273;
sommet[536][1]=166;
sommet[537][0]=325;
sommet[537][1]=164;
sommet[538][0]=91;
sommet[538][1]=264;
sommet[539][0]=36;
sommet[539][1]=468;
sommet[540][0]=445;
sommet[540][1]=226;
sommet[541][0]=278;
sommet[541][1]=244;
sommet[542][0]=451;
sommet[542][1]=260;
sommet[543][0]=339;
sommet[543][1]=188;
sommet[544][0]=186;
sommet[544][1]=346;
sommet[545][0]=119;
sommet[545][1]=276;
sommet[546][0]=226;
sommet[546][1]=164;
sommet[547][0]=362;
sommet[547][1]=260;
sommet[548][0]=137;
sommet[548][1]=338;
sommet[549][0]=279;
sommet[549][1]=334;
sommet[550][0]=81;
sommet[550][1]=262;
sommet[551][0]=407;
sommet[551][1]=186;
sommet[552][0]=313;
sommet[552][1]=312;
sommet[553][0]=433;
sommet[553][1]=350;
sommet[554][0]=550;
sommet[554][1]=268;
sommet[555][0]=82;
sommet[555][1]=280;
sommet[556][0]=200;
sommet[556][1]=174;
sommet[557][0]=108;
sommet[557][1]=446;
sommet[558][0]=342;
sommet[558][1]=282;
sommet[559][0]=441;
sommet[559][1]=194;
sommet[560][0]=325;
sommet[560][1]=242;
sommet[561][0]=323;
sommet[561][1]=444;
sommet[562][0]=43;
sommet[562][1]=354;
sommet[563][0]=441;
sommet[563][1]=276;
sommet[564][0]=111;
sommet[564][1]=456;
sommet[565][0]=401;
sommet[565][1]=378;
sommet[566][0]=324;
sommet[566][1]=350;
sommet[567][0]=121;
sommet[567][1]=460;
sommet[568][0]=221;
sommet[568][1]=168;
sommet[569][0]=331;
sommet[569][1]=346;
sommet[570][0]=584;
sommet[570][1]=466;
sommet[571][0]=421;
sommet[571][1]=314;
sommet[572][0]=101;
sommet[572][1]=350;
sommet[573][0]=177;
sommet[573][1]=270;
sommet[574][0]=561;
sommet[574][1]=440;
sommet[575][0]=406;
sommet[575][1]=338;
sommet[576][0]=170;
sommet[576][1]=338;
sommet[577][0]=552;
sommet[577][1]=290;
sommet[578][0]=33;
sommet[578][1]=360;
sommet[579][0]=279;
sommet[579][1]=156;
sommet[580][0]=347;
sommet[580][1]=404;
sommet[581][0]=432;
sommet[581][1]=272;
sommet[582][0]=277;
sommet[582][1]=304;
sommet[583][0]=131;
sommet[583][1]=454;
sommet[584][0]=585;
sommet[584][1]=402;
sommet[585][0]=93;
sommet[585][1]=330;
sommet[586][0]=581;
sommet[586][1]=404;
sommet[587][0]=233;
sommet[587][1]=294;
sommet[588][0]=274;
sommet[588][1]=144;
sommet[589][0]=552;
sommet[589][1]=288;
sommet[590][0]=322;
sommet[590][1]=148;
sommet[591][0]=54;
sommet[591][1]=184;
sommet[592][0]=558;
sommet[592][1]=252;
sommet[593][0]=102;
sommet[593][1]=420;
sommet[594][0]=413;
sommet[594][1]=206;
sommet[595][0]=164;
sommet[595][1]=332;
sommet[596][0]=39;
sommet[596][1]=388;
sommet[597][0]=310;
sommet[597][1]=242;
sommet[598][0]=180;
sommet[598][1]=256;
sommet[599][0]=439;
sommet[599][1]=312;
sommet[600][0]=89;
sommet[600][1]=304;
sommet[601][0]=425;
sommet[601][1]=314;
sommet[602][0]=403;
sommet[602][1]=358;
sommet[603][0]=554;
sommet[603][1]=466;
sommet[604][0]=439;
sommet[604][1]=220;
sommet[605][0]=197;
sommet[605][1]=274;
sommet[606][0]=313;
sommet[606][1]=332;
sommet[607][0]=426;
sommet[607][1]=360;
sommet[608][0]=386;
sommet[608][1]=278;
sommet[609][0]=98;
sommet[609][1]=356;
sommet[610][0]=446;
sommet[610][1]=256;
sommet[611][0]=200;
sommet[611][1]=208;
sommet[612][0]=117;
sommet[612][1]=282;
sommet[613][0]=288;
sommet[613][1]=282;
sommet[614][0]=222;
sommet[614][1]=370;
sommet[615][0]=398;
sommet[615][1]=276;
sommet[616][0]=136;
sommet[616][1]=412;
sommet[617][0]=429;
sommet[617][1]=282;
sommet[618][0]=385;
sommet[618][1]=332;
sommet[619][0]=230;
sommet[619][1]=316;
sommet[620][0]=238;
sommet[620][1]=226;
sommet[621][0]=265;
sommet[621][1]=316;
sommet[622][0]=104;
sommet[622][1]=438;
sommet[623][0]=125;
sommet[623][1]=240;
sommet[624][0]=326;
sommet[624][1]=254;
sommet[625][0]=63;
sommet[625][1]=336;
sommet[626][0]=391;
sommet[626][1]=306;
sommet[627][0]=423;
sommet[627][1]=330;
sommet[628][0]=168;
sommet[628][1]=194;
sommet[629][0]=214;
sommet[629][1]=282;
sommet[630][0]=198;
sommet[630][1]=332;
sommet[631][0]=350;
sommet[631][1]=174;
sommet[632][0]=336;
sommet[632][1]=284;
sommet[633][0]=161;
sommet[633][1]=246;
sommet[634][0]=221;
sommet[634][1]=164;
sommet[635][0]=326;
sommet[635][1]=458;
sommet[636][0]=420;
sommet[636][1]=150;
sommet[637][0]=564;
sommet[637][1]=198;
sommet[638][0]=397;
sommet[638][1]=172;
sommet[639][0]=415;
sommet[639][1]=196;
sommet[640][0]=100;
sommet[640][1]=450;
sommet[641][0]=104;
sommet[641][1]=360;
sommet[642][0]=260;
sommet[642][1]=418;
sommet[643][0]=38;
sommet[643][1]=326;
sommet[644][0]=279;
sommet[644][1]=422;
sommet[645][0]=396;
sommet[645][1]=362;
sommet[646][0]=429;
sommet[646][1]=172;
sommet[647][0]=65;
sommet[647][1]=300;
sommet[648][0]=556;
sommet[648][1]=312;
sommet[649][0]=293;
sommet[649][1]=252;
sommet[650][0]=572;
sommet[650][1]=466;
sommet[651][0]=258;
sommet[651][1]=444;
sommet[652][0]=334;
sommet[652][1]=460;
sommet[653][0]=108;
sommet[653][1]=188;
sommet[654][0]=113;
sommet[654][1]=412;
sommet[655][0]=214;
sommet[655][1]=360;
sommet[656][0]=318;
sommet[656][1]=440;
sommet[657][0]=572;
sommet[657][1]=350;
sommet[658][0]=562;
sommet[658][1]=252;
sommet[659][0]=402;
sommet[659][1]=210;
sommet[660][0]=69;
sommet[660][1]=248;
sommet[661][0]=446;
sommet[661][1]=230;
sommet[662][0]=333;
sommet[662][1]=454;
sommet[663][0]=179;
sommet[663][1]=252;
sommet[664][0]=275;
sommet[664][1]=158;
sommet[665][0]=565;
sommet[665][1]=430;
sommet[666][0]=160;
sommet[666][1]=196;
sommet[667][0]=256;
sommet[667][1]=332;
sommet[668][0]=277;
sommet[668][1]=306;
sommet[669][0]=268;
sommet[669][1]=150;
sommet[670][0]=310;
sommet[670][1]=414;
sommet[671][0]=405;
sommet[671][1]=186;
sommet[672][0]=447;
sommet[672][1]=268;
sommet[673][0]=228;
sommet[673][1]=336;
sommet[674][0]=256;
sommet[674][1]=216;
sommet[675][0]=327;
sommet[675][1]=170;
sommet[676][0]=120;
sommet[676][1]=176;
sommet[677][0]=167;
sommet[677][1]=248;
sommet[678][0]=96;
sommet[678][1]=410;
sommet[679][0]=127;
sommet[679][1]=396;
sommet[680][0]=259;
sommet[680][1]=314;
sommet[681][0]=294;
sommet[681][1]=364;
sommet[682][0]=434;
sommet[682][1]=332;
sommet[683][0]=263;
sommet[683][1]=250;
sommet[684][0]=41;
sommet[684][1]=168;
sommet[685][0]=365;
sommet[685][1]=218;
sommet[686][0]=217;
sommet[686][1]=350;
sommet[687][0]=313;
sommet[687][1]=396;
sommet[688][0]=257;
sommet[688][1]=330;
sommet[689][0]=264;
sommet[689][1]=314;
sommet[690][0]=327;
sommet[690][1]=224;
sommet[691][0]=95;
sommet[691][1]=196;
sommet[692][0]=291;
sommet[692][1]=238;
sommet[693][0]=318;
sommet[693][1]=372;
sommet[694][0]=574;
sommet[694][1]=376;
sommet[695][0]=278;
sommet[695][1]=200;
sommet[696][0]=101;
sommet[696][1]=194;
sommet[697][0]=440;
sommet[697][1]=308;
sommet[698][0]=571;
sommet[698][1]=422;
sommet[699][0]=336;
sommet[699][1]=398;
sommet[700][0]=139;
sommet[700][1]=228;
sommet[701][0]=124;
sommet[701][1]=248;
sommet[702][0]=72;
sommet[702][1]=328;
sommet[703][0]=392;
sommet[703][1]=208;
sommet[704][0]=440;
sommet[704][1]=330;
sommet[705][0]=580;
sommet[705][1]=372;
sommet[706][0]=419;
sommet[706][1]=296;
sommet[707][0]=291;
sommet[707][1]=182;
sommet[708][0]=311;
sommet[708][1]=308;
sommet[709][0]=453;
sommet[709][1]=282;
sommet[710][0]=54;
sommet[710][1]=274;
sommet[711][0]=130;
sommet[711][1]=270;
sommet[712][0]=583;
sommet[712][1]=248;
sommet[713][0]=179;
sommet[713][1]=200;
sommet[714][0]=112;
sommet[714][1]=230;
sommet[715][0]=435;
sommet[715][1]=216;
sommet[716][0]=318;
sommet[716][1]=384;
sommet[717][0]=141;
sommet[717][1]=294;
sommet[718][0]=214;
sommet[718][1]=162;
sommet[719][0]=278;
sommet[719][1]=344;
sommet[720][0]=310;
sommet[720][1]=442;
sommet[721][0]=104;
sommet[721][1]=398;
sommet[722][0]=587;
sommet[722][1]=262;
sommet[723][0]=284;
sommet[723][1]=174;
sommet[724][0]=102;
sommet[724][1]=182;
sommet[725][0]=391;
sommet[725][1]=218;
sommet[726][0]=28;
sommet[726][1]=358;
sommet[727][0]=119;
sommet[727][1]=452;
sommet[728][0]=238;
sommet[728][1]=218;
sommet[729][0]=574;
sommet[729][1]=468;
sommet[730][0]=40;
sommet[730][1]=214;
sommet[731][0]=218;
sommet[731][1]=346;
sommet[732][0]=280;
sommet[732][1]=236;
sommet[733][0]=293;
sommet[733][1]=424;
sommet[734][0]=445;
sommet[734][1]=212;
sommet[735][0]=161;
sommet[735][1]=296;
sommet[736][0]=199;
sommet[736][1]=276;
sommet[737][0]=31;
sommet[737][1]=372;
sommet[738][0]=83;
sommet[738][1]=306;
sommet[739][0]=276;
sommet[739][1]=290;
sommet[740][0]=426;
sommet[740][1]=174;
sommet[741][0]=287;
sommet[741][1]=144;
sommet[742][0]=37;
sommet[742][1]=154;
sommet[743][0]=131;
sommet[743][1]=250;
sommet[744][0]=73;
sommet[744][1]=406;
sommet[745][0]=86;
sommet[745][1]=274;
sommet[746][0]=54;
sommet[746][1]=284;
sommet[747][0]=561;
sommet[747][1]=356;
sommet[748][0]=347;
sommet[748][1]=398;
sommet[749][0]=101;
sommet[749][1]=320;
sommet[750][0]=31;
sommet[750][1]=334;
sommet[751][0]=410;
sommet[751][1]=318;
sommet[752][0]=564;
sommet[752][1]=378;
sommet[753][0]=312;
sommet[753][1]=370;
sommet[754][0]=153;
sommet[754][1]=230;
sommet[755][0]=423;
sommet[755][1]=154;
sommet[756][0]=267;
sommet[756][1]=282;
sommet[757][0]=113;
sommet[757][1]=424;
sommet[758][0]=216;
sommet[758][1]=290;
sommet[759][0]=433;
sommet[759][1]=246;
sommet[760][0]=572;
sommet[760][1]=392;
sommet[761][0]=57;
sommet[761][1]=152;
sommet[762][0]=33;
sommet[762][1]=322;
sommet[763][0]=224;
sommet[763][1]=332;
sommet[764][0]=158;
sommet[764][1]=320;
sommet[765][0]=283;
sommet[765][1]=276;
sommet[766][0]=388;
sommet[766][1]=172;
sommet[767][0]=417;
sommet[767][1]=350;
sommet[768][0]=59;
sommet[768][1]=432;
sommet[769][0]=164;
sommet[769][1]=236;
sommet[770][0]=43;
sommet[770][1]=150;
sommet[771][0]=71;
sommet[771][1]=278;
sommet[772][0]=341;
sommet[772][1]=456;
sommet[773][0]=556;
sommet[773][1]=322;
sommet[774][0]=257;
sommet[774][1]=336;
sommet[775][0]=262;
sommet[775][1]=376;
sommet[776][0]=362;
sommet[776][1]=266;
sommet[777][0]=365;
sommet[777][1]=198;
sommet[778][0]=198;
sommet[778][1]=382;
sommet[779][0]=392;
sommet[779][1]=300;
sommet[780][0]=566;
sommet[780][1]=284;
sommet[781][0]=106;
sommet[781][1]=364;
sommet[782][0]=571;
sommet[782][1]=202;
sommet[783][0]=165;
sommet[783][1]=266;
sommet[784][0]=222;
sommet[784][1]=206;
sommet[785][0]=256;
sommet[785][1]=170;
sommet[786][0]=163;
sommet[786][1]=318;
sommet[787][0]=276;
sommet[787][1]=282;
sommet[788][0]=124;
sommet[788][1]=432;
sommet[789][0]=276;
sommet[789][1]=264;
sommet[790][0]=127;
sommet[790][1]=320;
sommet[791][0]=341;
sommet[791][1]=224;
sommet[792][0]=40;
sommet[792][1]=268;
sommet[793][0]=379;
sommet[793][1]=310;
sommet[794][0]=199;
sommet[794][1]=290;
sommet[795][0]=430;
sommet[795][1]=324;
sommet[796][0]=139;
sommet[796][1]=222;
sommet[797][0]=160;
sommet[797][1]=350;
sommet[798][0]=350;
sommet[798][1]=212;
sommet[799][0]=228;
sommet[799][1]=220;
sommet[800][0]=123;
sommet[800][1]=244;
sommet[801][0]=435;
sommet[801][1]=344;
sommet[802][0]=153;
sommet[802][1]=316;
sommet[803][0]=350;
sommet[803][1]=356;
sommet[804][0]=113;
sommet[804][1]=180;
sommet[805][0]=108;
sommet[805][1]=236;
sommet[806][0]=112;
sommet[806][1]=234;
sommet[807][0]=175;
sommet[807][1]=368;
sommet[808][0]=72;
sommet[808][1]=312;
sommet[809][0]=38;
sommet[809][1]=242;
sommet[810][0]=399;
sommet[810][1]=244;
sommet[811][0]=93;
sommet[811][1]=292;
sommet[812][0]=42;
sommet[812][1]=376;
sommet[813][0]=579;
sommet[813][1]=142;
sommet[814][0]=31;
sommet[814][1]=378;
sommet[815][0]=128;
sommet[815][1]=228;
sommet[816][0]=140;
sommet[816][1]=262;
sommet[817][0]=264;
sommet[817][1]=442;
sommet[818][0]=435;
sommet[818][1]=348;
sommet[819][0]=442;
sommet[819][1]=290;
sommet[820][0]=53;
sommet[820][1]=184;
sommet[821][0]=219;
sommet[821][1]=364;
sommet[822][0]=432;
sommet[822][1]=360;
sommet[823][0]=55;
sommet[823][1]=436;
sommet[824][0]=318;
sommet[824][1]=422;
sommet[825][0]=555;
sommet[825][1]=424;
sommet[826][0]=583;
sommet[826][1]=332;
sommet[827][0]=234;
sommet[827][1]=286;
sommet[828][0]=317;
sommet[828][1]=248;
sommet[829][0]=118;
sommet[829][1]=356;
sommet[830][0]=112;
sommet[830][1]=168;
sommet[831][0]=69;
sommet[831][1]=330;
sommet[832][0]=270;
sommet[832][1]=204;
sommet[833][0]=67;
sommet[833][1]=370;
sommet[834][0]=83;
sommet[834][1]=266;
sommet[835][0]=122;
sommet[835][1]=272;
sommet[836][0]=557;
sommet[836][1]=170;
sommet[837][0]=189;
sommet[837][1]=358;
sommet[838][0]=167;
sommet[838][1]=366;
sommet[839][0]=168;
sommet[839][1]=270;
sommet[840][0]=121;
sommet[840][1]=440;
sommet[841][0]=579;
sommet[841][1]=382;
sommet[842][0]=256;
sommet[842][1]=174;
sommet[843][0]=124;
sommet[843][1]=348;
sommet[844][0]=273;
sommet[844][1]=360;
sommet[845][0]=175;
sommet[845][1]=284;
sommet[846][0]=428;
sommet[846][1]=240;
sommet[847][0]=42;
sommet[847][1]=444;
sommet[848][0]=233;
sommet[848][1]=180;
sommet[849][0]=269;
sommet[849][1]=196;
sommet[850][0]=264;
sommet[850][1]=266;
sommet[851][0]=330;
sommet[851][1]=426;
sommet[852][0]=34;
sommet[852][1]=252;
sommet[853][0]=229;
sommet[853][1]=176;
sommet[854][0]=193;
sommet[854][1]=392;
sommet[855][0]=331;
sommet[855][1]=468;
sommet[856][0]=221;
sommet[856][1]=320;
sommet[857][0]=110;
sommet[857][1]=434;
sommet[858][0]=434;
sommet[858][1]=300;
sommet[859][0]=571;
sommet[859][1]=290;
sommet[860][0]=228;
sommet[860][1]=328;
sommet[861][0]=392;
sommet[861][1]=348;
sommet[862][0]=428;
sommet[862][1]=314;
sommet[863][0]=104;
sommet[863][1]=258;
sommet[864][0]=287;
sommet[864][1]=250;
sommet[865][0]=100;
sommet[865][1]=156;
sommet[866][0]=220;
sommet[866][1]=264;
sommet[867][0]=381;
sommet[867][1]=262;
sommet[868][0]=239;
sommet[868][1]=190;
sommet[869][0]=166;
sommet[869][1]=268;
sommet[870][0]=179;
sommet[870][1]=290;
sommet[871][0]=576;
sommet[871][1]=410;
sommet[872][0]=99;
sommet[872][1]=248;
sommet[873][0]=317;
sommet[873][1]=468;
sommet[874][0]=285;
sommet[874][1]=202;
sommet[875][0]=171;
sommet[875][1]=262;
sommet[876][0]=341;
sommet[876][1]=258;
sommet[877][0]=49;
sommet[877][1]=214;
sommet[878][0]=227;
sommet[878][1]=196;
sommet[879][0]=329;
sommet[879][1]=410;
sommet[880][0]=581;
sommet[880][1]=380;
sommet[881][0]=589;
sommet[881][1]=446;
sommet[882][0]=272;
sommet[882][1]=170;
sommet[883][0]=564;
sommet[883][1]=252;
sommet[884][0]=377;
sommet[884][1]=316;
sommet[885][0]=111;
sommet[885][1]=196;
sommet[886][0]=65;
sommet[886][1]=232;
sommet[887][0]=339;
sommet[887][1]=280;
sommet[888][0]=66;
sommet[888][1]=160;
sommet[889][0]=323;
sommet[889][1]=414;
sommet[890][0]=336;
sommet[890][1]=226;
sommet[891][0]=273;
sommet[891][1]=214;
sommet[892][0]=574;
sommet[892][1]=150;
sommet[893][0]=399;
sommet[893][1]=294;
sommet[894][0]=417;
sommet[894][1]=156;
sommet[895][0]=228;
sommet[895][1]=300;
sommet[896][0]=332;
sommet[896][1]=306;
sommet[897][0]=395;
sommet[897][1]=220;
sommet[898][0]=283;
sommet[898][1]=354;
sommet[899][0]=388;
sommet[899][1]=260;
sommet[900][0]=73;
sommet[900][1]=364;
sommet[901][0]=105;
sommet[901][1]=272;
sommet[902][0]=115;
sommet[902][1]=250;
sommet[903][0]=551;
sommet[903][1]=258;
sommet[904][0]=219;
sommet[904][1]=150;
sommet[905][0]=558;
sommet[905][1]=306;
sommet[906][0]=185;
sommet[906][1]=216;
sommet[907][0]=97;
sommet[907][1]=292;
sommet[908][0]=39;
sommet[908][1]=322;
sommet[909][0]=390;
sommet[909][1]=300;
sommet[910][0]=65;
sommet[910][1]=178;
sommet[911][0]=99;
sommet[911][1]=278;
sommet[912][0]=130;
sommet[912][1]=424;
sommet[913][0]=578;
sommet[913][1]=160;
sommet[914][0]=330;
sommet[914][1]=220;
sommet[915][0]=449;
sommet[915][1]=290;
sommet[916][0]=185;
sommet[916][1]=252;
sommet[917][0]=40;
sommet[917][1]=272;
sommet[918][0]=565;
sommet[918][1]=290;
sommet[919][0]=204;
sommet[919][1]=174;
sommet[920][0]=73;
sommet[920][1]=204;
sommet[921][0]=580;
sommet[921][1]=388;
sommet[922][0]=585;
sommet[922][1]=160;
sommet[923][0]=342;
sommet[923][1]=280;
sommet[924][0]=30;
sommet[924][1]=288;
sommet[925][0]=225;
sommet[925][1]=202;
sommet[926][0]=140;
sommet[926][1]=220;
sommet[927][0]=422;
sommet[927][1]=250;
sommet[928][0]=335;
sommet[928][1]=296;
sommet[929][0]=283;
sommet[929][1]=464;
sommet[930][0]=135;
sommet[930][1]=368;
sommet[931][0]=281;
sommet[931][1]=164;
sommet[932][0]=198;
sommet[932][1]=146;
sommet[933][0]=289;
sommet[933][1]=318;
sommet[934][0]=187;
sommet[934][1]=328;
sommet[935][0]=62;
sommet[935][1]=322;
sommet[936][0]=398;
sommet[936][1]=252;
sommet[937][0]=413;
sommet[937][1]=364;
sommet[938][0]=572;
sommet[938][1]=402;
sommet[939][0]=237;
sommet[939][1]=310;
sommet[940][0]=102;
sommet[940][1]=316;
sommet[941][0]=288;
sommet[941][1]=280;
sommet[942][0]=197;
sommet[942][1]=272;
sommet[943][0]=210;
sommet[943][1]=350;
sommet[944][0]=54;
sommet[944][1]=416;
sommet[945][0]=190;
sommet[945][1]=370;
sommet[946][0]=408;
sommet[946][1]=356;
sommet[947][0]=280;
sommet[947][1]=282;
sommet[948][0]=427;
sommet[948][1]=336;
sommet[949][0]=277;
sommet[949][1]=154;
sommet[950][0]=572;
sommet[950][1]=298;
sommet[951][0]=194;
sommet[951][1]=352;
sommet[952][0]=557;
sommet[952][1]=318;
sommet[953][0]=318;
sommet[953][1]=210;
sommet[954][0]=45;
sommet[954][1]=184;
sommet[955][0]=208;
sommet[955][1]=326;
sommet[956][0]=586;
sommet[956][1]=454;
sommet[957][0]=555;
sommet[957][1]=260;
sommet[958][0]=224;
sommet[958][1]=216;
sommet[959][0]=319;
sommet[959][1]=386;
sommet[960][0]=581;
sommet[960][1]=180;
sommet[961][0]=583;
sommet[961][1]=366;
sommet[962][0]=28;
sommet[962][1]=200;
sommet[963][0]=574;
sommet[963][1]=210;
sommet[964][0]=336;
sommet[964][1]=214;
sommet[965][0]=167;
sommet[965][1]=314;
sommet[966][0]=338;
sommet[966][1]=384;
sommet[967][0]=430;
sommet[967][1]=228;
sommet[968][0]=405;
sommet[968][1]=380;
sommet[969][0]=560;
sommet[969][1]=476;
sommet[970][0]=177;
sommet[970][1]=264;
sommet[971][0]=436;
sommet[971][1]=342;
sommet[972][0]=552;
sommet[972][1]=308;
sommet[973][0]=260;
sommet[973][1]=278;
sommet[974][0]=114;
sommet[974][1]=206;
sommet[975][0]=275;
sommet[975][1]=412;
sommet[976][0]=262;
sommet[976][1]=274;
sommet[977][0]=202;
sommet[977][1]=194;
sommet[978][0]=238;
sommet[978][1]=208;
sommet[979][0]=46;
sommet[979][1]=400;
sommet[980][0]=242;
sommet[980][1]=192;
sommet[981][0]=56;
sommet[981][1]=366;
sommet[982][0]=157;
sommet[982][1]=200;
sommet[983][0]=323;
sommet[983][1]=334;
sommet[984][0]=120;
sommet[984][1]=404;
sommet[985][0]=372;
sommet[985][1]=228;
sommet[986][0]=380;
sommet[986][1]=168;
sommet[987][0]=290;
sommet[987][1]=336;
sommet[988][0]=158;
sommet[988][1]=220;
sommet[989][0]=228;
sommet[989][1]=284;
sommet[990][0]=575;
sommet[990][1]=340;
sommet[991][0]=412;
sommet[991][1]=342;
sommet[992][0]=288;
sommet[992][1]=208;
sommet[993][0]=113;
sommet[993][1]=356;
sommet[994][0]=389;
sommet[994][1]=178;
sommet[995][0]=442;
sommet[995][1]=214;
sommet[996][0]=275;
sommet[996][1]=156;
sommet[997][0]=109;
sommet[997][1]=296;
sommet[998][0]=108;
sommet[998][1]=234;
sommet[999][0]=210;
sommet[999][1]=356;
  int tri[n];
  triangle T[2*n];
  for(int i=0;i<n;i++){tri[i]=i;}
 
  AffichagePoints(n,sommet);
  TriLexicographique(n,sommet,n,tri);
  int t=TriangulIncrementale(n,sommet,tri,T);

  Delaunay(n,sommet,t,T);

  double rayon[t];//tableau contenant les rayons
  for(int i=0;i<t;i++){
    rayon[i]=RayonCercleCirconscrit(sommet[T[i].a],sommet[T[i].b],sommet[T[i].c]);
  }
  AffichageTriangulation(n,sommet,t,T);//affichage de Delaunay



//seuillage:

  triangle Taccepte[2*n];//les triangles qu'on affichera
  double alpha;  

while(1){
  cout << "Valeur de alpha: ";
  cin >> alpha;
  int t_acceptes=0;
  int indice=0;
  for(int i=0;i<t;i++){
    if(rayon[i]<alpha){//on accepte le triangle i
      t_acceptes++;
      Taccepte[indice].a=T[i].a; 
      Taccepte[indice].b=T[i].b; 
      Taccepte[indice].c=T[i].c;
      indice++;
    }
  }
  AffichageTriangulation(n,sommet,t_acceptes,Taccepte);
 }
}
