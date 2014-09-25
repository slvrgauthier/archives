#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "progListeSC.h"

/* *************************  DERNIERLSC ET ESTTRIEELSC ********************************* */
ListeSC dernierLSC(ListeSC L){
  /* Renvoie l'adresse de la dernière cellule de la liste non vide L */
  assert(L!=NULL);
  while(L->succ != NULL)
    L=L->succ;
  return L;
}

int estTrieeLSC(ListeSC L){
  /*   Res : Renvoie 1 si L est une ListeSC triée, 0 sinon */
  while(L->succ != NULL){
    if(L->info > (L->succ)->info)
      return 0;
    L=L->succ;
  }
  return 1;
}


/* *************************  CONCATENATION DE 2 LISTES ********************************* */
ListeSC concatLSC(ListeSC L1,ListeSC L2){
  /*   Res : Renvoie la ListeSC obtenue par concaténation des ListeSC L1 et L2 */
  /*         Opère en modifiant le chainage de la listeSC L1 */
  /*   Version itérative */
  (dernierLSC(L1))->succ = L2;
  return L1;
}

ListeSC concatLSCR(ListeSC L1,ListeSC L2){
  /*   Res : Renvoie la ListeSC obtenue par concaténation des ListeSC L1 et L2 */
  /*         Opère en modifiant le chainage de la listeSC L1 */
  /*   Version récursive */
  if(L1 == NULL)
    return L2;
  else
    return creerLSC(L1->info, concatLSCR(L1->succ, L2));
}

ListeSC concatLSCCopie(ListeSC L1,ListeSC L2){
  /*   Res : Renvoie la ListeSC obtenue par concaténation des ListeSC L1 et L2 */
  /*         Opère en recopiant les éléments les listeSC L1 et L2 */
  /*   complexité : ø(length(L1)+length(L2)) */
  ListeSC L = NULL;
  while(L1 != NULL){
    insererFinLSC(&L, L1->info);
    L1 = L1->succ;
  }
  while(L2 != NULL){
    insererFinLSC(&L, L2->info);
    L2 = L2->succ;
  }
  return L;
}


/* **************************** OTERREPETITION ******************************************** */
void oterRepetitionLSCR(ListeSC L){
  /*    Res : Supprime de la ListeSC L tous les éléments consécutifs égaux */
  /*          Opère en modifiant le chainage de la ListeSC L */
  /*    version récursive */
  if((L != NULL)&&(L->succ != NULL)){
    if(L->info == (L->succ)->info){
      L->succ = (L->succ)->succ;
      oterRepetitionLSCR(L);
    }
    else
      oterRepetitionLSCR(L->succ);
  }
 }

void oterRepetitionLSC(ListeSC L){
  while((L != NULL) && (L->succ != NULL)){
    while((L->succ != NULL) && (L->info == (L->succ)->info))
      L->succ = (L->succ)->succ;
    L = L->succ;
  }
}


/*****************************************************************************/
/*                                                                           */
/*                              main                                         */
/*                                                                           */
/*****************************************************************************/
int main(int argc, char *argv[]){
  ListeSC l1,l2,l3; int x;
  if (argc !=2){
  	printf("Donnez comme argument 1 2 3 ou 4 \n");}
  else {

    switch (atoi(argv[1]))
    {
        case 1 :  /* Test des opérations de base sur les listes */

        l1=lireLSC();

        /* insertion d'un élément de valeur 11 en dernière position de la liste l1 */
        /* en utilisant insererFinLSC */
        /* Complétez */
	insererFinLSC(&l1, 11);
        printf("Insertion de 11 en dernière position");afficherLSC(l1);

        /* insertion d'un élément de valeur 22 en 2ème position de la liste l1 */
        /* en utilisant insererApresLSC */
        /* Complétez */
	insererApresLSC(&l1, &(l1->info), 22);
        printf("Insertion de 22 en 2ème position");afficherLSC(l1);

        /* insertion d'un élément de valeur 33 en 2ème position de la liste l1 */
        /* sans utiliser insererApresLSC */
        /* Complétez */
	l1 = creerLSC(l1->info, creerLSC(33, l1->succ));
        printf("Insertion de 33 en 2ème position");afficherLSC(l1);

        /* Suppression du 2ème élément de la liste sans utiliser supprimerLSC*/
        /* Complétez */
	l1->succ=(l1->succ)->succ;
        printf("Suppression du 2ème élément "); afficherLSC(l1);

        /* Suppression du 2ème élément de la liste en utilisant supprimerLSC*/
        /* Complétez */
	supprimerLSC(&l1, l1->succ);
        printf("Suppression du 2ème élément "); afficherLSC(l1);

        /* Inversion des valeurs des 2 premiers éléments */
        /* Complétez */
	x=l1->info;l1->info=(l1->succ)->info;(l1->succ)->info=x;
        printf("Inversion des valeurs des 2 premiers éléments" ); afficherLSC(l1);

        /* Inversion des 2 premiers éléments */
        /* Complétez */
	l2=l1;l1=l1->succ;l2->succ=l1->succ;l1->succ=l2;
        printf("Inversion des 2 premiers éléments"); afficherLSC(l1);
        break;



        case 2 : /* Test des fonctions  estTrieeLSC et dernierLSC */
        l1=lireLSC();

        if (estTrieeLSC(l1))  printf("Cette liste est triée\n");
        else printf("Cette liste n'est pas triée\n");
        if (l1 != NULL){
          printf("La valeur de son dernier élément est %d\n",dernierLSC(l1)->info);}
        break;


        case 3 :  /* Test des fonctions  de concaténation de listes */
        l1=lireLSC();
        l2=lireLSC();
        l3=concatLSCCopie(l1,l2);
        printf("Concaténation des 2 listes :\n"); afficherLSC(l3);
        if ((l1 != NULL) && (l2 != NULL) &&(l3 != NULL))
            printf("Adresse dernière cellule de l1 :%11p, de l2 : %11p, de l3 :  %11p\n\n",
	       (void *) dernierLSC(l1), (void *) dernierLSC(l2), (void *) dernierLSC(l3));
	// Meme adresse pour les 3 dernières cellules des listes avec les 2 premières fonctions.
	// Adresses différentes avec la copie.
         break;

    case 4 : /* Test des fonctions oterRepetitionLSC */
      l1=lireLSC();
      oterRepetitionLSCR(l1);
      printf("Liste sans répétition :\n");
      afficherLSC(l1);


      break;
    }
  }
  return 0;
}
