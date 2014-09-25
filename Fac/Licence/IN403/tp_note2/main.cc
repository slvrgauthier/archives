#include <iostream>
#include "Personne.h"
#include "GroupeAmis.h"
using namespace std;

GroupeAmis AmisCommun(GroupeAmis G1, GroupeAmis G2){
  GroupeAmis GAC;
  while (!G1.EstVide()){
    if(G2.appartient(G1.personne)){
      GAC.ajouter(G1.personne);
      G1=G1.sousgroupe;
    }
  }
  return GAC;
}

int main(){
/*Personne a,b;
cin>>a>>b;
if(a!=b)
cout<<a<<" est different de "<<b<<endl;*/

/*GroupeAmis G1;
G1.ajouter(Personne("Yves","Lopez"));
GroupeAmis G2(G1);*/

/*GroupeAmis G1,G2,G3;
Personne P1("Lelui","Robert");
Personne P2,P3; cin>>P2>>P3;
G1+=P1;
G2+=P2;
G3+=P3+G1+G2;*/

GroupeAmis G1, G2;
Personne P1("aa","bb");
Personne P2("cc","dd");
Personne P3("ee","ff");
Personne P4("gg","hh");
G1.ajouter(P1);
G2=G1+P2;
G1+=P3;

G1.supprimer(P3);
G1+=P4;
G2+=P4;

AmisCommun(G1,G2).afficher();

return 0;
}
