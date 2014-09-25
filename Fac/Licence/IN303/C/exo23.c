#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[], char* env[]){
  if (argc < 2){
    fprintf(stderr, "Nombre d'arguments trop petit !\n");
    exit(1);
  }
  int f = open(argv[1], O_RDONLY);
  if (f < 0){
    fprintf(stderr, "Impossible d'ouvrir le fichier !\n");
    exit(2);
  }
  int i = 0;
  char c;
  while (read(f, &c, 1) > 0)
    i++;
  close(f);
  printf("Le fichier contient %i caractères.\n",i);
  return 0;
}

