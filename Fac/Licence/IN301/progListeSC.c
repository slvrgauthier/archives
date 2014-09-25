/**************************** progListeSC.c **********************************/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include  "progListeSC.h"


int estVideLSC(ListeSC l)
{ return (l==NULL);}

ListeSC creerLSC(int val, ListeSC succ){
  ListeSC l = (ListeSC) malloc(sizeof(CelluleSC));
  l->info=val;
  l->succ=succ;
  return l;}

void insererDebutLSC(ListeSC *p, int val){
  *p=creerLSC(val,*p);
  return;}

void insererApresLSC(ListeSC l, ListeSC p, int val){
  assert(l!=NULL);   assert(p!=NULL);
  (p->succ)=creerLSC(val,(p->succ));
  return;}

void insererFinLSC(ListeSC *p, int val){
  if ((*p)==NULL)
    (*p)=creerLSC(val,NULL);
  else
    insererFinLSC(&((*p)->succ),val);
  return;
}

ListeSC predecesseurLSC(ListeSC L, ListeSC P){
  assert(L!=NULL);
  assert(P!=NULL);

  if (L->succ==P){return L;}
  else {return predecesseurLSC(L->succ,P);}
}

void supprimerLSC(ListeSC *L, ListeSC P){
  assert((*L)!=NULL);
  assert(P!=NULL);

  if ((*L)==P){*L=(*L)->succ;}
  else {
    predecesseurLSC(*L,P)->succ=P->succ;
  }
  free(P);
  return;}

void supprimerDebutLSC(ListeSC *L){
  ListeSC P;

   assert(L!=NULL);


  P=(*L);
  (*L)=(*L)->succ;
  free(P);
  return;}


void supprimerFinLSC(ListeSC *L){
  assert((*L)!=NULL);

  if ((*L)->succ==NULL){
    free(*L);
    (*L)=NULL;}
  else {
    ListeSC P=(*L),Q;
    while ((P->succ)->succ!=NULL){
      P=P->succ;}
    Q=P->succ;
    P->succ=NULL;
    free(Q);}
  return;}



void afficherLSC(ListeSC l){
  printf("ListeSC : ");
  while (! estVideLSC(l)){
	printf(" %d ",l->info);
	l=l->succ;}
  printf("\n");
  return;}

ListeSC lireLSC(){
  ListeSC l;
  int i;
  printf("Entrez les éléments d'une liste d'entiers (0 pour finir)\n");
  l=NULL;
  scanf("%d",&i);
  while (i!=0) {
    insererFinLSC(&l,i);
    scanf("%d",&i);
  }
  return l;
}

