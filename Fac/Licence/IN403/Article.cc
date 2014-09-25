#include <iostream>
#include "Article.h"
#include "string.h"
using namespace std;

Article::Article(){ref=0;prix=0.0;nom="";promo=false;
                   reduc[0]=15;reduc[1]=25;reduc[2]=35;reduc[3]=45;}
Article::Article(int r,float p,string n,bool b) : ref(r),prix(p),nom(n),promo(b) {
  if(b){
    reduc[0]=10;reduc[1]=20;reduc[2]=30;reduc[3]=40;}
  else{
    reduc[0]=15;reduc[1]=25;reduc[2]=35;reduc[3]=45;}}

int Article::getRef(){return ref;}
void Article::setRef(int r){ref=r;}
float Article::getPrix(){return prix;}
void Article::setPrix(float p){prix=p;}
string Article::getNom(){return nom;}
void Article::setNom(string n){nom=n;}
bool Article::getPromo(){return promo;}
void Article::setPromo(bool b){promo=b;
  if(b){
    reduc[0]=10;reduc[1]=20;reduc[2]=30;reduc[3]=40;} 
  else{ 
    reduc[0]=15;reduc[1]=25;reduc[2]=35;reduc[3]=45;}}

void Article::saisie(){cout<<"Ref : ";cin>>ref;
                       cout<<"Prix : ";cin>>prix;
                       cout<<"Nom : ";cin>>nom;
                       cout<<"Promo :";cin>>promo;
                       if(promo){
                         reduc[0]=10;reduc[1]=20;reduc[2]=30;reduc[3]=40;} 
                       else{
                         reduc[0]=15;reduc[1]=25;reduc[2]=35;reduc[3]=45;}
                       cout<<endl;}

void Article::afficher(){cout<<"Reference : "<<ref<<endl;
                         cout<<"Prix : "<<prix<<endl;
                         cout<<"Nom : "<<nom<<endl;
                         cout<<"Promo : "<<promo<<endl;}
