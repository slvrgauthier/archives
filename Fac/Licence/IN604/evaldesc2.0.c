%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "string.h"
union{
  long int i;
  double d;
  char* s;
}yylval;

#define AVANCER { jeton=yylex();}
#define TEST_AVANCE(prevu) {if (jeton==(prevu)) AVANCER else ERREUR_SYNTAXE}
#define ERREUR_SYNTAXE {printf("\nMot non reconnu : erreur de syntaxe au caractère numéro %d, de jeton %d \n",numcar,jeton); exit(1);}
#define JETON (double)yylval

double E();double Re(double g);double T();double Rt(double g);double F();double Rp(double g);double 
P();

double jeton;

double E(){
  printf("E->TRe\n");
  return Re(T());
}
double Re(double g){
  if(jeton=='+'){
    printf("Re->+TRe\n");
    AVANCER
    return Re(g+T());
  }
  else if(jeton=='-'){
    printf("Re->-TRe\n");
    AVANCER
    return Re(g-T());
  }
  else{
    printf("Re->eps\n");
    return g;
  }
}
double T(){
  printf("T->PRt\n");
  return Rt(P());
}
double Rt(double g){
  if(jeton=='*'){
    printf("Rt->*PRt\n");
    AVANCER
    return Rt(g*P());
  }
  if(jeton=='/'){
    printf("Rt->/PRt\n");
    AVANCER
    return Rt(g/P());
  }
  else{
    printf("Rt->eps\n");
    return g;
  }
}
double P(){
  printf("P->FRp\n");
  return Rp(F());
}
double Rp(double g){
  if(jeton=='^'){
    printf("Rp->^PRp\n");
    AVANCER
    return Rp(pow(g,P()));
  }
  else{
    printf("Rp->eps\n");
    return g;
  }
}
double F(){
  if(jeton=='('){
    AVANCER
    double result=E();
    TEST_AVANCE(')')
    return result;
  }
  else
    if(jeton==304 || jeton==307){
      printf("F->%d\n",JETON);
      double result=JETON;
      AVANCER
      return result;
    }
    else ERREUR_SYNTAXE
}
%}
%option noyywrap
%%
0|[1-9][0-9]* {yylval.i=strtol(yytext,NULL,10); return 304;}
0[1-7][0-7]* {yylval.i=strtol(yytext,NULL,8); return 305;}
0x[1-9a-fA-F][0-9a-fA-F]* {yylval.i=strtol(yytext,NULL,16); return 306;}
([1-9][0-9]*\.[0-9]*|\.[0-9]+)([eE][-+]?[1-9][0-9]*)? {yylval.d=strtod(yytext,NULL); return 307;}
"//".*\n {return -2;}
"/*"([^*]|"*"+[^*/])*"*"+"/" {return -3;}
[a-zA-Z][0-9a-zA-Z_]* {yylval.s=yytext; return 308;}
.|\n {return yytext[0];}
%%
int main(){
  AVANCER
  double result=E();
  if(jeton==EOF||jeton=='\n')
    printf("\nMot reconnu : result=%d\n",result);
  else ERREUR_SYNTAXE
  return 0;
}
