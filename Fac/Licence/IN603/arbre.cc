#include <iostream>
using namespace std;
#include "arbre.h"

Arbre::Arbre() {racine = NULL;}
Arbre::Arbre(TypeCle c, Arbre* g, Arbre* d) {racine = new Noeud(c,g,d);}
Arbre::~Arbre() {if(!estVide()) {delete sag(); delete sad(); delete racine;}}

void ArbreRecherche::insere(TypeCle c) {
  if(estVide()) {
    Arbre* a1 = new ArbreRecherche();
    Arbre* a2 = new ArbreRecherche();
    racine = new Noeud(c,a1,a2);
  }
  else if(c==cle())
    cout<<"Répétition de "<<c<<endl;
  else if(c < cle())
    sag()->insere(c);
  else
    sad()->insere(c);
}