/**
* \file pile.c
* \brief Fichier de description des fonctions de pile.h
* \author Geoffrey Lecerf
* \version 1.1
* \date 11-15-2012
*
*
* Fichier definissant les fonctions utiles aux operations sur les piles
*/

#include "pile.h"

/**
* \fn Pile* creerPile()
* \brief Creer une pile
* \return La pile creee
*
*
* Fonction qui cree une pile
*/
Pile* creerPile (){
	Pile *p=malloc(sizeof(Pile));
	//init du premier element de la pile a NULL
	p->premierElem=NULL;
	//init de la taille de la pile a 0
	p->taille=0;

	return p;
}

/**
* \fn void empiler(Pile* p, void* e)
* \brief Empiler un element e
* \param p Pile sur laquelle on va empiler un element e
* \param e Element qu'on va empiler dans la pile p
*
*
* Fonction qui empile un element e quelconque dans une pile p
*/
void empiler (Pile *p, void *e){
	Element *elemt = malloc(sizeof(Element));
	/*
	** Element
	*/
	//la donnee de l'element prend comme valeur e
	elemt->donnee=e;
	//fait pointer l'element suivant de vers le premier element actuel de la pile
	elemt->elemSuivant=p->premierElem;

	/*
	** Pile
	*/
	//le premier element de la pile prend maintenant la valeur de l'element cree precedemment
	p->premierElem=elemt;
	//on agrandit la taille de la pile
	p->taille++;
}

/**
* \fn void depiler (Pile* p)
* \brief Depiler la pile
* \param p Pile qu'on va depiler
*
*
* Fonction qui permet d'enlever l'element en haut de la pile (le dernier
element entre
*/
void depiler (Pile *p){
	Element *elemSuiv = malloc(sizeof(Element));

	elemSuiv=p->premierElem;
	p->premierElem=p->premierElem->elemSuivant;
	free(elemSuiv);
	p->taille--;
}

/**
* \fn int taille(Pile* p)
* \brief Renvoie la taille de la pile
* \param p Pile dont on va retourner la taille
* \return Taille de la pile (int)
*
*
* Fonction qui retourne la taille de la pile p entree en parametre
*/
int taille(Pile *p){
	return p->taille;
}


/**
* \fn void* premierElemPile(Pile* p)
* \brief Renvoie dernier element entre
* \param p Pile dont on va retourner le dernier element entre
* \return Dernier element de la pile
*
*
* Fonction qui retourne le dernier element empile dans p
*/
void* premierElemPile(Pile *p){
	return p->premierElem->donnee;
}
