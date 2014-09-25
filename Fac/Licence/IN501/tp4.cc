#include <limits.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

void voisins(int n, int dmax, int point[][2], vector<int> voisin[]);
void AffichageGraphe(int n, int point[][2], vector<int> voisin[]);
void dijkstra(int n, vector<int> voisin[], int point[][2], int pere[]);
int dmin(int n, int d[], int traite[]);
int construitarbre(int n, int arbre[][2], int pere[]);
void AffichageGraphique(int n, int k, int point[][2], int arbre[][2]);

void pointrandom(int n, int point[][2]) {
  srand(time(NULL));
  for(int i=0;i<n;i++) {
    point[i][0]=rand()%612;
    point[i][1]=rand()%792;
  }
}

int main(){
  int n;                   //Le nombre de points.
  int m;                   //Le nombre d aretes.
  cout << "Entrer le nombre de points: ";
  cin >> n;
  
  int dmax=50;             // La distance jusqu'a laquelle on relie deux points.
  
  vector<int> voisin[n];   // Les listes de voisins.          
  int point[n][2];         // Les coordonnees des points.
  
  int d[n];                // La distance a la racine.
  int arbre[n-1][2];       // Les aretes de l'arbre de Dijkstra.
  int pere[n];             // La relation de filiation de l'arbre de Dijkstra.
  for(int i=0;i<n;i++)
    pere[i]=-1;
  
  cout<<"Graphe en cours..."<<endl;
  pointrandom(n,point);
  voisins(n,dmax,point,voisin);
  cout<<"Graphe terminé"<<endl;
  cout<<"Affichage graphe en cours..."<<endl;
  AffichageGraphe(n,point,voisin);
  cout<<"Affichage graphe terminé"<<endl;
  cout<<"Arbre en cours..."<<endl;
  dijkstra(n,voisin,point,pere);
  int k=construitarbre(n,arbre,pere);
  cout<<"Arbre terminé"<<endl;
  cout<<"Affichage arbre en cours..."<<endl;
  AffichageGraphique(n,k,point,arbre);
  cout<<"Affichage arbre terminé"<<endl;
  
  return 0;
}

void voisins(int n, int dmax, int point[][2], vector<int> voisin[]) {
  for(int i=0;i<n;i++) {
    for(int j=1;j<n;j++) {
      if(i!=j && (sqrt((point[i][0]-point[j][0])*(point[i][0]-point[j][0])+(point[i][1]-point[j][1])*(point[i][1]-point[j][1])))<dmax)
	voisin[i].push_back(j);
    }
  }
}

void AffichageGraphe(int n, int point[][2], vector<int> voisin[]) {     // Cree le fichier Exemple.ps qui affiche
								    // les points et l'arbre de Kruskal.
  ofstream output;                           
  output.open("grapheDijkstra.ps",ios::out);
  output << "%!PS-Adobe-3.0" << endl;
  output << "%%BoundingBox: 0 0 612 792" << endl;
  output << endl;  
  for(int i=0;i<n;i++) {
    output << point[i][0] << " " << point[i][1] << " 3 0 360 arc" <<endl;
    output << "0 setgray" <<endl;
    output << "fill" <<endl;
    output << "stroke"<<endl;
    output << endl;
  }
  output << endl;
  for(int i=0;i<n-1;i++) {
    for(int j=0;j<voisin[i].size();j++) {
      output << point[i][0] << " " << point[i][1] << " moveto" << endl;
      output << point[voisin[i].at(j)][0] << " " << point[voisin[i].at(j)][1] << " lineto" << endl;
      output << "stroke" << endl;
      output << endl;
    }
  }
}

void dijkstra(int n, vector<int> voisin[], int point[][2], int pere[]) {
  int d[n], traite[n];
  for(int v=0;v<n;v++) {
    d[v]=INT_MAX;
    traite[v]=0;
  }
  pere[0]=d[0]=0;
  int x=dmin(n,d,traite);
  while(x!=-1) {
    traite[x]=1;
    for(int i=0;i<voisin[x].size();i++) {
      int y=voisin[x].at(i);
      if(traite[y]==0) {
	int lxy = sqrt((point[x][0]-point[y][0])*(point[x][0]-point[y][0])+(point[x][1]-point[y][1])*(point[x][1]-point[y][1]));
	if(d[y]>(d[x]+lxy)) {
	  d[y]=d[x]+lxy;
	  pere[y]=x;
	}
      }
    }
    x=dmin(n,d,traite);
  }
}

int dmin(int n, int d[], int traite[]) {
  int min=INT_MAX;
  int x=-1;
  for(int i=0;i<n;i++) {
    if(traite[i]==0 && d[i]<min) {
      min=d[i];
      x=i;
    }
  }
  return x;
}

int construitarbre(int n, int arbre[][2], int pere[]) {
  int k=0;
  for(int i=0;i<n;i++) {
    if(pere[i]!=-1) {
      arbre[i][0]=i;
      arbre[i][1]=pere[i];
      k++;
    }
  }
}

void AffichageGraphique(int n, int k, int point[][2], int arbre[][2]) {     // Cree le fichier Exemple.ps qui affiche
                                                                     // les points et l'arbre de Kruskal.
  ofstream output;                           
  output.open("arbreDijkstra.ps",ios::out);
  output << "%!PS-Adobe-3.0" << endl;
  output << "%%BoundingBox: 0 0 612 792" << endl;
  output << endl;  
  for(int i=0;i<n;i++) {
    output << point[i][0] << " " << point[i][1] << " 3 0 360 arc" <<endl;
    output << "0 setgray" <<endl;
    output << "fill" <<endl;
    output << "stroke"<<endl;
    output << endl;
  }
  output << endl;
  for(int i=0;i<k;i++) {
    output << point[arbre[i][0]][0] << " " << point[arbre[i][0]][1] << " moveto" << endl;
    output << point[arbre[i][1]][0] << " " << point[arbre[i][1]][1] << " lineto" << endl;
    output << "stroke" << endl;
    output << endl;
  }
}
