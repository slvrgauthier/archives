#include <stdio.h>
#include <stdlib.h>
#include <string.h>

short int fgetshi(FILE* f);

int main(int argc, char* argv[], char* env[]){
  FILE* f = fopen(argv[1], "r+");
  short int T[7];
  for(int i=0 ; i<7 ; i++){
    T[i] = fgetshi(f);
    if(T[i] == 16777470)
      T[i] = -1;
    printf("%i ",T[i]);
  }
  printf("\n");
  fclose(f);
}

int fgeti(FILE* f){
  int res = 0, puis = 0;
  for(int i=0 ; i<3 ; i++){
    res = res + (fgetc(f) << puis);
    puis += 8;
  }
  return res + fgetc(f); // -1 = 16777470
}

short int fgetshi(FILE* f){
  return (fgetc(f) + (fgetc(f) << 8));
}

