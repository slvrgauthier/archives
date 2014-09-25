#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

void graphRandom(int n, int m, int edge[][2]);
void composantes(int n, int m, int edge[][2], int comp[]);
void ecritureTailles(int n, int m, int comp[]);


int main() {
  int n;	//Nombre de sommets
  int m;	//Nombre d'aretes
  cout << "Entrez le nombre de sommets :";
  cin >> n;
  cout << "Entrez le nombre d'aretes :";
  cin >> m;
  int edge[m][2];	//Tableau des aretes
  int comp[n];		//comp[i] est le numero de la composante contenant i

//Test
  graphRandom(n,m,edge);
  cout << "Edge :" << endl;
  for(int i=0 ; i<m ; i++)
    cout << edge[i][0] << " ";
  cout << endl;
  for(int i=0 ; i<m ; i++)
    cout << edge[i][1] << " ";
  cout << endl;

  composantes(n,m,edge,comp);
  cout << "Comp :" << endl;
  for(int i=0 ; i<n ; i++)
    cout << comp[i] << " ";
  cout << endl;

  ecritureTailles(n,m,comp);

  return 0;
}

void graphRandom(int n, int m, int edge[][2]) {
  srand(time(NULL));
  for(int i=0 ; i<m ; i++) {
    edge[i][0] = rand()%n;
    edge[i][1] = rand()%n;
  }
}

void composantes(int n, int m, int edge[][2], int comp[]) {
  for(int i=0 ; i<n ; i++)
    comp[i]=i;
  for(int i=0 ; i<m ; i++) {
    if(comp[edge[i][0]]!=comp[edge[i][1]]) {
      int aux=comp[edge[i][1]];
      for(int j=0 ; j<n ; j++)
        if(comp[j]==aux)
          comp[j]=comp[edge[i][0]];
    }
  }
}

void ecritureTailles(int n, int m, int comp[]) {
  int tailles[n];
  for(int i=0 ; i<n ; i++)
    tailles[i]=0;
  for(int i=0 ; i<n ; i++)
    tailles[comp[i]]++;

  int nombre[n];
  for(int i=0 ; i<n ; i++)
    nombre[i]=0;
  for(int i=0 ; i<n ; i++)
    if(tailles[i]!=0)
      nombre[tailles[i]-1]++;

  cout << "Il y a " << nombre[0] << " points isoles." << endl;
  for(int i=1 ; i<n ; i++)
    if(nombre[i]!=0)
      cout << "Il y a " << nombre[i] << " composantes de taille " << i+1 << endl;
}

