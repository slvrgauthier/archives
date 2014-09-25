#include <iostream>
#include "Itv.h"
using namespace std;

Itv::Itv(){bi=0.0;bs=0.0;}
Itv::Itv(float inf,float sup) : bi(inf),bs(sup) {}

float Itv::getBi(){return bi;}
void Itv::setBi(float inf){bi=inf;}
float Itv::getBs(){return bs;}
void Itv::setBs(float sup){bs=sup;}

void Itv::saisie(){cout<<"Bi : ";cin>>bi;
                       cout<<"Bs : ";cin>>bs;cout<<endl;}

void Itv::afficher(){cout<<"["<<bi<<","<<bs<<"]"<<endl;}

bool Itv::appartient(float x){if((x>=bi)&&(x<=bs)) 
                                return true; 
                              else return false;}

float Itv::longueur(){return bs-bi;}

bool Itv::egal(Itv I){if((I.bi==bi)&&(I.bs==bs))
                        return true;
                      else return false;}

bool Itv::inclu(Itv I){if(((I.bi>=bi)&&(I.bs<bs))||((I.bi>bi)&&(I.bs<=bs)))
                         return true;
                       else return false;}

bool Itv::disjoint(Itv I){if((I.bi>bs)||(I.bs<bi))
                            return true;
                          else return false;}

bool Itv::accole(Itv I){if((I.bi==bs)||(I.bs==bi))
                          return true;
                        else return false;}

bool Itv::imbrique(Itv I){if((!(egal(I)))&&(!(inclu(I)))&&(!(disjoint(I)))&&(!(accole(I))))
                            return true;
                          else return false;}

void Itv::translate(float x){bi+=x;bs+=x;}

void translate(Itv& I, float x){I.bi+=x;I.bs+=x;}
