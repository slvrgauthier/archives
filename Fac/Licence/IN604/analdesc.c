#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define AVANCER {jeton=getchar();numcar++;}
#define TEST_AVANCE(prevu) {if (jeton==(prevu)) AVANCER else ERREUR_SYNTAXE}
#define ERREUR_SYNTAXE {printf("\nMot non reconnu : erreur de syntaxe au caractère numéro %d, de jeton %d \n",numcar,jeton); exit(1);}

void E();void R();void T();void S();void F();

int jeton;
int numcar=0;

void E(){
  T();
  R();
}
void R(){
  if(jeton=='+'){
    AVANCER
    T();
    R();
  }
  else ;
}
void T(){
  F();
  S();
}
void S(){
  if(jeton=='*'){
    AVANCER
    F();
    S();
  }
  else ;
}
void F(){
  if(jeton=='('){
    AVANCER
    E();
    TEST_AVANCE(')')
  }
  else
    if(isdigit(jeton))
      AVANCER
    else ERREUR_SYNTAXE
}

int main(){
  AVANCER
  E();
  if(jeton==EOF||jeton=='\n')
    printf("\nMot reconnu\n");
  else ERREUR_SYNTAXE
}
