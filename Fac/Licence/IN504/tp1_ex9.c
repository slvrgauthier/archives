#include <stdlib.h>
#include <stdio.h>

int fact(int n) {
  if(n==0){
    printf("n = %d , résultat *1.\n",n);
    return 1;}
  else{
    printf("n = %d , résultat *n.\n",n);
    return n*fact(n-1);}
}

int main(int argc, char* argv[], char* env[]) {
  printf("Le résultat de fact(3) est %d\n",fact(3));
  return 0;
}
