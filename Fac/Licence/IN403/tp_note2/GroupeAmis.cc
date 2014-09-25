#include <iostream>
#include "Personne.h"
#include "GroupeAmis.h"

GroupeAmis::GroupeAmis() {sousgroupe=NULL;}
GroupeAmis::GroupeAmis(const Personne& P, GroupeAmis* G) {personne=P; sousgroupe=G;}
GroupeAmis::~GroupeAmis() {delete &personne; delete sousgroupe;}

void GroupeAmis::operator=(const GroupeAmis& G) {personne=G.personne; sousgroupe=G.sousgroupe;}
void GroupeAmis::operator+(const GroupeAmis& G) {
  Gptr=G; 
  while(!Gptr.EstVide()) {
    this.ajouter(Gptr.personne);
    Gptr=Gptr.sousgroupe;
  }
}
void GroupeAmis::operator+(const Personne& P) {this.ajouter(P);}

bool GroupeAmis::EstVide()const {Personne Vide; return personne==Vide && sousgroupe==NULL;}

void GroupeAmis::ajouter(const Personne& P)  {
  if (EstVide())
    personne=P;
  else //{
    //GroupeAmis sg(P, sousgroupe);
    //sousgroupe= &sg;
    sousgroupe= new GroupeAmis(P, sousgroupe);
}

void GroupeAmis::supprimer(const Personne& P) {
  if(!EstVide()){
    if (personne==P){
      Personne Vide;
      personne=Vide;}
    else
      sousgroupe->supprimer(P);
  }}


void GroupeAmis::afficher()const { if (!EstVide()) {personne.affiche(cout); sousgroupe->afficher();} }

bool GroupeAmis::appartient(const Personne& P) {
  if (EstVide()) 
    return false; 
  else if (personne==P) 
    return true; 
  else 
    return sousgroupe->appartient(P); }

