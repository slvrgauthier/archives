#ifndef TD2_H
#define TD2_H

class Suite {  
public :
  Suite();
  virtual ~Suite();
  virtual float operator()(int) const =0;
  virtual float s(int) const;
  virtual ostream& affiche(ostream& os) const =0;
  virtual istream& saisie(istream& is) =0;
};

class SuiteArith:virtual public Suite {
private :
  float u0;
  float r;
  
public :
  SuiteArith(float init=0, float raison=0);
  virtual ~SuiteArith();
  virtual float operator()(int) const;
  virtual float s(int) const;
  virtual float raison() const;
  virtual ostream& affiche(ostream& os) const;
  virtual istream& saisie(istream& is);
};

class SuiteConst:virtual public Suite {
private :
  int rg;
  float a;
  vector<float> u;
  
public :
  SuiteConst(int val=0);
  virtual ~SuiteConst();
  virtual float operator()(int) const;
  virtual int rang() const;
  virtual ostream& affiche(ostream& os) const;
  virtual istream& saisie(istream& is);
};

#endif

