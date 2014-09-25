%{
#include <stdio.h>
#include <unistd.h>
#include "string.h"
union{
  long int i;
  double d;
  char* s;
}yylval;
%}
%option noyywrap
%%
if {return 300;}
then {return 301;}
else {return 302;}
throw {return 303;}
0|[1-9][0-9]* {yylval.i=strtol(yytext,NULL,10); return 304;}
0[1-7][0-7]* {yylval.i=strtol(yytext,NULL,8); return 305;}
0x[1-9a-fA-F][0-9a-fA-F]* {yylval.i=strtol(yytext,NULL,16); return 306;}
([1-9][0-9]*\.[0-9]*|\.[0-9]+)([eE][-+]?[1-9][0-9]*)? {yylval.d=strtod(yytext,NULL); return 307;}
"//".*\n {return -2;}
"/*"([^*]|"*"+[^*/])*"*"+"/" {return -3;}
[a-zA-Z][0-9a-zA-Z_]* {yylval.s=yytext; return 308;}
.|\n {return yytext[0];}
%%
int main() {
  int j;
  char *invite="Saisissez un mot reconnu par l'automate, suivi de EOF (CTRL-D) : ";
  char* jeton;
  printf("%s",invite);
  while((j=yylex())) {
    switch(j){
      case 300 : jeton="IF"; break;
      case 301 : jeton="THEN"; break;
      case 302 : jeton="ELSE"; break;
      case 303 : jeton="THROW"; break;
      case 304 : jeton="INT"; break;
      case 305 : jeton="OCTO"; break;
      case 306 : jeton="HEXA"; break;
      case 307 : jeton="FLOAT"; break;
      case 308 : jeton="ID"; break;
    }
    if(j>=300)
      printf("Lexeme : %s ; Jeton : %s\n%s",yytext,jeton,invite);
    else if(j>20)
      printf("Lexeme : %s ; Jeton : %i\n%s",yytext,j,invite);
    else if(j!=10)
      printf("Contenu filtré par l'automate...\n%s",invite);
    else
      printf("%s",invite);
  }
  printf("\nFin d'analyse...\n");
}
