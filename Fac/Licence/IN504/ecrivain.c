/* Ecrivain sur un tube nommé : réalisation de rendez-vous avec le lecteur.
 * Chacun des deux essaie de créer le tube nommé par mkfifo. S'il existe déjà, on
 * continue bien sûr. Donc l'idée est juste de créer le tube par le premier
 * processus. On lit ligne par ligne.
 */
#include <sys/types.h>//tous appels
#include <sys/stat.h>//mkfifo, open
#include <stdio.h>//perror
#include <errno.h>//errno
#include <stdlib.h>
#include <string.h>
#include <unistd.h>//read, write
#include <fcntl.h>//open
#include <signal.h>

char nomtube[1024];

void gst(int sig){ /* gestionnaire du signal SIGPIPE */
  unlink(nomtube); /* le lecteur s'est terminé */
  exit(3);
}

int main(int n, char * argv[]){
  if (n != 2){
    fprintf(stderr,"Syntaxe : %s nomdutube\n",argv[0]);
    exit(1);
  }
  if(mkfifo(argv[1], S_IRUSR|S_IWUSR|S_IROTH|S_IWOTH)==-1 && errno!=EEXIST){
    perror("Erreur mkfifo - on continue");
  }
  int tube=open(argv[1], O_WRONLY);
  if (tube == -1){
    perror("Erreur ouverture tube");
    exit(2);
  }
  strcpy(argv[1],nomtube); /* pour le gestionnaire */
  struct sigaction action;
  action.sa_handler = gst;
  sigaction(SIGPIPE, &action, NULL); /* si signal alors supp le tube */
  
  int K=1024;
  char msg[K+1],*res;
  printf(">");res=gets(msg); /* res est NULL si EOF */
  while(res){
    write(tube, msg, strlen(msg));
    printf(">");res=gets(msg);
  }
  return 0;
}
