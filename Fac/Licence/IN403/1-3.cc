#include <iostream>
using namespace std;

int main(){
  int a=0,b=1,c,n;

  cout<<"Entrez le rang maximal :"<<endl;
  cin>>n;

  for(int i=0;i<=n;i++){
    if(i==0)
      cout<<"Rang 0 : 0"<<endl;
    else if(i==1)
      cout<<"Rang 1 : 1"<<endl;
    else{
      c=a+b;
      cout<<"Rang "<<i<<" : "<<c<<endl;
      a=b;
      b=c;
    }
  }
  return 0;
}
