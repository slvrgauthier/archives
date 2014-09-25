#ifndef PERSONNE_H
#define PERSONNE_H

#include <iostream>
using namespace std;
#include "string.h"

class Personne{
  private:
    string nom;
    int nb_places;

  public:
    Personne();
    Personne(string,int);
    ~Personne();

    string getNom() const;
    int getNb_places() const;

    void setNom(string);
    void setNb_places(int);

    void saisie();
    void affichage() const;
};

#endif
