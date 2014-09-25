#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define AVANCER {jeton=getchar();numcar++;}
#define TEST_AVANCE(prevu) {if (jeton==(prevu)) AVANCER else ERREUR_SYNTAXE}
#define ERREUR_SYNTAXE {printf("\nMot non reconnu : erreur de syntaxe au caractère numéro %d, de jeton %d \n",numcar,jeton); exit(1);}
#define JETON jeton-'0'

int E();int Re(int n);int T();int Rt(int n);int F();int Rp(int n);int 
P();

int jeton;
int numcar=0;

int E(){
  printf("E->TRe\n");
  return Re(T());
}
int Re(int n){
  if(jeton=='+'){
    printf("Re->+TRe\n");
    AVANCER
    return Re(n+T());
  }
  else if(jeton=='-'){
    printf("Re->-TRe\n");
    AVANCER
    return Re(n-T());
  }
  else{
    printf("Re->eps\n");
    return n;
  }
}
int T(){
  printf("T->PRt\n");
  return Rt(P());
}
int Rt(int n){
  if(jeton=='*'){
    printf("Rt->*PRt\n");
    AVANCER
    return Rt(n*P());
  }
  if(jeton=='/'){
    printf("Rt->/PRt\n");
    AVANCER
    return Rt(n/P());
  }
  else{
    printf("Rt->eps\n");
    return n;
  }
}
int P(){
  printf("P->FRp\n");
  return Rp(F());
}
int Rp(int n){
  if(jeton=='^'){
    printf("Rp->^PRp\n");
    AVANCER
    return Rp(pow(n,P()));
  }
  else{
    printf("Rp->eps\n");
    return n;
  }
}    
int F(){
  if(jeton=='('){
    AVANCER
    int result=E();
    TEST_AVANCE(')')
    return result;
  }
  else
    if(isdigit(jeton)){
      printf("F->%d\n",JETON);
      int result=JETON;
      AVANCER
      return result;
    }
    else ERREUR_SYNTAXE
}

int main(){
  AVANCER
  int result=E();
  if(jeton==EOF||jeton=='\n')
    printf("\nMot reconnu : result=%d\n",result);
  else ERREUR_SYNTAXE
}
