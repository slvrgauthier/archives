all : expreg

expreg : arbin.o expreg.o
	gcc -std=c99 -o expreg arbin.o expreg.o 
arbin.o : arbin.c
	gcc -std=c99 -o arbin.o -c arbin.c
expreg.o : y.tab.c
	gcc -std=c99 -o expreg.o -c y.tab.c
y.tab.c : expreg.y
	bison -y expreg.y