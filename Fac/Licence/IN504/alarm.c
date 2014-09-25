#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include <stdlib.h>

struct sigaction action; /* variable globale car accédée dans gst */

void gst(int sig){
  static int cpt=1;
  switch(cpt) {
    case 1 :
      printf("Veuillez repondre plus vite !\n");
      cpt++;
      alarm(3);
      return;
      break;
    case 2 :
      printf("Veuillez repondre encore plus vite !\n");
      cpt++;
      alarm(3);
      return;
      break;
    case 3 :
      printf("Trop tard\n");
      exit(1);
      break;
  }
}

int main(int n, char **argv){
  action.sa_handler=gst;
  action.sa_flags=SA_RESTART; /* redémarrer l'appel syst */
  sigaction(SIGALRM, &action, NULL);
  printf("Entrez un entier dans les 10 secondes : ");
  alarm(3);
  int i;
  scanf("%i", &i);
  alarm(0); /* débrancher l'alarme */
  printf("bravo pour votre célérité ! entier saisi : %d\n",i);
  return 0;
}
