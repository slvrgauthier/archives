#include <iostream>
#include "Itv.h"
using namespace std;

int main(){
  Itv I1(2.5,7.5);
  Itv I2,I3;

  float x,y;
  cout<<"Entrez deux float :";
  cin>>x>>y;
  I2.setBi(x);
  I2.setBs(y);

  cout<<"Resume de I1 :"<<endl;
  cout<<"bi : "<<I1.getBi()<<endl;
  cout<<"bs : "<<I1.getBs()<<endl;
  cout<<"affiche : ";
  I1.afficher();
  cout<<"1.0 ";
  if(I1.appartient(1.0))
    cout<<"appartient a I1."<<endl;
  else
    cout<<"n'appartient pas a I1"<<endl;
  cout<<"5.0 ";
  if(I1.appartient(5.0))
    cout<<"appartient a I1."<<endl;
  else
    cout<<"n'appartient pas a I1"<<endl;
  cout<<"longueur : "<<I1.longueur()<<endl;
  cout<<endl;

  cout<<"Resume de I2 :"<<endl;
  cout<<"bi : "<<I2.getBi()<<endl;
  cout<<"bs : "<<I2.getBs()<<endl;
  cout<<"affiche : ";
  I2.afficher();

  cout<<"I1 est ";
  if(I1.egal(I2))
    cout<<"egal, ";
  else
    cout<<"non-egal, ";
  if(I1.inclu(I2))
    cout<<"inclus, ";
  else
    cout<<"non-inclus, ";
  if(I1.disjoint(I2))
    cout<<"disjoint, ";
  else
    cout<<"non-disjoint, ";
  if(I1.accole(I2))
    cout<<"accole, ";
  else
    cout<<"non-accole et ";
  if(I1.imbrique(I2))
    cout<<"imbrique ";
  else
    cout<<"non-imbrique ";
  cout<<"a I2."<<endl;

  cout<<"I1 avec une translation de 2.5 : ";
  I1.translate(2.5);
  I1.afficher();
  cout<<"I1 avec une translation de 2.5 : ";
  translate(I1,2.5);
  I1.afficher();
  cout<<endl;

  cout<<"Saisir I3 :"<<endl;
  I3.saisie();
  I3.afficher();
}
