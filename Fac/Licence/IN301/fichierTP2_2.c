#include <time.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "progListeSC.h"


ListeSC dernierLSC(ListeSC L){
  assert(L!=NULL);
  while ((L->succ) != NULL){
    L=(L->succ);}
  return L;
}

int estTrieeLSC(ListeSC L){
  /*   Res : Renvoie 1 si L est une ListeSC triée, 0 sinon */
  /*   version récursive  */

  if (estVideLSC(L) || estVideLSC(L->succ))
    return 1;
  else
    if (L->info < (L->succ)->info)
      return estTrieeLSC(L->succ);
    else return 0;
}


/* ****************** estListeIntervalle *****************************/
int estListeIntervalle(ListeSC L){
  /*   Res : renvoie 1 si L est une Liste intervalle, renvoie 0 sinon */
  if(L == NULL)
    return 1;
  while(L->succ != NULL){
    if(L->info != (L->succ)->info - 1)
      return 0;
    L = L->succ;
  }
  return 1;
}

/* ******************** consListeIntervalle *************************/
ListeSC consListeIntervalle1(int l, int p){
  /*     Donnée : l>0 */
  /*     Res : renvoie une liste intervalle de longueur l et dont le premier élément a pour valeur p */
  /*     Complexité : 0(n²)  */
  int i; ListeSC L;
  assert(l>0);

  L=NULL;
  for(i=0;i<l;i++){
    insererFinLSC(&L,p+i);}
  return L;
}

ListeSC consListeIntervalle2(int l, int p){
  /*     Donnée : l>0 */
  /*     Res : renvoie une liste intervalle de longueur l et dont le premier élément a pour valeur p */
  /*     Complexité : 0(n)  */
  int i; ListeSC L;
  assert(l>0);

  L=NULL;
  for(i=l-1;i>=0;i--)
    insererDebutLSC(&L, p+i);
  return L;
}

/* ********************* transfListeIntervalle **********************/
void transfListeIntervalle(ListeSC L){
  /* Donnée : L est une liste triée non vide  */
  /* Res : modifie L en y insérant des éléments de sorte qu'elle soit une Liste Intervalle */
  assert((L!=NULL));
  assert(estTrieeLSC(L));
  
  ListeSC P = L;
  while(P->succ != NULL){
    if((P->succ)->info != P->info + 1)
      P->succ = creerLSC(P->info + 1, P->succ);
    P = P->succ;
  }
}




/*****************************************************************************/
/*                                                                           */
/*                              main                                         */
/*                                                                           */
/*****************************************************************************/
int main(int argc, char *argv[]){
  ListeSC l1,l2,l3;

  if (argc !=2){
  	printf("Donnez comme argument 1 2 3 ou 4 \n");}
  else {
    switch (atoi(argv[1])){
    case 1 :
      l1=lireLSC();
      if (estListeIntervalle(l1))
	printf("Cette liste est une liste intervalle \n");
      else
	printf("Cette liste n'est pas une liste intervalle \n");
      break;

    case 2 :
      { int lg, prem;

      printf("Donnez 2 entiers strictement positifs (longueur et premier élément de la liste intervalle) : ");
      scanf("%d %d",&lg, &prem);
      l2=consListeIntervalle1(lg,prem);
      afficherLSC(l2);
      l3=consListeIntervalle2(lg,prem);
      afficherLSC(l3);
      break;}

    case 3 :
      { int lg, prem; clock_t t1,t2,t3;

      printf("Donnez 2 entiers strictement positifs (longueur et premier élément de la liste intervalle) : ");
      scanf("%d %d",&lg, &prem);
      t1=clock();
      l2=consListeIntervalle1(lg,prem);
      t2=clock();
      l2=consListeIntervalle2(lg,prem);
      t3=clock();
      printf(" Construction d'une Liste de taille %d \n  version linéaire %f sec\n  version quadratique %f sec\n",
	     lg,(t3-t2)*1e-6 ,(t2-t1)*1e-6 );
	break;
      }
       case 4 : /* Transformation d'une liste triée en liste Intervalle */

      printf("Entrez une Liste Triée : ");
      l1=lireLSC();
      transfListeIntervalle(l1);
      printf("Liste Intervalle construite ");
      afficherLSC(l1);
    }

}

  return 0;
}




