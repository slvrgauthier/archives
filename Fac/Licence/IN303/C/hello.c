#include <stdio.h>

int main (int argc, char*argv[], char*env[]){
int i;
for(i=0;i<argc;i++)
printf("Arg%d : %s\n",i,argv[i]);
while(env[i]!=NULL){
printf("%s\n",env[i]);i++;}
return 0;
}


//gcc -std=99 -Wall -oHELLO HELLO.c


