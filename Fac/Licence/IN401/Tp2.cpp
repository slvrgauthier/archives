#include <iostream>
using namespace std;

void f1(int n);
void f9(int n);
void f2(int n);
void f3(int n);

int main(){
  int x;
  cout<<"Tapez un int : ";
  cin>>x;
  cout<<endl;
  cout<<"f1 ";
  f1(x);
  cout<<"stop"<<endl;
  cout<<"f9 ";
  //f9(x);
  cout<<"stop"<<endl;
  cout<<"f2 ";
  f2(x);
  cout<<"stop"<<endl;
  cout<<"f3 ";
  f3(x);
  cout<<"stop"<<endl;
/* Différence de temps entre :
    f1 et f9 : à partir de 7
    f9 et f2 : à partir de 52
    f2 et f3 : à partir de 16  */
  return 0;
}

void f1(int n){
  int j=0;
  for(int i=0;i<n;i++)
    j++;
}

void f9(int n){
  int s=0;
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      for(int k=0;k<n;k++)
        for(int l=0;l<n;l++)
          for(int m=0;m<n;m++)
            for(int o=0;o<n;o++)
              for(int p=0;p<n;p++)
                for(int q=0;q<n;q++)
                  for(int r=0;r<n;r++)
                    s++;
}

void f2(int n){
  if(n==0)
    int i=0;
  else{
    f2(n-1);
    f2(n-1);
  }
}

void f3(int n){
  if(n==0)
    int i=0;
  else{
    f3(n-1);
    f3(n-1);
    f3(n-1);
  }
}
