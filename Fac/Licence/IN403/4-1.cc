#include <iostream>
#include <cmath>
using namespace std;
#include "point2D.h"
#include "triangle.h"

int main(){
  const Point2D orig;
  Point2D A(2.3,5.8),B(1,4),C(0,3),D(4,0),E(0.5,sqrt(3)/2.0),F(0,1);

  orig.affiche();
  cout<<"origine : "<<orig.getX()<<" , "<<orig.getY()<<endl;

  A.affiche();
  B.affiche();

  cout<<A.distance(orig)<<endl;
  cout<<A.distance(B)<<endl;

  B.setX(-4.5);
  B.setY(4.5);

  cout<<A.distance(B)<<endl;

  Triangle T(orig,A,B),U(orig,C,D),V(orig,F,E);
  if(T.isoc())
    cout<<"T est isocèle";
  else
    cout<<"T est non-isocèle";
  if(T.rect())
    cout<<", rectangle";
  else
    cout<<", non-rectangle";
  if(T.equi())
    cout<<", equilateral."<<endl;
  else
    cout<<", non-equilateral."<<endl;
  cout<<"Son perimetre est "<<T.peri()<<endl;
  if(U.isoc())
    cout<<"U est isocèle";
  else
    cout<<"U est non-isocèle";
  if(U.rect())
    cout<<", rectangle";
  else
    cout<<", non-rectangle";
  if(U.equi())
    cout<<", equilateral."<<endl;
  else
    cout<<", non-equilateral."<<endl;
  cout<<"Son perimetre est "<<U.peri()<<endl;
  if(V.isoc())
    cout<<"V est isocèle";
  else
    cout<<"V est non-isocèle";
  if(V.rect())
    cout<<", rectangle";
  else
    cout<<", non-rectangle";
  if(V.equi())
    cout<<", equilateral."<<endl;
  else
    cout<<", non-equilateral."<<endl;
  cout<<"Son perimetre est "<<V.peri()<<endl;
return 0;
}
