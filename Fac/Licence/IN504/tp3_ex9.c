#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv, char** arge){
  if(argc!=3 || strlen(argv[2])!=1){
    printf("Syntaxe incorrecte : %s fic.txt c\n", argv[0]);
    return 1;
  }
  int f=open(argv[1],O_RDONLY);
  if (f<0){
    printf("Impossible d'ouvrir %s !\n", argv[1]);
    return 2;
  }
  char x=argv[2][0]; //printf("x=%c; ",x);
  int debut=0;
  int fin=lseek(f,0,SEEK_END); //printf("fin:%d; ",fin);
  if (fin==-1){
    printf("Impossible de se déplacer dans %s !\n", argv[1]);
    return 3;
  }else if (fin==0){
    printf("Fichier vide : %s !\n", argv[1]);
    return 4;
  }
  int milieu,i;
  char c;
  do {
    milieu=(debut+fin)/2;
    //printf("milieu=%d; ",milieu);
    i=lseek(f,milieu,SEEK_SET);
    // se placer au milieu
    if (i==-1){
      printf("Impossible de se déplacer en %d dans %s !\n",milieu, argv[1]);
      return 5;
    }
    i=read(f,&c,1); //printf("c=%c; ",c);
    if (i!=1){
      printf("Impossible de lire dans %s !\n", argv[1]);
      return 6;
    }
    if(c>x){
      fin=milieu-1;
    }else if(c<x){
      debut=milieu+1;
    }
  }while(c!=x && debut<=fin);
  close(f);
  if(c==x)
    printf("Le caractère %c est en position %d !\n",x, milieu);
  else
    printf("Le caractère %c est introuvable !\n",x);
}
