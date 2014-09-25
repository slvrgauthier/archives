#include <iostream>
using namespace std;
#include "MatCreu.h"

Elem::Elem(){valeur=0.0;ligne=0;colonne=0;}
Elem::Elem(float val,int l,int c){valeur=val;ligne=l;colonne=c;}

float Elem::getValeur() const{return valeur;}
int Elem::getLigne() const{return ligne;}
int Elem::getColonne() const{return colonne;}

float Elem::setValeur(float val){valeur=val;}
int Elem::setLigne(int l){ligne=l;}
int Elem::setColonne(int c){colonne=c;}


MatCreu::MatCreu(){nbElem=0;}

int MatCreu::getNbElem() const{return nbElem;}

//On suppose les ajouts faits dans l'ordre. -> à modifier
void MatCreu::ajouter(const Elem& e){
  for(int i=0;i<NMAX;i++)
    if(Tab[i].getValeur()==0){
      Tab[i].setValeur(e.getValeur());
      Tab[i].setLigne(e.getLigne());
      Tab[i].setColonne(e.getColonne());
      break;
    }
  }
  
void MatCreu::retirer(const Elem& e){
}

MatCreu MatCreu::addition(const MatCreu& m){
  MatCreu N;
  int i1=0,i2=0;
  while(i1<NMAX && i2<NMAX){
    int i1l=Tab[i1].getLigne(), i1c=Tab[i1].getColonne();
    int i2l=m.Tab[i2].getLigne(), i2c=m.Tab[i2].getColonne();
    if(i1l < i2l){
      N.ajouter(Tab[i1]);
      i1++;
    }
    else if (i1l == i2l){
      if(i1c < i2c){
	N.ajouter(Tab[i1]);
	i1++;
      }
      else if(i1c == i2c){
	N.ajouter(Elem(Tab[i1].getValeur()+m.Tab[i2].getValeur(),i1l,i1c));
	i1++;
	i2++;
      }
      else{
	N.ajouter(m.Tab[i2]);
	i2++;
      }
    }
    else{
      N.ajouter(m.Tab[i2]);
      i2++;
    }
  }
  if(i2<NMAX)
    while(i2<NMAX){
      N.ajouter(m.Tab[i2]);
      i2++;
    }
  if(i1<NMAX)
    while(i1<NMAX){
      N.ajouter(Tab[i1]);
      i1++;
    }
  return N;
}

void MatCreu::affiche() const{
  int i=0;
  for(int ligne=1;ligne<=MATH;ligne++){
    for(int colonne=1;colonne<=MATL;colonne++){
      if((Tab[i].getLigne()==ligne)&&(Tab[i].getColonne()==colonne)){
	cout<<Tab[i].getValeur()<<"\t";
	i++;
      }
      else
	cout<<0<<"\t";
    }
    cout<<endl;
    }
}

void MatCreu::aff() const{
  for(int i=0;i<NMAX;i++){
    if(Tab[i].getValeur()==0)
      break;
    else
      cout<<Tab[i].getValeur()<<"\t"<<Tab[i].getLigne()<<"\t"<<Tab[i].getColonne()<<endl;
  }
}
