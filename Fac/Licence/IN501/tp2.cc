#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void pointrandom(int n, int point[][2]);
void distances(int n, int m, int point[][2], int edge[][3]);
void tri(int m, int edge[][3]);
void kruskal(int n, int m, int edge[][3], int arbre[][2]);
void AffichageGraphique(int n, int point[][2], int arbre[][2]);

int main(){
  int n;             //Le nombre de points.
  cout << "Entrer le nombre de points: ";
  cin >> n;
  int m=n*(n-1)/2;   // Le nombre de paires de points.
  int point[n][2];   // Les coordonnees des points dans le plan.
  int edge[m][3];    // Les paires de points et le carre de leur longueur.
  int arbre[n-1][2]; // Les aretes de lâ€™arbre de Kruskal.
  
  pointrandom(n,point);
//   cout << "Tableau point :"<<endl;
//   for(int i=0;i<n;i++)
//     cout<<"("<<point[i][0]<<","<<point[i][1]<<") ";
//   cout<<endl;
  
  distances(n,m,point,edge);
//   cout << "Tableau edge :"<<endl;
//   for(int i=0;i<m;i++)
//     cout<<"("<<edge[i][0]<<","<<edge[i][1]<<" : "<<edge[i][2]<<") ";
//   cout<<endl;
  
  tri(m,edge);
//   cout << "Tableau edge trié :"<<endl;
//   for(int i=0;i<m;i++)
//     cout<<"("<<edge[i][0]<<","<<edge[i][1]<<" : "<<edge[i][2]<<") ";
//   cout<<endl;
  
  kruskal(n,m,edge,arbre);
  AffichageGraphique(n,point,arbre);

  return 0;
}

void pointrandom(int n, int point[][2]) {
  srand(time(NULL));
  for(int i=0;i<n;i++) {
    point[i][0]=rand()%612;
    point[i][1]=rand()%792;
  }
}

void distances(int n, int m, int point[][2], int edge[][3]) {
  int k=0;
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      if(i<j) {
        edge[k][0]=i;
        edge[k][1]=j;
        edge[k][2]=(point[i][0]-point[j][0])*(point[i][0]-point[j][0])+(point[i][1]-point[j][1])*(point[i][1]-point[j][1]);
        k++;
      }
}

void tri(int m, int edge[][3]) {
  int fin=1; int aux[3];
  while(fin) {
    fin=0;
    for(int i=0;i<m-1;i++)
      if(edge[i][2]>edge[i+1][2]) {
	for(int j=0;j<3;j++) {
	  aux[j]=edge[i][j];
	  edge[i][j]=edge[i+1][j];
	  edge[i+1][j]=aux[j];
	}
	fin=1;
      }
  }
}

void kruskal(int n, int m, int edge[][3], int arbre[][2]) {
  int comp[n]; int k=0;
  for(int i=0 ; i<n ; i++)
    comp[i]=i;
  for(int i=0 ; i<m ; i++) {
    if(comp[edge[i][0]]!=comp[edge[i][1]]) {
      int aux=comp[edge[i][1]];
      arbre[k][0]=edge[i][0]; arbre[k][1]=edge[i][1];
      k++;
      for(int j=0 ; j<n ; j++)
        if(comp[j]==aux)
          comp[j]=comp[edge[i][0]];
    }
  }
}

void AffichageGraphique(int n, int point[][2], int arbre[][2]) {     // Cree le fichier Exemple.ps qui affiche
                                                                     // les points et l'arbre de Kruskal.
  ofstream output;                           
  output.open("arbreKruskal.ps",ios::out);
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
    output << point[arbre[i][0]][0] << " " << point[arbre[i][0]][1] << " moveto" << endl;
    output << point[arbre[i][1]][0] << " " << point[arbre[i][1]][1] << " lineto" << endl;
    output << "stroke" << endl;
    output << endl;
  }
}
