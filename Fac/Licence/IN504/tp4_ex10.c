#include <stdio.h>
#include <stdlib.h> // malloc
#include <unistd.h> // exec
#include <string.h> // str..
#include <sys/types.h> //wait
#include <sys/wait.h>

int main(int argc, char ** argv){
  char *prompt="slvr@slvr-prompt$";
  char s[1024];
  do{
    printf("%s", prompt);
    scanf("%s",s);
    if(!strcmp(s,"exit"))
      return 0;
    if(!strcmp(s,"PID"))
      printf("Je suis le slvr-prompt numéro %d\n",getpid());
    else {
      pid_t Pid;
      switch(Pid = fork()){
        case -1: printf("Probleme : echec du fork"); break;
        case 0: execlp(s,s,NULL); printf("L'enfant numéro %d est né !\n",getpid()); break;
        default: wait(NULL); printf("Le slvr-prompt numéro %d est de retour !\n",getpid());
      }
    }
  }while(1);
}
