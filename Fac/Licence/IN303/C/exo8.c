#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* env[]){
float t=0;
int i;
for(i=1;i<argc;i++)
t+=atoi(argv[i]);
printf("%f",(t/(argc-1)));
}


