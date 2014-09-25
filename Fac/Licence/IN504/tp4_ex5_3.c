#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char ** argv){
  printf("je vais demander mon recouvrement par gcc moi-même !\n");
  char *s=malloc(strlen(argv[0])+3); // .c
  strcat(strcpy(s,argv[0]),".c");
  int i = execlp("gcc","gcc","-o",argv[0],s,NULL) ;
  if (i<0)
    printf("Erreur de recouvrement !\n");
  else
    printf("Impossible !");
}
