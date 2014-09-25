#ifndef TD3_H
#define TD3_H

#include "Assoc.h"

template<typename TypeCle, typename TypeValeur>
class Dictionnaire {
private :
  Assoc<TypeCle,TypeValeur>* tabAssoc;
  int nbAssoc;
  int capacite;
  static TypeCle cleDefaut;
  static TypeValeur valeurDefaut;

public:
  static int hash(TypeCle, int);
  Dictionnaire();
  Dictionnaire(const Dictionnaire& D);
  virtual ~Dictionnaire();
  virtual void put(const TypeCle&,const TypeValeur&);
  virtual TypeValeur get(const TypeCle&)const;
  virtual bool estVide()const;
  virtual int taille()const;
  virtual bool contient(const TypeCle&)const;
  virtual void affiche(ostream&);
  virtual Dictionnaire& operator=(const Dictionnaire& D);
};

#endif

