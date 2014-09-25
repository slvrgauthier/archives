#include <iostream>
#include <sstream>

typedef int Valeur;

struct Sommet;

typedef Sommet* AB;

struct Sommet {
  Valeur racine;
  AB Pere,SAG, SAD;

  int hauteur,balanceGmoinsD;

  Sommet(Valeur v){
    racine=v;
    Pere=NULL;
  };
  Sommet(Sommet& s){
    SAG=s.SAG;
    SAD=s.SAD;
  };

  AB remonterToutEnHaut();

  void GrefferSAG(AB g){
    SAG=g;
    g->Pere=this;
  };
  void GrefferSAD(AB d){
    SAD=d;
    d->Pere=this;
  };

  void SupprimerSAG(){
    SAG->Pere=NULL;
    SAG=NULL;
  };
  void SupprimerSAD(){
    SAD->Pere=NULL;
    SAD=NULL;
  };

  bool FeuilleP(){
    (SAG==NULL && SAD==NULL);
  };

  void RemplacerPourLePerePar(AB d){
    if(this == this->Pere->SAG)
      Pere->GrefferSAG(d);
    else
      Pere->GrefferSAD(d);
  };
};


std::string TikzRecursAB(int ligne,int gauche, int droite, int numeroPere, int typeFils, AB Ar);

std::string TikzAB(AB Ar);






std::string TikzRecursAB(int ligne,int gauche, int droite, int numeroPere, int typeFils, AB Ar){
  std::ostringstream ossnum, osslign,osscol,ossnumPere, ossbal, ossnum2Pere,ossnumRac;
  if (Ar) {
    ossnumPere<<numeroPere;
    ossnumRac<<Ar->racine;
    if (Ar->Pere )ossnum2Pere<<Ar->Pere->racine; else ossnum2Pere<<0;
    int numero;
    if (typeFils==-1) numero=1; else numero= 2*numeroPere + typeFils;
    ossnum<<numero;
    osslign<<ligne;
    int mil = (gauche + droite)/2;
    osscol<<mil;
    std::string stres;

    stres="\\node[draw] (SZ" + ossnum.str() + ") at (" + osscol.str() + ", " + osslign.str() + ") { " + ossnumRac.str() + "};\n";

    if (typeFils!=-1) stres+="\\draw (SZ"+ossnumPere.str()+") -- (SZ"+ossnum.str() +");\n";
    if (Ar->SAG) stres+=TikzRecursAB(ligne -1 ,gauche,mil-1, numero,0,Ar->SAG);
    if (Ar->SAD) stres+=TikzRecursAB(ligne - 1,mil+1,droite, numero,1,Ar->SAD);

    return stres;
  }
  else return "";}

std::string SortieLatex(AB Ar){
  return "\\documentclass[a4paper]{article} \n \\usepackage{tikz} \n \\begin{document} \n \\begin{tikzpicture}\n" + TikzRecursAB(1,1,10,1, -1,Ar) + "\n  \\end{tikzpicture}\n  \\end{document} \n";
}

// g++ -c SortieLatex.cpp
