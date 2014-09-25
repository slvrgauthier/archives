#include <iostream>
#include <cmath>
using namespace std;
#include "point2D.h"

Point2D::Point2D(){x=0.0;y=0.0;}
Point2D::Point2D(float abs,float ord) : x(abs),y(ord) {}

void Point2D::affiche()const{cout<<"("<<x<<","<<y<<")"<<endl;}
double Point2D::distance(const Point2D& p) const {
return (double)sqrt((p.x-x)*(p.x-x)+(p.y-y)*(p.y-y));}

float Point2D::getX() const {return x;}
void Point2D::setX(float abs){x=abs;}
float Point2D::getY() const {return y;}
void Point2D::setY(float ord){y=ord;}
