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
  
  int eof=1,pos=0;
  char c[16];
  
  while(0<(eof=read(f,&c,16))) {
    printf("%8.8x: ",pos);
    pos+=16;
    for(int i=0;i<eof;i++) {
      printf("%2.2hhx",c[i]);
      if(i%2)
	printf(" ");
    }
    if(eof<16)
      for(int i=eof;i<16;i++) {
        printf("  ");
	if(i%2)
	  printf(" ");
      }
    printf(" ");
    for(int i=0;i<eof;i++){
      if(c[i]>=0x20 && c[i]<0x7F)
        printf("%c",c[i]);
      else
        printf(".");
    }
    printf("\n");
  }

  
  return 0;
}
