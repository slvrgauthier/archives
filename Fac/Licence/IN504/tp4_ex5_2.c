#include <stdio.h>
#include <unistd.h>

int main(int argc, char ** argv){
  printf("je vais demander mon recouvrement par ls -l /bin !\n");
  int i = execl("/bin/ls","ls","-l","/bin",NULL) ;
  if (i<0)
    printf("Erreur de recouvrement !\n");
  else
    printf("Impossible !");
}
