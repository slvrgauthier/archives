#define NMAX 50
#define MATL 50
#define MATH 50
#ifndef MATRICE_H
#define MATRICE_H

class Elem{
  private:
    float valeur;
    int ligne;
    int colonne;

  public:
    Elem();
    Elem(float,int,int);

    float getValeur() const;
    int getLigne() const;
    int getColonne() const;

    float setValeur(float);
    int setLigne(int);
    int setColonne(int);
};

class MatCreu{
  private:
    int nbElem;
    Elem Tab[NMAX];

  public:
    MatCreu();

    int getNbElem() const;

    void ajouter(const Elem&);
    void retirer(const Elem&);
    MatCreu addition(const MatCreu&);
    void affiche() const;
    void aff() const;
};

#endif
