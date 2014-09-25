#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

int main(int argc, char *argv[]){
  if(argc!=3){
    fprintf(stderr,"utilisation: %s chemin nbjours\n", argv[0]);
    exit(1);
  }
  int nbjours=atoi(argv[2]);
  DIR * rep=opendir(argv[1]);
  if (rep==NULL){
    fprintf(stderr,"Impossible d'ouvrir le répertoire : %s\n",argv[1]);
    exit(2);
  }
  struct dirent * entree; /* entrée de répertoire */
  char chemin[512]; /* chemin d'une entrée */
  struct stat etat; /* état de l'inode */
  struct timeval now;
  if (gettimeofday(&now,NULL)<0){
    fprintf(stderr,"Impossible d'obtenir la date système :!\n");
    exit(3);
  }
  while ((entree=readdir(rep)) != NULL){
    strcat(strcat(strcpy(chemin,argv[1]),"/"),entree->d_name);
    if (lstat(chemin,&etat)<0){
      fprintf(stderr,"Impossible d'ouvrir le fichier : %s\n",chemin);
      exit(4);
    }
    if (difftime(now.tv_sec,etat.st_mtime)<nbjours*24*60*60){
      printf("%s %s",entree->d_name, ctime(&(etat.st_mtime)));
    }
  }
  closedir(rep);
  return 0;
}