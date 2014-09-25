%{
#include <math.h>
#include "typedef.h"
int errSemantiq=0;
#define DIVPARO 1
#define LOGNEG 2
#define YYSTYPE double
int yylex(void); void yyerror(char* s);
%}
%token LITFLOT SIN COS EXP LN PI QUIT HELP AVG REF
%left '+' '-'
%left '*' '/' '%'
%right MOINSUNAIRE
%right '^'
%%
liste 	:				{}
	| liste ligne			{}
	;
ligne	: '\n'				{}
	| error '\n'			{ yyerrok; }
	| expr '\n'			{ if(!errSemantiq) printf("Resultat : %10.2f\n",$1); else if(errSemantiq==DIVPARO){ printf("Erreur semantique : division par 0 !\n"); errSemantiq=0; } else { printf("Erreur semantique : logarithme d'un negatif ou nul !\n"); errSemantiq=0; } }
	| QUIT '\n' 			{ return 0; }
	| HELP '\n' 			{ printf("\tAide de la calculette\n=====================\n...\n"); }
	;
expr	: '(' expr ')'			{ $$=$2; }
	| expr '+' expr			{ $$=$1+$3; }
	| expr '-' expr			{ $$=$1-$3; }
	| expr '*' expr			{ $$=$1*$3; }
	| expr '/' expr			{ if($3!=0) $$=$1/$3; else errSemantiq=DIVPARO; }
	| expr '^' expr			{ $$=pow($1,$3); }
	| expr '%' expr			{ if($3!=0) $$=fmod($1,$3); else errSemantiq=DIVPARO; }
	| '-' expr %prec MOINSUNAIRE	{ $$=-$2; }
	| SIN '(' expr ')'		{ $$=sin(PI/180*$3); }
	| COS '(' expr ')'		{ $$=cos(PI/180*$3); }
	| EXP '(' expr ')'		{ $$=exp($3); }
	| LN '(' expr ')'		{ if($3>0) $$=log($3); else errSemantiq=LOGNEG; }
	| AVG '(' le ')'		{ cell* p=$3; float acc=0; int cpt=0; while(p){acc+=p->val;p=p->suiv;cpt++;}if(cpt!=0)$$=(acc/cpt);else errSmantiq=DIVPARO;}
	| PI				{ $$=PI; }
	| LITFLOT			{ $$=$1; }
	;
le	: expr se			{ cell* p=malloc(sizeof(cell));p->val=$1;p->suiv=$2;$$=p;}
	|				{ $$=NULL; }
	;
se	: ',' expr se			{ cell* p=malloc(sizeof(cell));p->val=$2;p->suiv=$3;$$=p;}
	|				{ $$=NULL; }
	;
%%
void yyerror(char* s) {fprintf(stderr,"%s\n",s);}
int main(void){yydebug=0; return yyparse();}
