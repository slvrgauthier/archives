#include <iostream>
#include <map>
#include <iterator>

using namespace std;

ostream& operator<<(ostream& os, const pair<const string,int>& p) {
  os<<p.first<<" "<<p.second<<endl;
  return os;
}

int main() {
  map<string,int,less<string> >dico; //less<string> fonction d'ordre
  string mot;
  while(cin>>mot) {
    if(dico.find(mot) != dico.end()) //voir man map.find
      ++(*(dico.find(mot))).second;
    else
      dico[mot]=1;
  }
  map<string,int,less<string> >::iterator is;
  cout<<endl<<endl;
  for(is=dico.begin();is!=dico.end();is++)
    cout<<*is;
  cout<<"\n"<<endl;
}

