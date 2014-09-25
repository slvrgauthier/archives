#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[], char* env[]) {
  char buffer[1024];
  char* dir=getcwd(buffer,1024);
  printf("Le dossier \"%s\" ",dir);
  int r=0;
  
  int i=0;
  while(strstr(env[i],"PATH=.")==NULL)
    i++;
  char* path=env[i];
  while(strtok(path,":")!=NULL && path!=env[i+1]) {
    if(strstr(path,dir)!=NULL && strlen(path)==strlen(dir))
      r=1;
    path+=strlen(path)+1;
  }
  if(r==1)
    printf("est");
  else
    printf("n'est pas");
  printf(" dans la variable PATH.\n");
  return 0;
}
