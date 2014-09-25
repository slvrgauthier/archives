#include <stdio.h>
#include <stdlib.h>

// Prototypes :
void OptLign(int nbLign, char* buffer, FILE* f);
void OptChar(int nbChar, char* buffer, FILE* f);

// Main :
int main(int argc, char*argv[], char*env[]){
  FILE* f;
  if(argv[argc-1][0] == '-')
    f = stdin;
  else
    f = fopen(argv[argc-1],"r+");
  char* buffer = malloc(1024);
  for(int i=1 ; i<argc ; i++){
    fseek(f, 0, SEEK_SET);
    if(argv[i][0] == '-'){
      if(argv[i][1] == 'c')
        OptChar(atoi(argv[i]+2), buffer, f);
      else
        OptLign(atoi(argv[i]+1), buffer, f);
    }
  }
  free(buffer);
  fclose(f);
  return 0;
}

// Fonctions :
void OptLign(int nbLign, char* buffer, FILE* f){
  char c = 'a';
  int i=0, j=0;
  while((c != EOF) && (i < nbLign)){
    c = fgetc(f);
    while((c != EOF) && (c != '\n')){
      buffer[j] = c;
      c = fgetc(f);
      j++;
    }
    buffer[j] = '\0';
    j = 0;
    printf("%s\n",buffer);
    i++;
  }
}

void OptChar(int nbChar, char* buffer, FILE* f){
  char c = 'a';
  int j=0;
  while((c != EOF) && (j < nbChar)){
    c = fgetc(f);
    buffer[j] = c;
    j++;
  }
  buffer[j] = '\0';
  printf("%s\n",buffer);
}

