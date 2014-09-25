#include <iostream>
using namespace std;

void TriSelection(int t[], int n);
int indPPV(int t[], int i, int n);

void TriInsertion(int t[], int n);
void rot(int t[], int k, int l);
void insert(int t[], int n);

void TriFusion(int t[], int n);
void fusOrd(int t[], int d, int m, int f);

int main(){
  cout<<"Tri selection :"<<endl;
  int T1[10]={18,15,2,34,20,5,45,75,2,90};
  TriSelection(T1,10);
  for(int i=0;i<10;i++)
    cout<<T1[i]<<" ";
  cout<<endl;

  cout<<endl<<"Tri par insertion :"<<endl;
  int T2[10]={15,24,15,26,25,85,10,24,0,1};
  TriInsertion(T2,10);
  for(int i=0;i<10;i++)
    cout<<T2[i]<<" ";
  cout<<endl;

  cout<<endl<<"Tri fusion :"<<endl;
  int T3[10]={52,42,62,32,2,85,95,74,12,30};
  TriFusion(T3,10);
  for(int i=0;i<10;i++)
    cout<<T3[i]<<" ";
  cout<<endl;

return 0;
}

void TriSelection(int t[], int n){
  for(int i=0;i<n;i++){
    int j=indPPV(t,i,n), temp=t[i];
    t[i]=t[j]; t[j]=temp;
  }
}

int indPPV(int t[], int i, int n){
  int temp=t[i], ind=i;
  for(int j=i+1;j<n;j++)
    if(t[j]<temp){
      temp=t[j];
      ind=j;
    }
  return ind;
}

void TriInsertion(int t[], int n){
  for(int i=0;i<n;i++)
    insert(t,i);
}

void rot(int t[], int k, int l){
  int temp=t[l];
  for(int i=l-1;i>=k;i--)
    t[i+1]=t[i];
  t[k]=temp;
}

void insert(int t[], int n){
  int k=n;
  while((k>0) && (t[k-1]>t[n]))
    k--;
  rot(t,k,n);
}

void TriFusion(int t[], int n){

}

void fusOrd(int t[], int d, int m, int f){

}
