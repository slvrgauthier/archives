#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h> // pour cos() et sin()
#define PI 3.14159265

using namespace std;

int const n=100;

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

int ProduitScalaire(int p0[2], int p1[2], int p2[2],int p3[2]){
	//Renvoie le produit scalaire de p0p1,p2p3
	return (p1[0]-p0[0])*(p3[0]-p2[0])+(p1[1]-p0[1])*(p3[1]-p2[1]);
}

int Carre(int x){
	//Sans commentaire
	return x*x;
}

int NormeAuCarre(int p1[2],int p2[2]){
	//Calcul la norme au carre de p1p2
	return Carre(p1[1]-p2[1])+Carre(p1[0]-p2[0]);
}

bool EstADroite(int A[2], int B[2], int C[2]){
	//Renvoie vrai si C est strictement a droite de (AB) oriente de A vers B.
	if(det(A,B,A,C)>=0){return false;}
	else{return true;}
}

/*******************************************************************/
//Generation de sommets au hasard
/*******************************************************************/

void PointAuHasard(int n,int sommet[][2]){
	//Tire n points au hasard uniformement repartis dans un disque, leurs coordonnees sont
	//stockees dans sommet[][2]
	srand(time(NULL));
	for(int i=0;i<n;i++){
		int r= rand()%250;
		int theta= rand() %360;
		sommet[i][0]=(int) (300 +r*cos( (float)theta /180.0 * PI ));
		sommet[i][1]=(int) (400 + r*sin((float)theta /180.0 * PI ));
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
		output << sommet[i][0]+2 << " " << sommet[i][1] << " moveto" <<endl;
		output << "/Courier findfont 15 scalefont setfont" << endl;
		output << "("<< i << ")" << " show" << endl;
		output << "stroke" << endl;
		output << endl;
	}
	output << endl;
	output.close();
}

void AffichageTriangulation(int n, int sommet[][2], int t, triangle T[]){
	//Affichage des n points du plan dont les coordonnees sont dans sommet[][2] et d'une triangulation
	//en t triangles stockes dans T, tableau de taille t.
	//Produit en sortie un fichier Triangulation.ps
	ofstream output;
	output.open("Triangulation.ps");//
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


/************************************************************************/
//Calcul de la triangulation
/************************************************************************/




void TriLexicographique(int n, int sommet[][2], int t, int Tri[]){
	//En entree, Tri, tableau de taille n, contient les indices des sommets a trier, a l'initialisation
	//Tri[i]=i, et t est la taille de Tri, donc t=n pour le premier appel.
	//En sorti, Tri contient les indices des sommets tries par ordre lexicographique croissant. 
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
						if(d>1){TriLexicographique(n,sommet,d,Td);}
						if(t-d-1>1){TriLexicographique(n,sommet,t-d-1,Tg);}
						//Fusion dans Tri
						for(int i=0;i<t;i++){
							if(i<t-d-1){Tri[i]=Tg[i];}
							if(i==t-d-1){Tri[i]=pivot;}
							if(i>t-d-1){Tri[i]=Td[i-t+d];}
						}
	}
}


int TriangulIncrementale(int n, int sommet[][2], int tri[], triangle T[]){
	//En sortie, T doit contenir la liste des triangles de la triangulation incrementale.
	//Le nombre de triangles crees est retournee.
	
	//Tableau gerant les sommets de l'enveloppe convexe courante
	//taille_envconv est la taille effective de l'enveloppe convexe
	//Le premier sommet de envconv est le dernier sommet insere, les autres suivent dans le sens direct et on remet le premier sommet en derniere position
	//Vous etes libre d'utiliser une autre structure de donnees qu'un (pauvre) tableau.
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
//main
/*******************************************************************/


int main(){
	int sommet[n][2];
	int tri[n];
	triangle T[3*n];
	for(int i=0;i<n+1;i++){tri[i]=i;}
	PointAuHasard(n,sommet);

sommet[0][0]=215;
sommet[0][1]=219;
sommet[1][0]=405;
sommet[1][1]=479;
sommet[2][0]=233;
sommet[2][1]=479;
sommet[3][0]=249;
sommet[3][1]=385;
sommet[4][0]=420;
sommet[4][1]=270;
sommet[5][0]=430;
sommet[5][1]=386;
sommet[6][0]=475;
sommet[6][1]=537;
sommet[7][0]=141;
sommet[7][1]=210;
sommet[8][0]=267;
sommet[8][1]=415;
sommet[9][0]=145;
sommet[9][1]=421;
sommet[10][0]=343;
sommet[10][1]=317;
sommet[11][0]=315;
sommet[11][1]=410;
sommet[12][0]=195;
sommet[12][1]=427;
sommet[13][0]=440;
sommet[13][1]=513;
sommet[14][0]=262;
sommet[14][1]=488;
sommet[15][0]=86;
sommet[15][1]=330;
sommet[16][0]=377;
sommet[16][1]=489;
sommet[17][0]=354;
sommet[17][1]=402;
sommet[18][0]=205;
sommet[18][1]=476;
sommet[19][0]=487;
sommet[19][1]=236;
sommet[20][0]=352;
sommet[20][1]=359;
sommet[21][0]=508;
sommet[21][1]=320;
sommet[22][0]=251;
sommet[22][1]=382;
sommet[23][0]=317;
sommet[23][1]=509;
sommet[24][0]=434;
sommet[24][1]=416;
sommet[25][0]=365;
sommet[25][1]=229;
sommet[26][0]=272;
sommet[26][1]=373;
sommet[27][0]=155;
sommet[27][1]=239;
sommet[28][0]=401;
sommet[28][1]=305;
sommet[29][0]=283;
sommet[29][1]=515;
sommet[30][0]=326;
sommet[30][1]=386;
sommet[31][0]=388;
sommet[31][1]=618;
sommet[32][0]=412;
sommet[32][1]=505;
sommet[33][0]=431;
sommet[33][1]=219;
sommet[34][0]=499;
sommet[34][1]=449;
sommet[35][0]=370;
sommet[35][1]=428;
sommet[36][0]=176;
sommet[36][1]=299;
sommet[37][0]=325;
sommet[37][1]=560;
sommet[38][0]=178;
sommet[38][1]=385;
sommet[39][0]=296;
sommet[39][1]=401;
sommet[40][0]=165;
sommet[40][1]=451;
sommet[41][0]=216;
sommet[41][1]=228;
sommet[42][0]=327;
sommet[42][1]=310;
sommet[43][0]=308;
sommet[43][1]=369;
sommet[44][0]=446;
sommet[44][1]=453;
sommet[45][0]=275;
sommet[45][1]=397;
sommet[46][0]=343;
sommet[46][1]=484;
sommet[47][0]=209;
sommet[47][1]=562;
sommet[48][0]=303;
sommet[48][1]=394;
sommet[49][0]=321;
sommet[49][1]=414;
sommet[50][0]=221;
sommet[50][1]=365;
sommet[51][0]=451;
sommet[51][1]=514;
sommet[52][0]=297;
sommet[52][1]=400;
sommet[53][0]=190;
sommet[53][1]=282;
sommet[54][0]=374;
sommet[54][1]=434;
sommet[55][0]=347;
sommet[55][1]=472;
sommet[56][0]=501;
sommet[56][1]=364;
sommet[57][0]=267;
sommet[57][1]=415;
sommet[58][0]=338;
sommet[58][1]=266;
sommet[59][0]=279;
sommet[59][1]=164;
sommet[60][0]=279;
sommet[60][1]=253;
sommet[61][0]=360;
sommet[61][1]=456;
sommet[62][0]=478;
sommet[62][1]=260;
sommet[63][0]=352;
sommet[63][1]=322;
sommet[64][0]=418;
sommet[64][1]=337;
sommet[65][0]=298;
sommet[65][1]=449;
sommet[66][0]=161;
sommet[66][1]=508;
sommet[67][0]=236;
sommet[67][1]=557;
sommet[68][0]=275;
sommet[68][1]=440;
sommet[69][0]=306;
sommet[69][1]=405;
sommet[70][0]=249;
sommet[70][1]=315;
sommet[71][0]=354;
sommet[71][1]=601;
sommet[72][0]=237;
sommet[72][1]=448;
sommet[73][0]=281;
sommet[73][1]=347;
sommet[74][0]=478;
sommet[74][1]=525;
sommet[75][0]=211;
sommet[75][1]=200;
sommet[76][0]=308;
sommet[76][1]=398;
sommet[77][0]=509;
sommet[77][1]=422;
sommet[78][0]=132;
sommet[78][1]=352;
sommet[79][0]=300;
sommet[79][1]=473;
sommet[80][0]=406;
sommet[80][1]=474;
sommet[81][0]=232;
sommet[81][1]=349;
sommet[82][0]=337;
sommet[82][1]=455;
sommet[83][0]=489;
sommet[83][1]=380;
sommet[84][0]=324;
sommet[84][1]=430;
sommet[85][0]=391;
sommet[85][1]=626;
sommet[86][0]=402;
sommet[86][1]=405;
sommet[87][0]=336;
sommet[87][1]=423;
sommet[88][0]=173;
sommet[88][1]=417;
sommet[89][0]=307;
sommet[89][1]=505;
sommet[90][0]=203;
sommet[90][1]=393;
sommet[91][0]=362;
sommet[91][1]=417;
sommet[92][0]=425;
sommet[92][1]=413;
sommet[93][0]=493;
sommet[93][1]=406;
sommet[94][0]=341;
sommet[94][1]=579;
sommet[95][0]=230;
sommet[95][1]=548;
sommet[96][0]=221;
sommet[96][1]=171;
sommet[97][0]=372;
sommet[97][1]=188;
sommet[98][0]=325;
sommet[98][1]=194;
sommet[99][0]=325;
sommet[99][1]=398;
	AffichagePoints(n,sommet);
	TriLexicographique(n,sommet,n,tri);
	int t=TriangulIncrementale(n,sommet,tri,T);
	AffichageTriangulation(n,sommet,t,T);
}

