#include <iostream>
using namespace std;
#include "personne.h"
#include "string.h"

Personne::Personne() {nom="";nb_places=0;}
Personne::Personne(string n,int nb) : nom(n),nb_places(nb) {}
Personne::~Personne() {nom="Libre";nb_places=0;/*delete &nom; delete &nb_places;*/}

string Personne::getNom() const {return nom;}
int Personne::getNb_places() const {return nb_places;}

void Personne::setNom(string n) {nom=n;}
void Personne::setNb_places(int nb) {nb_places=nb;}

void Personne::saisie() {
  cout<<"Entrez le nom :"<<endl;
  cin>>nom;
  cout<<endl<<"Entrez le nombre de places :"<<endl;
  cin>>nb_places;
  cout<<endl;
}

void Personne::affichage() const {
  cout<<"Nom : "<<nom<<endl<<"Nombre de places : "<<nb_places<<endl;
}
