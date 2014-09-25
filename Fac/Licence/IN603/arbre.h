#ifndef ARBRE_H
#define ARBRE_H

#include "noeud.h"

class Arbre {
protected :
  Noeud * racine;
public :
  Arbre();
  Arbre(TypeCle c, Arbre * g, Arbre * d);
  virtual TypeCle cle() const;
  virtual Arbre*& sag() const;
  virtual Arbre*& sad() const;
  virtual bool estVide() const;
  virtual bool feuille() const;
  virtual void insere(TypeCle c)=0;
protected :
  virtual void imprime(ostream&) const;
  virtual void imprimeContenu(ostream&) const;
  virtual void imprimeEntete(ostream&) const;
  virtual bool recherche(TypeCle c) const;
};

ostream& operator<<(ostream& os, const Arbre& A);

class ArbreRecherche:virtual public Arbre {
public:
  ArbreRecherche();
  ArbreRecherche(TypeCle c, ArbreRecherche* g, ArbreRecherche* d);
  ArbreRecherche(const ArbreRecherche&);
  virtual ~ArbreRecherche();
  virtual ArbreRecherche& operator=(const ArbreRecherche&);
  virtual void insere(TypeCle cle);
  virtual bool recherche(TypeCle cle) const;
};

#endif
