#include <iostream>
#include <cmath>

#include "fonctionsMysterieuses.h"

int apuissanceb(int a, int b) {
// renvoie a puissance b
  if (b==0) return 1;
  if (b % 2 == 0) return apuissanceb(a * a, b / 2);
  return a * apuissanceb(a,b-1);}

int Incrementer(int n, bool T[]){
  if(T[n]==1){
    T[n]=0;
    return Incrementer(n-1,T);
  }
  else{
    T[n]=1;
    return ((sizeof(T)/2)-n+1);
}

int Compte(int n){
  int cpt=0;
  int* T=malloc(n*sizeof(int));
  for(int i=0;i<n;i++)
    T[i]=0;
  for(int i=0;i<apuissanceb(2,n);i++)
    cpt+=Incrementer(n,T);
  return cpt/n;
}

int main(int argv, char** argc){

  int numeroFonction = atoi(argc[1]),
     n =  atoi(argc[2]),
    v;
  float w;

  switch (numeroFonction) {
    case 1 : v=f1(n); w=(float)v/sqrt(n); break; // constante : 3
    case 2 : v=f2(n); w=(float)v/apuissanceb(n,5); break; // constante : 0,1
    case 3 : v=f3(n); w=(float)v/(n*n); break; // constante : 0,5
    case 4 : v=f4(n); w=(float)v/log2(n); break; // constante : 1,35
    case 5 : v=f5(n); w=(float)v/apuissanceb(2,n); break; // constante : 10
    case 6 : v=f6(n); w=(float)v/apuissanceb(3,n); break; // constante : 20
  }

  std::cout<<"f"<<numeroFonction<<"("<<n<<") renvoie "<<v<<"\n"<<w<<"\n";
  return 0;
}

/*
ordre de compilation :  g++ SolutionsFonctionMysterieuses.cpp fonctionsMysterieuses.o -o test
Ordre d'exécution :  ./test 1 2 
*/

