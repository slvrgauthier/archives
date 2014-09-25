#include <stdlib.h>
#include <stdio.h>

#include "arbin.h"

/*----------------------GREFFERGAUCHE-----------------------------------------*/
void greffergauche(Arbin pere, Arbin filsg) {
  videra(&sag(pere));		/* vider l'ancien sag */
  pere->fg=filsg;		/* le remplacer */
}

/*----------------------GREFFERDROITE-----------------------------------------*/
void grefferdroite(Arbin pere, Arbin filsd){
  videra(&sad(pere));
  pere->fd=filsd;
}

/*----------------------CONSTRUIRE--------------------------------------------*/
Arbin construire(int rac, Arbin g, Arbin d){
  Arbin nouv = (Arbin) malloc(sizeof(Noeudbin)) ;
  nouv->val=rac;
  nouv->fg=g;
  nouv->fd=d;
  return(nouv) ;
}

/*----------------------COPIERA-----------------------------------------------*/
Arbin copiera(Arbin a){
  Arbin nouv;			/* nouvel arbin copie */
  if (videa(a)) return NULL;	/* arbin vide */
  nouv = (Arbin) malloc(sizeof(Noeudbin)) ;
  nouv->val=a->val;
  nouv->fg=copiera(sag(a));
  nouv->fd=copiera(sad(a));
  return(nouv) ;
} 

/*----------------------VIDERA------------------------------------------------*/
void videra(Arbin *pa){	
  Arbin *pg,*pd;			/* arbins de sauvegarde */
  if (videa(*pa)) return;		/* arbin vide */
  pg=&(sag(*pa));			/* possible car sag() est une macro */
  pd=&(sad(*pa));
  videra(pg);
  videra(pd);
  free(*pa);			/* on est sur une feuille */
  *pa=NULL;			/* mettre le pointeur a NULL  */
  return;
} 
/*----------------------AFFICHERAR-fonction privée (static) ------------------*/
static void afficherar(Arbin a,int indent){
  int i;
  for (i=0;i<indent;i++)
    printf("  ");		/* 2 espaces par profondeur d'indentation */
  if (videa(a))
    printf("\r");
  else {
    printf("%c\n",racine(a));
    afficherar(sag(a),indent+1);
    afficherar(sad(a),indent+1);
  }
}
/*----------------------AFFICHERA---------------------------------------------*/
void affichera(Arbin a){
  afficherar(a,0);
}
