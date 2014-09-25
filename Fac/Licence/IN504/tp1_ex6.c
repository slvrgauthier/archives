#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[], char*env[]){
  printf("Argv :\nNombre de parametres : %d\n",argc);
  for(int i=0;i<argc;i++)
    printf("Param %d : %s\n",i,argv[i]);
  printf("\nEnv :\n");
  int i=0;
  while(env[i]!=NULL) {
    printf("Param %d : %s\n",i,env[i]);
    i++;
  }
  printf("Nombre de parametres : %d\n",i);
  exit(EXIT_SUCCESS);
}

