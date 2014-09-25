#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
  pid_t Pid;
  switch(Pid = fork()){
    case -1:{
      printf("Probleme : echec du fork") ;
      break ;
    }
    case 0:{
      printf("du descendant : valeur de retour de fork() : %d\n", Pid);
      printf("du descendant : je suis %d de parent %d \n", getpid(),getppid()) ;
      break ;
    }
    default:{
      printf("du parent : valeur de retour de fork() : %d\n", Pid);
      printf("du parent : je suis %d de parent %d \n",getpid(), getppid());
      pid_t mortAnnoncee=waitpid(Pid,NULL,0) ;
      printf("du parent : mort annoncee de : %d \n",mortAnnoncee);
      break ;
    }
  }
}
