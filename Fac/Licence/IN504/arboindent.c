#include <dirent.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parcours(char* rep, int indent){ /* retourne 0 si OK */
  DIR * repCourant=opendir(rep); // ptr sur obj dynam. répertoire courant
  if (repCourant==NULL){
    fprintf(stderr,"Impossible d'ouvrir le répertoire : %s\n",rep);
    return -1;
  }
  char *chemin=(char *)malloc(1024);
  struct dirent *entree;
  struct stat etat; /* pour le lstat */
  while ((entree=readdir(repCourant)) != NULL){ // pour chaque entrée
    strcat(strcat(strcpy(chemin,rep),"/"),entree->d_name);
    // lstat pour ne pas etre embete par les liens
    if(lstat(chemin,&etat)<0){
      fprintf(stderr,"Impossible d'ouvrir le fichier : %s\n",chemin);
    }
    if (S_ISDIR(etat.st_mode) && strcmp(entree->d_name, ".") && strcmp(entree->d_name, "..")){
      int i; 
      for(i=0;i<indent;i++) 
	printf(" "); /* indentation */
      printf("%s\n",chemin);
      parcours(chemin,indent+1);
    }
  }
  free(chemin);
  closedir(repCourant);
  return 0;
}

int main(int argc, char*argv[]){
  if(argc!=2){
    fprintf(stderr,"utilisation: %s repertoire\n", argv[0]);
    exit(1);
  }
  printf("%s\n",argv[1]); /* la racine */
  return parcours(argv[1],1);
}
