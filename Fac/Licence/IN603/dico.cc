#include <iostream>
#include <string>

using namespace std;

#include "td3.h"

template<tyename TypeCle,typename TypeValeur>
int Dictionnaire<TypeCle,TypeValeur>::hash(TypeCle c, int n)

template<tyename TypeCle,typename TypeValeur>
Dictionnaire<TypeCle,TypeValeur>::Dictionnaire() {
  tabAssoc=new Assoc<TypeCle,TypeValeur>[10];
  for(int i=0;i<10;i++) {
    tabAssoc[i].setCle(cleDefaut);
    tabAssoc[i].setValeur(valeurDefaut);
  }
  nbAssoc=0;
  capacite=10;
}

template<tyename TypeCle,typename TypeValeur>
Dictionnaire<TypeCle,TypeValeur>::Dictionnaire(const Dictionnaire& D) {
  capacite=D.capacite;
  nbAssoc=D.nbAssoc;
  tabAssoc=new Assoc<TypeCle,TypeValeur>[capacite];
  for(int i=0;i<capacite;i++)
    tabAssoc[i]=D.tabAssoc[i];
}

template<tyename TypeCle,typename TypeValeur>
Dictionnaire<TypeCle,TypeValeur>::~Dictionnaire() {
  for(int i=0;i<capacite;i++)
    ~tabAssoc[i];
}

template<tyename TypeCle,typename TypeValeur>
void Dictionnaire<TypeCle,TypeValeur>::put(const TypeCle& c,const TypeValeur v) {}


template<tyename TypeCle,typename TypeValeur>
TypeValeur Dictionnaire<TypeCle,TypeValeur>::get(const TypeCle& c)const {}

template<tyename TypeCle,typename TypeValeur>
bool Dictionnaire<TypeCle,TypeValeur>::estVide()const {}

int Dictionnaire<TypeCle,TypeValeur>::taille()const {return nbAssoc;}

template<tyename TypeCle,typename TypeValeur>
bool Dictionnaire<TypeCle,TypeValeur>::contient(const TypeCle& c)const {}

template<tyename TypeCle,typename TypeValeur>
void Dictionnaire<TypeCle,TypeValeur>::affiche(ostream& os)const {}

template<tyename TypeCle,typename TypeValeur>
Dictionnaire& Dictionnaire<TypeCle,TypeValeur>::operator=(const Dictionnaire& D) {}

//Permettre la création d'instances :
template<> class Dictionnaire<string,int>;
template<> class Dictionnaire<int,int>;
//...

template<> int Dictionnaire<string,int>::hash(string c,int tailleTab) {
  int i=0;
  for(int j=0;j<c.length();j++)
    i+=(j+1)*c[j];
  }
  return (i%tailleTab);
}

template<> string Dictionnaire<string,int>::cleDefaut="rien";

