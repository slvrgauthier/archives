%{
#define YYSTYPE double
#include "typedef.h"
#include "y.tab.h"
#include <stdlib.h>
#include <stdio.h>
%}
chiffre		([0-9])
entier		({chiffre}+)
%option noyywrap
%%
[\t]+							{}
{entier}|{entier}\.{chiffre}*|{chiffre}*\.{entier}	{ yylval=atof(yytext); return (LITFLOT); }
[a-zA-Z]{chiffre}{1,2}					{ return (REF); }
sin							{ return (SIN); }
cos							{ return (COS); }
exp							{ return (EXP); }
ln							{ return (LN); }
avg							{ return (AVG); }
pi							{ return (PI); }
exit|quit						{ return (QUIT); }
aide|help|\?						{ return (HELP); }
.|\n							{ return yytext[0]; }
%%