#include <iostream>
using namespace std;
#include "MatCreu.h"

int main(){
MatCreu A,B;
Elem A1(4,1,3),A2(-34,1,6),A3(17,2,49),A4(567,5,11),A5(3,23,43),A6(129,39,1),A7(90,44,44),B1(60,2,35),B2(8,3,21),B3(43,5,11),B4(-7,6,37),B5(-129,39,1);

A.ajouter(A1);
A.ajouter(A2);
A.ajouter(A3);
A.ajouter(A4);
A.ajouter(A5);
A.ajouter(A6);
A.ajouter(A7);
B.ajouter(B1);
B.ajouter(B2);
B.ajouter(B3);
B.ajouter(B4);
B.ajouter(B5);

MatCreu C=A.addition(B);

cout<<"Matrice A :"<<endl;
A.aff();
//A.affiche();
cout<<"Matrice B :"<<endl;
B.aff();
//B.affiche();
cout<<"Matrice C :"<<endl;
C.aff();
//C.affiche();

return 0;
}
