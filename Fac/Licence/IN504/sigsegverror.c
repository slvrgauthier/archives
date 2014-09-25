/* sigsegv.cc
Gestion de SIGSEGV en le produisant.
ici avec complément sur errno pour afficher
la valeur de errno et le texte correspondant.
*/
#include<stdio.h>
#include <stdlib.h>
#include<signal.h>
#include<errno.h>
#include <string.h>

void gst (int sig){
  printf("Recu le signal : %d\n",sig);
  printf("Valeur de errno %d; message :%s\n",errno,strerror(errno));
  exit(1);
}

int main(){
  struct sigaction action;
  action.sa_handler = gst;
  sigaction(SIGSEGV, &action, NULL);
  int *pi=NULL;
  printf("ooouuups : %d\n trop tard\n",*pi);
}
