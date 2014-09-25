#include <iostream>
using namespace std;

long long int fibIter(int k){
  long long int a=0,b=1,c;
  if(k==0)
    return 0;
  if(k==1)
    return 1;
  for(int i=1;i<k;i++){
      c=a+b;
      a=b;
      b=c;
  }
  return c;
}

int main(){
  int n;

  cout<<"Entrez le rang maximal :"<<endl;
  cin>>n;

  for(int i=0;i<=n;i++)
    cout<<"Rang "<<i<<" : "<<fibIter(i)<<endl;

  return 0;
}
