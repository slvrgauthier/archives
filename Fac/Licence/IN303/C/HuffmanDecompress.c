#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//              Using the software : Decompression [path in] [path out]

// ==============================    Global Var :   ==============================


// ==============================    Prototypes :   ==============================
short int fgetshi(FILE* f);
int fgeti(FILE* f);


// ==============================       Main :      ==============================
int main(int argc, char*argv[], char*env[]){
  if (argc < 3){
    printf("Need two file paths to decompress.\n");
    exit(1);
  }
  FILE* f = fopen(argv[1],"r+");
  FILE* g = fopen(argv[2], "r+");
  if (f == NULL){
    printf("Cannot open file (IN).\n");
    exit(2);
  }
  if (g == NULL){
    printf("Cannot open file (OUT).\n");
    exit(3);
  }
// Reading the binary file :
//tree :
  int nbNoeud = fgetshi(f);
  int ind[nbNoeud];
  int fg[nbNoeud];
  int fd[nbNoeud];
  int parent[nbNoeud];
  for(int i=0 ; i<nbNoeud ; i++){
    ind[i] = fgetshi(f);
    fg[i] = fgetshi(f);
    fd[i] = fgetshi(f);
    parent[i] = fgetshi(f);
    //printf("%i, %i, %i, %i\n",ind[i],fg[i],fd[i],parent[i]);
  }
  int indRacine = ind[nbNoeud-1];
  
//text :
  int nbChar = fgeti(f);
  char c = fgetc(f);
  int indNoeud = indRacine, masque, i, tot = nbChar, percent1 = 0, percent2 = 0;
  while(nbChar != 0){
    masque = 8;
    while((masque != 0) && (nbChar != 0)){
      for(int j=0 ; j<nbNoeud ; j++)
	  if(ind[j] == indNoeud)
	    i = j;
      if((c & (1 << (masque-1))) == (1 << (masque-1)))
	indNoeud = fd[i];
      else
	indNoeud = fg[i];
      for(int j=0 ; j<nbNoeud ; j++)
	  if(ind[j] == indNoeud)
	    i = j;
      if((fg[i] == -1) && (fd[i] == -1)){
	fwrite(&indNoeud, sizeof(char), 1, g);
	nbChar--;
	percent2 = 100-nbChar*100/tot;
	if((percent2 != percent1) && (percent2 % 10 == 0)){
	  printf("0 [");
	  for(int j=0 ; j<percent2/10 ; j++)
	    printf("-");
	  printf("] %i%\n",percent2);
	  percent1 = percent2;
	}
	indNoeud = indRacine;
      }
      masque--;
    }
    c = fgetc(f);
  }
  
// Closing :
  fclose(f);
  fclose(g);
  return 0;
}

// ==============================    Functions :    ==============================
short int fgetshi(FILE* f){
  return (fgetc(f) + (fgetc(f) << 8));
}

int fgeti(FILE* f){
  return (fgetc(f) + (fgetc(f) << 8) + (fgetc(f) << 16) + (fgetc(f) << 24));
}

