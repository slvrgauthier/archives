#include <stdio.h>
#include <unistd.h>

int main(int argc, char ** argv){
  printf("je vais demander mon recouvrement par ls !\n");
  int i = execl("/bin/ls","ls",NULL) ;
  if (i<0)
    printf("Erreur de recouvrement !\n");
  else
    printf("Impossible !");
}
