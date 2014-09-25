#include <iostream>
#include <string>
using namespace std;

bool pal(string s){
  size_t i=0,j=s.length()-1;
  while(i<j){
    if(s[i]!=s[j])
      return false;
    i++;
    j--;
  }
  return true;
}

int main(){
  string s;
  cout<<"Tapez du texte :"<<endl;
  cin>>s;

  while(s!="fini"){
    cout<<s;
    if(pal(s))
      cout<<" : est un palindrome."<<endl;
    else
      cout<<" : n'est pas un palindrome."<<endl;
    cin>>s;
  }
  return 0;
}
