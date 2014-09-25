/* Lecteur sur un tube nommé : réalisation de rendez-vous avec l'écrivain.
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

int main(int n, char * argv[]){
  if (n != 2){
    fprintf(stderr,"Syntaxe : %s nomdutube\n",argv[0]);
    exit(1);
  }
  if(mkfifo(argv[1], S_IRUSR|S_IWUSR|S_IROTH|S_IWOTH)==-1 && errno!=EEXIST){
    perror("Erreur mkfifo - on continue");
  }
  int tube=open(argv[1], O_RDONLY);
  if (tube == -1){
    perror("Erreur ouverture tube");
    exit(2);
  }
  int K=1024,nb;
  char msg[K+1];
  while(0!=(nb=read(tube,msg,K))){
    msg[nb]='\0';
    printf(msg);
  }
  unlink(argv[1]);
  return 0;
}
