#include <stdlib.h>
#include <stdio.h>
#include "vecteur.h"

//Allocation dynamique et initialisation
vecteur vecteur_creer(){
  vecteur temp = malloc(sizeof(struct Vecteur));
  temp->taille = 0;
  temp->tableau = NULL;
  return temp;
}

//Libération de la mémoire du vecteur et de ses éléments
int vecteur_detruire(vecteur v){
  if(v->tableau!=NULL){
    free(v->tableau);
  }
  free(v);
  return 0;
}

//Crée et retourne un vecteur identique à celui passé en paramètre 
vecteur vecteur_clone(const vecteur v){
  vecteur temp = vecteur_creer();
  if(vecteur_taille(v)==0)return temp;
  else{
    temp->taille = vecteur_taille(v);
    temp->tableau = malloc(vecteur_taille(v) * sizeof(void*));
    for(unsigned int i = 0; i<vecteur_taille(v); i++)
      temp->tableau[i] = vecteur_lire(v,i);
    return temp;
  }
}

//Retourne une chaine de caractère indiquant la taille du vecteur
char* vecteur_chaine(const vecteur v){
  char* chaine = malloc(40*sizeof(char));
  sprintf(chaine,"Vecteur de taille %d.",vecteur_taille(v));
  return chaine;
}

//Ajoute l'élément x à la position k dans le vecteur v
unsigned int vecteur_ajout(vecteur v, void* x, const unsigned int k){  
  void* T[vecteur_taille(v)];
  int i;
  if(k>vecteur_taille(v))return vecteur_taille(v);
  else{
   for(i=0;i<vecteur_taille(v);i++)T[i]=v->tableau[i];
   free(v->tableau);
   v->tableau = malloc((vecteur_taille(v)+1)*sizeof(void*));
   v->taille = vecteur_taille(v)+1;
   v->tableau[k]=x;
   for(i=0;i<k;i++)v->tableau[i]=T[i];
   for(i=k+1;i<vecteur_taille(v);i++)v->tableau[i]=T[i-1];
   return vecteur_taille(v);  
  }
}

//Ajoute l'élément x au début du vecteur v
unsigned int vecteur_ajout_debut(vecteur v, void* x){
  return vecteur_ajout(v,x,0);
}

//Ajoute l'élément x à la fin du vecteur v
unsigned int vecteur_ajout_fin(vecteur v, void* x){  
  return vecteur_ajout(v,x,vecteur_taille(v));
}

//Supprime et retourne le k-ième élément du vecteur v
void* vecteur_retirer(vecteur v, const unsigned int k){ 
  void* T[vecteur_taille(v)];
  int i;
  if(k>=vecteur_taille(v))return NULL;
  else{
   for(i=0;i<vecteur_taille(v);i++)T[i]=v->tableau[i];
   free(v->tableau);
   v->tableau = malloc((vecteur_taille(v)-1)*sizeof(void*));
   v->taille = vecteur_taille(v)-1;
   for(i=0;i<k;i++)v->tableau[i]=T[i];
   for(i=k;i<vecteur_taille(v);i++)v->tableau[i]=T[i+1];
   return T[k];  
  }
}

//Supprime et retourne le premier élément du vecteur v
void* vecteur_retirer_debut(vecteur v){
  return vecteur_retirer(v,0);
}

//Supprime et retourne le dernier élément du vecteur v
void* vecteur_retirer_fin(vecteur v){  
  return vecteur_retirer(v,vecteur_taille(v)-1);
}

//Retourne l'élément à la position k du vecteur v
void* vecteur_lire(const vecteur v, const unsigned int k){
  if(k>=vecteur_taille(v))return NULL;
  else return v->tableau[k];
}

//Retourne la taille du vecteur v
unsigned int vecteur_taille(const vecteur v){
  return v->taille;
}



