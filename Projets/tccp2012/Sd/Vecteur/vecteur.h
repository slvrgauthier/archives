#ifndef _VECTEUR_H
#define _VECTEUR_H

//documenter avec doxygen, mettre au moins un @author

struct Vecteur{
  unsigned int taille;
  void** tableau;
};
typedef struct Vecteur* vecteur;

vecteur vecteur_creer();
int vecteur_detruire(vecteur v);
vecteur vecteur_clone(const vecteur v);
//int vecteur_egal(vecteur v, vecteur w);
//int vecteur_compare(vecteur v, vecteur w);
char* vecteur_chaine(const vecteur v);

//Ajoute l'élément x à la position k dans le vecteur v
unsigned int vecteur_ajout(vecteur v, void* x, const unsigned int k);

//Ajoute l'élément x au début du vecteur v
unsigned int vecteur_ajout_debut(vecteur v, void* x);

//Ajoute l'élément x à la fin du vecteur v
unsigned int vecteur_ajout_fin(vecteur v, void* x);

//Supprime et retourne le k-ième élément du vecteur v
void* vecteur_retirer(vecteur v, const unsigned int k);

//Supprime et retourne le premier élément du vecteur v
void* vecteur_retirer_debut(vecteur v);

//Supprime et retourne le dernier élément du vecteur v
void* vecteur_retirer_fin(vecteur v);

//Retourne l'élément à la position k du vecteur v
void* vecteur_lire(const vecteur v, const unsigned int k);

//Retourne la taille du vecteur v
unsigned int vecteur_taille(const vecteur v);


#endif
