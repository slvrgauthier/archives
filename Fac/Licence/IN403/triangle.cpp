#include <iostream>
using namespace std;
#include "point2D.h"
#include "triangle.h"

Triangle::Triangle(const Point2D& p1,const Point2D& p2,const Point2D& p3){
A.setX(p1.getX());A.setY(p1.getY());B.setX(p2.getX());B.setY(p2.getY());C.setX(p3.getX());C.setY(p3.getY());
}

bool Triangle::isoc() const {
  double c1=A.distance(B), c2=B.distance(C), c3=C.distance(A);
  if(c1==c2 || c2==c3 || c3==c1)
    return true;
  else 
    return false;}

bool Triangle::rect() const {
  double c1=A.distance(B), c2=B.distance(C), c3=C.distance(A);
  if(((c1*c1) == (c2*c2+c3*c3)) || ((c2*c2) == (c3*c3+c1*c1)) || ((c3*c3) == (c1*c1+c2*c2)))
    return true;
  else
    return false;}

bool Triangle::equi() const{
  double c1=A.distance(B), c2=B.distance(C), c3=C.distance(A);
  if(c1==c2 && c2==c3)
    return true;
  else
    return false;}

double Triangle::peri() const{
  double c1=A.distance(B), c2=B.distance(C), c3=C.distance(A);
  return c1+c2+c3;}
