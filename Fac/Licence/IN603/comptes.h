#ifndef COMPTES_H
#define COMPTES_H

class CompteBancaire {
private :
  double solde = 0;

public :
  CompteBancaire();
  virtual ~CompteBancaire();
  virtual void deposer(double);
};

class CompteRemunere:public CompteBancaire {
private :
  double interet = 1,1;

public :
  CompteRemunere();
  virtual ~CompteRemunere();
  virtual void deposer(double);
};

class CompteDepot:virtual public CompteBancaire {
public :
  CompteDepot();
  virtual ~CompteDepot();
  virtual void deposer(double);
};

class CompteDepotRemunere:public CompteRemunere, public CompteDepot {
public :
  CompteDepotRemunere();
  virtual ~CompteDepotRemunere();
  void deposer(double);
};

class CompteDepotAvecCarteCredit:public CompteDepot {
public :
  CompteDepotAvecCarteCredit();
  virtual ~CompteDepotAvecCarteCredit();
};

class CompteDepotRemunereEtAvecCarteCredit:public CompteDepotAvecCarteCredit, public CompteDepotRemunere {
public :
  CompteDepotRemunereEtAvecCarteCredit();
  virtual ~CompteDepotRemunereEtAvecCarteCredit();

};

#endif

