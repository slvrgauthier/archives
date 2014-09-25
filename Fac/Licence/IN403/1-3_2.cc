#include <iostream>
using namespace std;

long long int fibRec(int k){
  if(k==0)
    return 0;
  else if(k==1)
    return 1;
  else
    return (fibRec(k-1)+fibRec(k-2));
}

int main(){
  int n;

  cout<<"Entrez le rang maximal :"<<endl;
  cin>>n;

  cout<<fibRec(n)<<endl;

  return 0;
}
