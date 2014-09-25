#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#define INTERVALLE 100

void echanger(int tableau[], int a, int b);
void quickSort(int tableau[], int debut, int fin);

int main(int argc, char* argv[]){
  int n=10;
  if(argc>1)
   n=atoi(argv[1]);
  int* T=(int*)malloc(n*sizeof(int));
  srand(time(NULL));
  for(int i=0;i<n;i++)
    T[i]=rand()%INTERVALLE;
  quickSort(T,0,n-1);
  for(int i=0;i<n;i++)
    cout<<T[i]<<" ";
  cout<<endl;
  return 0;
}

void echanger(int tableau[], int a, int b){
    int temp = tableau[a];
    tableau[a] = tableau[b];
    tableau[b] = temp;
}

void quickSort(int tableau[], int debut, int fin){
    int gauche = debut-1;
    int droite = fin+1;
    const int pivot = tableau[debut];
    if(debut >= fin)
        return;
    while(1){
        do droite--; while(tableau[droite] > pivot);
        do gauche++; while(tableau[gauche] < pivot);

        if(gauche < droite)
            echanger(tableau, gauche, droite);
        else break;
    }
    quickSort(tableau, debut, droite);
    quickSort(tableau, droite+1, fin);
}
