%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "arbin.h"

#include "string.h"
union{
  long int i;
  double d;
  char* s;
}yylval;

#define AVANCER {jeton=getchar();numcar++;}
#define TEST_AVANCE(prevu) {if (jeton==(prevu)) AVANCER else ERREUR_SYNTAXE}
#define ERREUR_SYNTAXE {printf("\nMot non reconnu : erreur de syntaxe au caractère numéro %d, de jeton %d \n",numcar,jeton); exit(1);}
#define JETON construire(jeton-'0',NULL,NULL)

Arbin E();Arbin Re(Arbin n);Arbin T();Arbin Rt(Arbin n);Arbin F();Arbin Rp(Arbin n);Arbin 
P();

int jeton;
int numcar=0;

Arbin E(){
  printf("E->TRe\n");
  return Re(T());
}
Arbin Re(Arbin n){
  if(jeton=='+'){
    printf("Re->+TRe\n");
    AVANCER
    return construire('+',n,Re(T()));
  }
  else if(jeton=='-'){
    printf("Re->-TRe\n");
    AVANCER
    return construire('-',n,Re(T()));
  }
  else{
    printf("Re->eps\n");
    return n;
  }
}
Arbin T(){
  printf("T->PRt\n");
  return Rt(P());
}
Arbin Rt(Arbin n){
  if(jeton=='*'){
    printf("Rt->*PRt\n");
    AVANCER
    return construire('*',n,Rt(P()));
  }
  if(jeton=='/'){
    printf("Rt->/PRt\n");
    AVANCER
    return construire('/',n,Rt(P()));
  }
  else{
    printf("Rt->eps\n");
    return n;
  }
}
Arbin P(){
  printf("P->FRp\n");
  return Rp(F());
}
Arbin Rp(Arbin n){
  if(jeton=='^'){
    printf("Rp->^PRp\n");
    AVANCER
    return construire('^',n,Rp(P()));
  }
  else{
    printf("Rp->eps\n");
    return n;
  }
}    
Arbin F(){
  if(jeton=='('){
    AVANCER
    Arbin result=E();
    TEST_AVANCE(')')
    return result;
  }
  else
    if(isdigit(jeton)){
      printf("F->%d\n",JETON);
      Arbin result=construire(jeton,NULL,NULL);
      AVANCER
      return result;
    }
    else ERREUR_SYNTAXE
}
%}
%option noyywrap
%%
0|[1-9][0-9]* {yylval.d=(double)strtol(yytext,NULL,10); return 304;}
0[1-7][0-7]* {yylval.i=strtol(yytext,NULL,8); return 305;}
0x[1-9a-fA-F][0-9a-fA-F]* {yylval.i=strtol(yytext,NULL,16); return 306;}
([1-9][0-9]*\.[0-9]*|\.[0-9]+)([eE][-+]?[1-9][0-9]*)? {yylval.d=strtod(yytext,NULL); return 307;}
"//".*\n {return -2;}
"/*"([^*]|"*"+[^*/])*"*"+"/" {return -3;}
[a-zA-Z][0-9a-zA-Z_]* {yylval.s=yytext; return 308;}
.|\n {return yytext[0];}
%%
int main(){
  printf("Entrez le calcul à effectuer (suivi d'entrée) :\n");
  AVANCER
  Arbin result=E();
  if(jeton=='\n') {
    printf("\nVoici l'arbre syntaxique abstrait associé :\n\n");
    affichera(result);
  }
  else ERREUR_SYNTAXE
  return 0;
}
