#include <iostream>
#include <fstream>
#include <math.h> // pour cos() et sin()
#define PI 3.14159265
#include <stdlib.h>


using namespace std;


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

int CentreCercleCirconscrit(int A[2], int B[2],int C[2], int O[3]){

  //Stocke dans O les coordonnees du centre du cercle circonscrit a A, B et C
    //Renvoie 1 si ces 3 points sont alignes, 0 sinon et fait le calcul dans ce cas

    if(det(A,B,A,C)==0){return 1;}
   int xa=A[0]; int ya=A[1];
   int xb=B[0]; int yb=B[1];
   int xc=C[0]; int yc=C[1];
   O[0]=(int)((float)((yc-yb)*(xb*xb+yb*yb-xa*xa-ya*ya)-(yb-ya)*(xc*xc+yc*yc-xb*xb-yb*yb))/(float)(2*det(A,B,B,C)));
   O[1]=(int)((float)((xc-xb)*(xb*xb+yb*yb-xa*xa-ya*ya)-(xb-xa)*(xc*xc+yc*yc-xb*xb-yb*yb))/(float)(2*det(B,C,A,B)));
   return 0;
}

int CentreCercleCirconscrit(int A[2], int B[2],int C[2], float O[3]){

  //Stocke dans O les coordonnees du centre du cercle circonscrit a A, B et C
    //Renvoie 1 si ces 3 points sont alignes, 0 sinon et fait le calcul dans ce cas

    if(det(A,B,A,C)==0){return 1;}
   int xa=A[0]; int ya=A[1];
   int xb=B[0]; int yb=B[1];
   int xc=C[0]; int yc=C[1];
   O[0]=((float)((yc-yb)*(xb*xb+yb*yb-xa*xa-ya*ya)-(yb-ya)*(xc*xc+yc*yc-xb*xb-yb*yb))/(float)(2*det(A,B,B,C)));
   O[1]=((float)((xc-xb)*(xb*xb+yb*yb-xa*xa-ya*ya)-(xb-xa)*(xc*xc+yc*yc-xb*xb-yb*yb))/(float)(2*det(B,C,A,B)));
   return 0;
}

float distance(float O[2], int p[2]) {
	return sqrt(pow(O[1]-p[1], 2)+pow(O[0]-p[0], 2));
}

void AffichageTestCercleCirconscrit(int sommet[4][2]){

  //Affiche les 4 points de sommet et le cercle circonscrit au trois premiers
    //Pour tester la fonction StrictementDansLeCercleCirconscrit

   ofstream output;
  output.open("Test.ps");//
  output << "%!PS-Adobe-3.0" << endl;
  output << endl;
  for(int i=0;i<4;i++){
    output << sommet[i][0] << " " << sommet[i][1] << " 2 0 360 arc"
           <<endl;
    output << "0 setgray" <<endl;
    output << "fill" <<endl;
    output << sommet[i][0]+2 << " " << sommet[i][1] << " moveto"
           <<endl;
    output << "/Courier findfont 15 scalefont setfont" << endl;
    output << "("<< i+1 << ")" << " show" << endl;
    output << "stroke" << endl;
    output << endl;
  }
  output << endl;
  int O[2];  //Centre du cercle circonscrit
  if(CentreCercleCirconscrit(sommet[0],sommet[1],sommet[2],O)==1){cout
    << "Points alignes" << endl; exit(1);}
  output << O[0] << " " << O[1] << " 2 0 360 arc" <<endl;
  output << "0 setgray" <<endl;
  output << "fill" <<endl;
  output << O[0]+2 << " " << O[1] << " moveto" <<endl;
  output << "/Courier findfont 15 scalefont setfont" << endl;
  output << "(O)" << " show" << endl;
  output << "stroke" << endl;
  output << endl;
  int r; //Rayon du cercle circonscrit
     r=(int)sqrt((double)NormeAuCarre(sommet[0],O));
     output << O[0] << " " << O[1] << " " << r << " 0 360 arc" <<endl;
     output << "0 setgray" <<endl;
     output << "stroke" << endl;
     output << endl;
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

void AffichageTriangulation(bool delo, int n, int sommet[][2], int t, triangle T[]){

  //Affichage des n points du plan dont les coordonnees sont dans sommet[][2] et 
  //d'une triangulation en t triangles stockes dans T, tableau de taille t.
  // si delo est a true, on ecrit Delaunay.ps, sinon Incremental.ps
   ofstream output;
   if(!delo){output.open("Incremental.ps");}else{
     output.open("Delaunay.ps");}

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
//Generation de sommets au hasard
/*******************************************************************/

void PointAuHasard(int n,int sommet[][2]){

  //Tire n points au hasard uniformement repartis dans un disque, leurs coordonnees sont
  //stockees dans sommet[][2]
  int graine=time(NULL);
  cout << "graine: "<< graine << endl;
  srand(graine);
  for(int i=0;i<n;i++){
    int r= rand()%250;
    int theta= rand() %360;
    sommet[i][0]=(int) (300 +r*cos( (float)theta /180.0 * PI ));
    sommet[i][1]=(int) (400 + r*sin((float)theta /180.0 * PI ));
  }
}

/*******************************************************************/
//Reperer un point par rapport au cercle circonscrit a un triangle
/*******************************************************************/

bool MemeCote(int A[2], int B[2], int C[2], int D[2]){

  //Renvoie vrai si C et D sont du meme cote de (AB).

  if((det(A,B,A,C)*det(A,B,A,D))>0){return true;}
  else{  return false;}
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

//---------------------------------------
bool StrictementDansLeCercleCirconscrit(int A[2], int B[2], int C[2], int D[2]){
  float O[2];
  if(CentreCercleCirconscrit(A,B,C,O) == 0) {
	  return (distance(O,A) > distance(O,D));
  }
  else {
	  return false;
  }
}


/************************************************************************/
//Calcul d'une premiere triangulation (algo incremental par ex)
/************************************************************************/


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

//----------------------------------------


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
	
	
	//Deroulement de l'algorithme
	for(int i=3;i<n;i++){//insertion de tri[i]
		if(sommet[tri[i]][0]==sommet[envconv[0]][0] && sommet[tri[i]][1]==sommet[envconv[0]][1]){
			continue;
		}//Si on a 2 points confondus, la maj de l'env conv peut bugger!
		
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

/*******************************************************************/
//Triangulation de Delaunay
/*******************************************************************/

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

//--------------------------------------------

int Delaunay(int n, int sommet[][2],int t, triangle T[]){
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
					cout<<"Flip "<<T[i].a<<" "<<T[i].b<<" "<<T[i].c<<" avec "<<T[voisin[i][j]].a<<" "<<T[voisin[i][j]].b<<" "<<T[voisin[i][j]].c<<endl;
					Flip(i,voisin[i][j],t,T,voisin);
					flag = 1;
					break;
				}
				else if(p2 != -1 && StrictementDansLeCercleCirconscrit(sommet[T[voisin[i][j]].a], sommet[T[voisin[i][j]].b], sommet[T[voisin[i][j]].c], sommet[p2])) {
					//cout<<tp<<" dans le circonscrit de "<<T[i].a<<" "<<T[i].b<<" "<<T[i].c<<endl;
					cout<<"Flip "<<T[i].a<<" "<<T[i].b<<" "<<T[i].c<<" avec "<<T[voisin[i][j]].a<<" "<<T[voisin[i][j]].b<<" "<<T[voisin[i][j]].c<<endl;
					Flip(voisin[i][j],i,t,T,voisin);
					flag = 1;
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
 
  int n=32;

  int sommet[n][2];
  int tri[n];
  triangle T[2*n];
  for(int i=0;i<n;i++){tri[i]=i;}
  PointAuHasard(n,sommet);

sommet[0][0]=100;
sommet[0][1]=100;
sommet[1][0]=100;
sommet[1][1]=500;
sommet[2][0]=120;
sommet[2][1]=300;
sommet[3][0]=140;
sommet[3][1]=100;
sommet[4][0]=140;
sommet[4][1]=500;
sommet[5][0]=160;
sommet[5][1]=300;
sommet[6][0]=180;
sommet[6][1]=100;
sommet[7][0]=180;
sommet[7][1]=500;
sommet[8][0]=200;
sommet[8][1]=300;
sommet[9][0]=220;
sommet[9][1]=100;
sommet[10][0]=220;
sommet[10][1]=500;
sommet[11][0]=240;
sommet[11][1]=300;
sommet[12][0]=260;
sommet[12][1]=100;
sommet[13][0]=260;
sommet[13][1]=500;
sommet[14][0]=280;
sommet[14][1]=300;
sommet[15][0]=300;
sommet[15][1]=100;
sommet[16][0]=300;
sommet[16][1]=500;
sommet[17][0]=320;
sommet[17][1]=300;
sommet[18][0]=340;
sommet[18][1]=100;
sommet[19][0]=340;
sommet[19][1]=500;
sommet[20][0]=360;
sommet[20][1]=300;
sommet[21][0]=380;
sommet[21][1]=100;
sommet[22][0]=380;
sommet[22][1]=500;
sommet[23][0]=400;
sommet[23][1]=300;
sommet[24][0]=420;
sommet[24][1]=100;
sommet[25][0]=420;
sommet[25][1]=500;
sommet[26][0]=440;
sommet[26][1]=300;
sommet[27][0]=460;
sommet[27][1]=100;
sommet[28][0]=460;
sommet[28][1]=500;
sommet[29][0]=480;
sommet[29][1]=300;
sommet[30][0]=500;
sommet[30][1]=100;
sommet[31][0]=500;
sommet[31][1]=500;
  AffichagePoints(n,sommet);
  TriLexicographique(n,sommet,n,tri);
  int t=TriangulIncrementale(n,sommet,tri,T);
  AffichageTriangulation(false,n,sommet,t,T);
  
  AffichageTestCercleCirconscrit(sommet);
  
  Delaunay(n,sommet,t,T);
  AffichageTriangulation(true,n,sommet,t,T);
  

}

