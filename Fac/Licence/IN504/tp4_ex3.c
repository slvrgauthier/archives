#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int statique = 1;

int main(int argc, char ** argv){
  int locale = 2;
  int *pi=malloc(sizeof(int));
  *pi=3; /* Tas */
  if(argc!=2){
    printf("Syntaxe incorrecte : %s fic.txt\n", argv[0]);
    return 1;
  }
  int f=open(argv[1],O_RDONLY);
  if (f<0){
    printf("Impossible d'ouvrir %s !\n", argv[1]);
    return 2;
  }
  printf("Avant fork - Je suis : %d\n",getpid());
  printf("Avant fork - statique=%d; Adresse de statique=%p\n",statique,&statique);
  printf("Avant fork - locale=%d; Adresse de locale=%p\n",locale,&locale);
  printf("Avant fork - *pi=%d; Adresse de *pi=%p; Adresse de pi=%p\n",*pi,pi,&pi);
  printf("Avant fork - f=%d\n",f);
  char s[6];
  strcpy(s,"xxxxx");
  int i=read(f,s,5);
  if (i!=5){
    printf("Impossible de lire dans %s !\n", argv[1]);
    return 6;
  }
  printf("Avant fork - lecture de 5 octets : %s\n",s);
  pid_t Pid = fork();
  switch(Pid){
    case -1: // echec du fork
      printf("Probleme : echec du fork");
      return 3;
    break ;
  case 0: // c'est le fils
    printf("\nFils - Je suis : %d\n", getpid());
    printf("Fils - statique=%d; Adresse de statique=%p\n",statique,&statique);
    printf("Fils - locale=%d; Adresse de locale=%p\n",locale,&locale);
    printf("Fils - *pi=%d; Adresse de *pi=%p; Adresse de pi=%p\n",*pi,pi,&pi);
    printf("Fils - f=%d\n",f);
    char s[3];
    strcpy(s,"xx");
    int i=read(f,s,2);
    if (i!=2){
      printf("Impossible de lire dans %s !\n", argv[1]);
      return 6;
    }
    printf("Fils - lecture de 2 octets : %s\n",s);
    statique+=10;locale+=10; *pi+=10;
    printf("Fils après - statique=%d; Adresse de statique=%p\n",statique,&statique);
    printf("Fils après - locale=%d; Adresse de locale=%p\n",locale,&locale);
    printf("Fils après - *pi=%d; Adresse de *pi=%p; Adresse de pi=%p\n",*pi,pi,&pi);
    printf("Fils après - f=%d\n",f);
    sleep(6) ;
    break ;
    
    default: // c'est le pere
      statique+=100;locale+=100;
      (*pi)+=100;
      printf("Père après - statique=%d; Adresse de statique=%p\n",statique,&statique);
      printf("Père après - locale=%d; Adresse de locale=%p\n",locale,&locale);
      printf("Père après - *pi=%d; Adresse de *pi=%p; Adresse de pi=%p\n",*pi,pi,&pi);
      printf("Père après - f=%d\n",f);
      close(f);
      break ;
  }
}
