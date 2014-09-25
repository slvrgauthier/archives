#include "SortieLatex.cpp"

int main() {
  // fabrication de A0
  AB A0=new Sommet(0), A1=new Sommet(1), A2=new Sommet(2), A3=new Sommet(3),A4=new Sommet(4), A5=new Sommet(5), A6=new Sommet(6);
  A3->GrefferSAG(A4);
  A3->GrefferSAD(A5);
  A0->GrefferSAG(A2);
  A0->GrefferSAD(A4);
  A6->GrefferSAG(A0);
  A6->GrefferSAD(A0);
  // impression
  std::cout<<SortieLatex(A6);
  return 1;
}

