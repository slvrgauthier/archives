#include <stdio.h>
#include <stdlib.h>

// Prototypes :
void OptLign(int nbLign, FILE* f);
void OptChar(int nbLign, FILE* f);

// Main :
int main(int argc, char*argv[], char*env[]){
  FILE* f;
  if(argv[argc-1][0] == '-')
    f = stdin;
  else
    f = fopen(argv[argc-1],"r+");
  for(int i=1 ; i<argc ; i++){
    fseek(f, 0, SEEK_SET);
    if(argv[i][0] == '-'){
      if(argv[i][1] == 'c')
        OptChar(atoi(argv[i]+2), f);
      else
        OptLign(atoi(argv[i]+1), f);
    }
  }
  fclose(f);
  return 0;
}

// Fonctions :
void OptLign(int nbLign, FILE* f){
  char** file = malloc(nbLign * sizeof(char*)); // file[n] == file [0]
  int tete = 0, queue = 0, tt = nbLign + 1;
  for(int i=0 ; i<tt ; i++)
    file[i] = malloc(1024);
  while(fgets(file[queue], 1024, f) != NULL){
    queue = (queue+1)%tt;
    if(queue == tete)
      tete = (tete+1)%tt;
  }
  while(tete != queue){
    printf("%s",file[tete]);
    tete = (tete+1)%tt;
  }
  printf("\n");
  for(int i=0 ; i<tt ; i++)
    free(file[i]);
  free(file);
}

void OptChar(int nbChar, FILE* f){
  char* file = malloc(nbChar * sizeof(char)); // file[n] == file [0]
  int tete = 0, queue = 0, tt = nbChar + 1;
  while((file[queue]=fgetc(f)) != EOF){
    queue = (queue+1)%tt;
    if(queue == tete)
      tete = (tete+1)%tt;
  }
  while(tete != queue){
    printf("%c",file[tete]);
    tete = (tete+1)%tt;
  }
  printf("\n");
  free(file);
}

