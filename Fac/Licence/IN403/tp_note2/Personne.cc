#include <iostream>
#include "Personne.h"
#include "string.h"
using namespace std;

Personne::Personne() { nom=""; prenom=""; }
Personne::Personne(string n, string p) : nom(n), prenom(p) {}

bool Personne::operator==(const Personne& P)const {return nom==P.nom && prenom==P.prenom;}
bool Personne::operator!=(const Personne& P)const {return nom!=P.nom || prenom!=P.prenom;}

ostream& Personne::affiche(ostream &os)const {return os<<nom<<" "<<prenom;}
istream& Personne::saisie(istream &is) {return is>>nom>>prenom;}

istream& operator>>(istream& i, Personne& P) {P.saisie(i);}
ostream& operator<<(ostream& o, Personne& P) {P.affiche(o);}
