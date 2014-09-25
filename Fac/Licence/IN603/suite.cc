#include <iostream>
#include <vector>

using namespace std;

#include "td2.h"

Suite::Suite() {}
Suite::~Suite() {}
float Suite::s(int n) const {
  float som = 0;
  for(int i=0 ; i<n ; i++)
    som += (*this)(i);
  return som;
}
ostream& operator<< (ostream& os, const Suite& s) { s.affiche(os); return os; }
istream& operator>> (istream& is, const Suite& s) { s.saisie(is); return is; }

// SuiteArith::SuiteArith
float SuiteArith::operator()(int n) {return u0+n*r;}
float SuiteArith::s(int n) const {return (n*(*this)(0)+n*(n-1)*(r/2));}
float SuiteArith::raison() {return r;}
// ostream& SuiteArith::
// istream& SuiteArith::

SuiteConst::SuiteConst(int val) { a=val; rg=0; }
SuiteConst::~SuiteConst() {}
float SuiteConst::operator()(int n) const {
  if(n>=rang())
    return a;
  else
    return u[n];
}
float SuiteConst::rang() const {return rg;}
// ostream& SuiteConst::
istream& SuiteConst::saisie(istream& is) {
  float v;
  cout<<"rang :\n";
  is>>rg;
  cout<<"valeurs :\n";
  for(int i=0;i<rg;i++){
    float f;
    is>>f;
    u.push_back(f);
  }
}
