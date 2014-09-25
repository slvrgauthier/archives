/**
* \file test_pile.c
* \brief Test des differentes fonctions dans pile.c
* \author Geoffrey Lecerf
* \version 1.1
* \date 11-15-2012
*
*
* Fichier qui teste les differentes structures et fonctions deffinies
dans les fichiers pile.c et pile.h
*/

#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

/**
* \fn int main(int argc, char** argv)
* \brief Programme test 
* \param argc Nombre d'elements passes en parametre du fichier binaire executable
* \param argv Tableau des elements passes en parametre du fichier binaire executable
* \return EXIT_SUCCESS - Arret normal du programme
*
*
* Programme qui teste les differentes fonctions relatives aux piles
*/
int main (int argc, char** argv){
	/*
	*PARTIE TEST DE LA FONCTION
	*/

	// Creation d'une pile "pile"
	printf("\n***Creation d'une pile \"pile\"***\n\n");
	Pile *pile=creerPile();
	// Creation des elements a empiler dans pile
	int i=10;
	char c='c';
	int d=1223419;

	// 1er appel de la fonction empiler(Pile*,void*) sur pile
	printf("+Empilement de l'element \"int a=1\"\n");
	empiler(pile,i);
	//// Affichage de la taille (fonction taille(Pile*)) et du premier element (fonction premierElemPile(Pile*)) de la pile
	printf("\tTaille de la pile : %d\n\tPremier elem : %d \n\n",taille(pile),premierElemPile(pile));

	// 2e appel de la fonction empiler(Pile*,void*) sur pile
	printf("+Empilement de l'element \"char c='c'\"\n");
	empiler(pile,c);	
	//// Affichage de la taille (fonction taille(Pile*)) et du premier element (fonction premierElemPile(Pile*)) de la pile
	printf("\tTaille de la pile : %d\n\tPremier elem : %c \n\n",taille(pile),premierElemPile(pile));
	
	// 3e appel de la fonction empiler(Pile*,void*) sur pile
	printf("+Empilement de l'element \"char d='1223419'\"\n");
	empiler(pile,d);	
	//// Affichage de la taille (fonction taille(Pile*)) et du premier element (fonction premierElemPile(Pile*)) de la pile
	printf("\tTaille de la pile : %d\n\tPremier elem : %d \n\n",taille(pile),premierElemPile(pile));


	// 1er appel de la fonction depiler(Pile*) sur pile
	printf("-Depilement de la pile \"pile\"\n");
	depiler(pile);
	//// Affichage de la taille (fonction taille(Pile*)) et du premier element (fonction premierElemPile(Pile*)) de la pile
	printf("\tTaille de la pile : %d\n\tPremier elem : %c \n\n",taille(pile),premierElemPile(pile));

	// 2e appel de la fonction depiler(Pile*) sur pile
	printf("-Depilement de la pile \"pile\"\n");
	depiler(pile);
	//// Affichage de la taille (fonction taille(Pile*)) et du premier element (fonction premierElemPile(Pile*)) de la pile
	printf("\tTaille de la pile : %d\n\tPremier elem : %d \n\n",taille(pile),premierElemPile(pile));
	

	//Arret du programme
	return EXIT_SUCCESS;
}
