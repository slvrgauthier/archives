#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[], char* env[]) {
  if(argc<2){
    printf("Aucun fichier à ouvrir...\n");
    exit(1);
  }
  
  int f=open(argv[1],O_RDONLY);
  if(f<0) {
    printf("Ouverture de fichier impossible...");
    exit(2);
  }
  
  int ascii[256];
  for(int i=0;i<256;i++)
    ascii[i]=0;
  
  char c;
  while(0<read(f,&c,1))
    ascii[(int)c]++;
    
  close(f);
  for(int i=0;i<256;i++)
    if(ascii[i])
      printf("%c:%d ",i,ascii[i]);
  printf("\n");
  
  return 0;
}
