#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv, char** arge){
  if(argc!=3){
    printf("Syntaxe incorrecte : %s source.txt destination.txt\n", argv[0]);
    return 1;
  }
  int source=open(argv[1],O_RDONLY);
  if (source<0){
    printf("Impossible d'ouvrir %s !\n", argv[1]);
    return 2;
  }
  int dest=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0x644);
  if (dest<0){
    printf("Impossible d'ouvrir %s !\n", argv[2]);
    return 3;
  }
  char c;
  while(0<read(source,&c,1)){
    write(dest,&c,1);
  }
  close(dest);
  close(source);
}
