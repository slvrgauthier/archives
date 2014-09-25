#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
  if(argc!=2){
    fprintf(stderr,"utilisation: %s chemin\n", argv[0]);
    exit(1);
  }
  DIR * rep=opendir(argv[1]);
  if (rep==NULL){
    fprintf(stderr,"Impossible d'ouvrir le répertoire : %s\n",argv[1]);
    exit(2);
  }
  else{
    struct dirent * entree; /* entrée de répertoire */
    char chemin[512]; /* chemin d'une entrée */
    struct stat etat; /* état de l'inode */
    while ((entree=readdir(rep)) != NULL){
      printf("%ld ",entree->d_ino) ; /* inode number : long en décimal */
      strcat(strcat(strcpy(chemin,argv[1]),"/"),entree->d_name);
      if (lstat(chemin,&etat)<0){
        fprintf(stderr,"Impossible d'ouvrir le fichier : %s\n",chemin);
        exit(3);
      }
      if ((etat.st_mode&S_IFMT)==S_IFDIR){ printf("d"); } 
      else if(S_ISREG(etat.st_mode)){ printf("-"); } 
      else if(S_ISLNK(etat.st_mode)){ printf("l"); } 
      else { printf("?"); }
      if(etat.st_mode & S_IRUSR) printf("r"); else printf("-");
      if(etat.st_mode & S_IWUSR) printf("w"); else printf("-");
      if(etat.st_mode & S_IXUSR) printf("x"); else printf("-");
      if(etat.st_mode & S_IRGRP) printf("r"); else printf("-");
      if(etat.st_mode & S_IWGRP) printf("w"); else printf("-");
      if(etat.st_mode & S_IXGRP) printf("x"); else printf("-");
      if(etat.st_mode & S_IROTH) printf("r"); else printf("-");
      if(etat.st_mode & S_IWOTH) printf("w"); else printf("-");
      if(etat.st_mode & S_IXOTH) printf("x"); else printf("-");
      printf(" %s\n",entree->d_name);
    }
    closedir(rep);
  }
  return 0;
}
