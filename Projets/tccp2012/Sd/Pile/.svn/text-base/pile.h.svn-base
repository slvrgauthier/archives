/**
* \file pile.h
* \brief Fichier d'en-tete
* \author Geoffrey Lecerf
* \version 1.1
* \date 11-15-2012
*
*
* Fichier definissant la structure de donnees Pile (LIFO (Last In First Out))
se basant sur une liste simplement chainee (presentee sur la verticale)
*/

#ifndef PILE_H
#define PILE_H
#include <stdio.h>
#include <stdlib.h>

/**
* \struct ElementPile pile.h
* \brief Structure ElementPile
*
*
* Definition structure Element representant les elements de la pile
*/
typedef struct ElementPile{
	void *donnee; /*!< Donnees de l'element de la pile. */
	struct ElementPile *elemSuivant; /*!< Pointeur sur l'element suivant de la pile */
}Element;

/**
* \struct Pile pile.h
* \brief Structure principale Pile
*
*
* Definition structure Pile representant la pile
*/
typedef struct Pile{
	Element *premierElem; /*!< Adresse du premier element de la liste (pile) */
	int taille; /*!< Nombre d'elements de la liste (pile) */
}Pile;

/**
* \fn Pile* creerPile()
* \brief Construction pile
* \return Renvoie la pile creee
*
*
* Fonction qui contruit une pile
*/
Pile* creerPile();

/**
* \fn void empiler(Pile *p, void *e)
* \brief Empiler un element dans la pile 
* \param p Pile dans laquelle on empilera l'element e
* \param e Element a empiler dans la pile p
*
*
* Fonction qui empile un element en haut de la pile
*/
void empiler(Pile *p, void *e);

/**
* \fn void depiler(Pile *p) 
* \brief Depiler la pile
* \param p Pile dont on depilera le dernier element
*
*
* Fonction qui depile (qui supprime) le dernier element entre de la pile 
*/
void depiler(Pile *p);

/**
* \fn int taille(Pile* p)
* \brief Renvoie la taille de la pile
* \param p Pile dont on va retourner la taille
* \return Taille de la pile (int)
*
*
* Fonction qui retourne la taille de la pile p entree en parametre
*/
int taille(Pile *p);


/**
* \fn void* premierElemPile(Pile* p)
* \brief Renvoie dernier element entre
* \param p Pile dont on va retourner le dernier element entre
* \return Dernier element de la pile
*
*
* Fonction qui retourne le dernier element empile dans p
*/
void* premierElemPile(Pile *p);

#endif /*PILE_H*/
