%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "arbin.h"
int yylex();
void yyerror();
%}
%union{
Arbin a;
int i;
}
%type<a> e
%token<i> SYMB
%left '|'
%left CONCAT SYMB
%left '*'
%%
liste : liste ligne {}
      | {}
      ;
ligne : e '\n' {affichera($1);}
      | '\n' {}
      | error '\n' {yyerrok;}
      ;
e : e '|' e {$$=construire('|',$1,$3);}
  | e '*' {if(racine($1)=='*') $$=$1; else $$=construire('*',$1,NULL);}
  | '(' e ')' {$$=$2;}
  | e e %prec CONCAT {$$=construire('.',$1,$2);}
  | SYMB {$$=construire($1,NULL,NULL);}
  ;
%%
int yylex(){
  char c=getchar();
  if(c=='0' || c=='@' || islower(c)) {
    yylval.i=c;
    return SYMB;
  }
  else
    return c;
}
void yyerror(){
  fprintf(stderr,"erreur de syntaxe");
}
int main(){
  printf("Entrez une expression régulière : ");
  return yyparse();
}
