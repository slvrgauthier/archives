#include <iostream>

using namespace std;

void  removeif(C& c, Pred p) {
  typename C::iterator pr=remove_if(c.begin(),c.end(),p);
  c.erase(pr,c.end());
}

template<class C>
void afficher(const C& c) {
  copy(c.begin(),c.end(),ostream_iterator<typename C::value_type(cout," "));
  cout<<endl;
}

int main() {
  
}

