CC=gcc
CFLAGS=-std=c99
LEX=flex
YACC=bison
YACCFLAGS=-ydtv
#-y a la yacc : y.tab.c; -d genere y.tab.h; -t debogage possible; -v verbose
calc : calc.y calc.l
	@echo debut $(YACC)-compil : $<
	$(YACC) $(YACCFLAGS) $<
	$(LEX) calc.l
	@echo debut compil c avec edition de liens de y.tab.c
	$(CC) $(CFLAGS) -o $@ y.tab.c lex.yy.c -lm
	@echo fin $(YACC)-compil de : $<
	@echo Vous pouvez executer : $@