#include <iostream>
#include "Article.h"
using namespace std;

int main(){
  Article A1(152,29.90,"Lecteur MP3",true);
  Article A2,A3;

  A2.setRef(154);
  A2.setPrix(59.90);
  A2.setNom("Lecteur MP4");
  A2.setPromo(false);

  cout<<"Entrez les valeurs de A3 :"<<endl;
  A3.saisie();

  cout<<endl<<"Article 1 :"<<endl;
  A1.afficher();
  cout<<endl<<"Article 2 :"<<endl;
  cout<<"Reference : "<<A2.getRef()<<endl;
  cout<<"Prix : "<<A2.getPrix()<<endl;
  cout<<"Nom : "<<A2.getNom()<<endl;
  cout<<"Promo : "<<A2.getPromo()<<endl;

  cout<<endl<<"Article 3 :"<<endl;
  A3.afficher();

  Article Tab[3]={A1,A2,A3};
  float total=0.0;
  for(int i=0;i<3;i++)
    total+=Tab[i].prix;
  cout<<endl<<"Prix total : "<<total<<endl;
}
