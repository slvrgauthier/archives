#ifndef FILE_H
#define FILE_H

#include <iostream>
using namespace std;
#include "personne.h"
#include "string.h"

class File{
  private:
    Personne *tab;
    int taille;
    int deb;
    int fin;

  public:
    File();
    File(int);
    ~File();

    void ajouter(const Personne&);
    void retirer();

    void affichage() const;

    bool fileVide() const;
    int longueur() const;
    void etats() const;
};

#endif
