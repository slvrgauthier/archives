#include <stdio.h>
#include <stdlib.h>
#include "vecteur.h"


int main(int argc, char* argv[]){
  
  vecteur A=vecteur_creer();
  
  if(vecteur_taille(A)==0)printf("Initialisation de A - taille correcte\n");
  else printf("Initialisation de A - taille incorrecte\n");
  
  int a=3, b=5, c=9, d=13, e=15, f=19;
  
  printf("Ajout de %d dans A. Taille de A = %d.\n",a,vecteur_ajout_fin(A,&a));
  printf("Ajout de %d dans A. Taille de A = %d.\n",b,vecteur_ajout_fin(A,&b));
  printf("Ajout de %d au debut de A. Taille de A = %d.\n",c,vecteur_ajout_debut(A,&c));
  printf("Ajout de %d au debut de A. Taille de A = %d.\n",d,vecteur_ajout_debut(A,&d));
  printf("Ajout de %d dans A a l'indice 1. Taille de A = %d.\n",e,vecteur_ajout(A,&e,1));
  printf("Ajout de %d dans A a l'indice 3. Taille de A = %d.\n",f,vecteur_ajout(A,&f,3));
  
  for(unsigned int i=0; i<vecteur_taille(A); i++){
    printf("A[%d] = %d.\n",i,*(int*)vecteur_lire(A,i));
  }
  
  printf("Retrait de %d dans A.\n",*(int*)vecteur_retirer_fin(A));
  
  vecteur B=vecteur_clone(A);
  if(vecteur_taille(B)==vecteur_taille(A))printf("Initialisation de B par copie de A - taille correcte\n");
  else printf("Initialisation de B par copie de A - taille incorrecte\n");
  
  if(vecteur_detruire(A)==0)printf("A detruit\n");  
  else printf("Probleme a la destruction de A\n");
  
  printf("Retrait de %d a l'indice 2 dans B.\n",*(int*)vecteur_retirer(B,2));
  printf("Retrait de %d du debut de B.\n",*(int*)vecteur_retirer_debut(B));
  
  char* ctemp=vecteur_chaine(B);
  printf("B: %s\n",ctemp);
  free(ctemp);
  
  for(unsigned int i=0; i<vecteur_taille(B); i++){
    printf("B[%d] = %d.\n",i,*(int*)vecteur_lire(B,i));
  }
  
  if(vecteur_detruire(B)==0)printf("B detruit\n");  
  else printf("Probleme a la destruction de B\n");
  
  return 0;
}



