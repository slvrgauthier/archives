#include <iostream>
using namespace std;
#include "personne.h"
#include "file.h"
#include "string.h"

File::File() {taille=0; deb=0; fin=0;}
File::File(int t) {tab=new Personne[t+1]; taille=t; deb=0; fin=0;}
File::~File() {delete[] tab; delete &taille; delete &deb; delete &fin;}

void File::ajouter(const Personne& p) {
  if(taille!=0 && (fin+1)%taille==deb){
    Personne *temp;
    temp=new Personne[taille+1];
    for(int i=deb;i!=fin;i=(i+1)%taille)
      temp[i]=tab[i];
    tab=new Personne[taille+1];
    for(int i=0;i<taille;i++)
      tab[i]=temp[i];
    taille++;
    for(int k=taille-1;k>fin;k--)
      tab[k]=tab[k-1];
    deb++;
  }
  tab[fin]=p;
  fin=(fin+1)%taille;
}

void File::retirer() {
  Personne vide("Libre",0);
  if(fileVide()==false){
    tab[deb]=vide; 
    deb++;
  }
}

void File::affichage() const {cout<<"Personnes en attente :"<<endl; for(int i=0;i<taille;i++) cout<<tab[i].getNom()<<endl;}

bool File::fileVide() const {return (fin==deb);}
int File::longueur() const {return fin-deb+1;}
void File::etats() const {
  cout<<"File d'attente :"<<endl;
  for(int i=0;i<taille;i++)
    cout<<tab[i].getNom()<<endl;
  cout<<"Taille : "<<taille<<endl;
  cout<<"Indice de debut : "<<deb<<endl;
  cout<<"Indice de fin : "<<fin<<endl;
}
