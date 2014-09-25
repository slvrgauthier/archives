#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* env[]){
  FILE* f = fopen(argv[1],"r+");
  int T[7]={256,12546,58495,-1,0,18,511};
  for(int i=0; i<7 ; i++)
    fwrite(&T[i],2,1,f);
  fclose(f);
}

