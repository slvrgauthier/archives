#include <iostream>
using namespace std;

int main (){
  int a,b,c,n,v,j=0;
  size_t i=0;

  cout<<"Entrez le premier nombre du triplet :"<<endl;
  cin>>a;
  cout<<"Entrez le deuxieme nombre du triplet :"<<endl;
  cin>>b;
  cout<<"Entrez le troisieme nombre du triplet :"<<endl;
  cin>>c;
  cout<<"Entrez le nombre de données total :"<<endl;
  cin>>n;
  cout<<"Entrez vos données :"<<endl;

  while(j<n){
    cin>>v;
    j++;
    if((v==a)&&(j<n)){
      cin>>v;
      j++;
      if((v==b)&&(j<n)){
        cin>>v;
        j++;
        if((v==c)&&(j<n))
          i++;
      }
    }
  }
  cout<<"Le triplet revient "<<i<<" fois."<<endl;
  return 0;
}

