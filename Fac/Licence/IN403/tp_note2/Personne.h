#ifndef PERSONNE_H
#define PERSONNE_H

#include "string.h"
using namespace std;

class Personne {
  private :
    string nom;
    string prenom;

  public :
    Personne();
    Personne(string, string);
    bool operator==(const Personne&)const;
    bool operator!=(const Personne&)const;
    ostream& affiche(ostream&)const;
    istream& saisie(istream&);
};


istream& operator>> (istream& i, Personne&);
ostream& operator<< (ostream& o, Personne&);

#endif
