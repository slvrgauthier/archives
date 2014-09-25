#ifndef ARBRE_H
#define ARBRE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct arbre arbre;

struct arbre
{
		void* contenu;
		arbre* fils;
		arbre* frere;
		int nbpointe; //nombre de pointeurs vers l'instance de la struct;
		
//		Pointeurs vers les fonctions :
		arbre* (*ajouterFrere)(arbre* this,void* cont);
		arbre* (*ajouterFils)(arbre* this,void* cont);
		arbre* (*getFrereNbx)(arbre* this,int nb);
		arbre* (*getFilsNbx)(arbre* this,int nb);
		int (*nbElementsArbre)(arbre* this);
		int (*estFeuille)(arbre* this);
		int (*detruireArbre)(arbre* this);
		arbre* (*cloneRacine)(arbre* this);
		void (*grefferArbre)(arbre* this,arbre* A);
		void (*grefferFrere)(arbre* this,arbre* A);
		char* (*chaine)(arbre* this);
};

arbre* creerArbre(void* cont);
arbre* _ajouterFrere(arbre* this,void* cont);
arbre* _ajouterFils(arbre* this,void* cont);
arbre* _getFrereNbx(arbre* this,int nb);
arbre* _getFilsNbx(arbre* this,int nb);
int _nbElementsArbre(arbre* this);
int _estFeuille(arbre* this);
int _detruireArbre(arbre* this);
arbre* _cloneRacine(arbre* this);
void _grefferArbre(arbre* this,arbre* A);
void _grefferFrere(arbre* this,arbre* A);
char* _chaine(arbre* this);
#endif
