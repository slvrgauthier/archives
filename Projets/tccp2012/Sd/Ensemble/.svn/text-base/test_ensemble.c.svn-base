/**
 * \file : test_ensemble.h
 * \brief : Test sur les ensembles
 * \author CARBONNEL Jessie, LY Julie
 * \version 0.4
 * \date 10 octobre 2012
*/


#include <stdio.h>
#include <stdlib.h>

#include "ensemble.h"
#include "typesBase/typeBase.h"


int main( int argc, char* argv[] )
{
	// Création d'éléments ---------------------------------------------------------------------------------
	Entier a = Entier_Creer(4) ;
	Entier a2 = Entier_Creer(17) ;

	Flottant b = Flottant_Creer(5.2) ;
	Flottant b2 = Flottant_Creer(22.6) ;

	Car c = Car_Creer('x') ;
	Car c2 = Car_Creer('y') ;

	String d = String_Creer("Hello") ;
	String d2 = String_Creer("World") ;



	// Création de deux ensembles vide ----------------------------------------------------------------------
	Ensemble e = ensemble_creer() ;
	Ensemble e2 = ensemble_creer() ;



	// Ajouter d'éléments dans les ensembles ----------------------------------------------------------------
	// -> Ensemble n°1 : { Hello, x, 5.2, 17, 4 }
		element_ajouter(e, a) ;
		element_ajouter(e, a2) ;
		element_ajouter(e, b) ;
		element_ajouter(e, c) ;
		element_ajouter(e, d) ;

	// -> Ensemble n°1 : { World, Hello, y, 22.6, 5.2, 4 }
		element_ajouter(e2, a) ;
		element_ajouter(e2, b) ;
		element_ajouter(e2, b2) ;
		element_ajouter(e2, c2) ;
		element_ajouter(e2, d) ;
		element_ajouter(e2, d2) ;
		element_ajouter(e2, d2) ; // <- On tente d'introduire une deuxième occurence de d2



	// Affichage des deux ensembles --------------------------------------------------------------------------
	printf("\n# SOIT LES ENSEMBLES SUIVANT :\n") ;
	printf("Ensemble E1 : ") ;      ensemble_afficher(e) ;
	printf("\n") ;
	printf("Ensemble E2 : ") ;      ensemble_afficher(e2) ; // -> d2 n'apparait qu'une seule fois !



	// Test de la présence d'un élément dans un ensemble -> 1 s'il est présent, 0 sinon.  --------------------
	printf("\n\n# ELEMENT PRESENT ?\n") ;
	if(element_present(e, c) == 1) // -> Ce qui est VRAI !
	{
		printf("L'élément [c = 'x'] est présent dans E1.") ; // -> Doit s'afficher
	}
	else
	{
		printf("L'élément [c = 'x'] n'existe pas dans E1.") ;
	}

	printf("\n") ;

	if(element_present(e, b2) == 1) // -> Ce qui est FAUX !
	{
		printf("L'élément [b2 = 22.6] est présent dans E1.") ;
	}
	else
	{
		printf("L'élément [b2 = 22.6] n'existe pas dans E1.") ; // -> Doit s'afficher
	}



	// Clonage d'un ensemble ----------------------------------------------------------------------------------
	Ensemble e3 = ensemble_cloner(e) ;

	printf("\n \n# CLONAGE D'UN ENSEMBLE :\n") ;

	printf("Rappel E1 : ") ;     ensemble_afficher(e) ;
	printf("\n") ;
	printf("Son clone E3 : ") ;     ensemble_afficher(e3) ;




	// Ajout d'un élément dans un ensemble ----------------------------------------------------------------
	printf("\n \n# AJOUT D'ELEMENTS (ajout élement '22.6' et ensemble 'E2') : \n") ;
	
	Ensemble e4 = ensemble_cloner(e) ;
	printf("E4 (clone de E1) avant : ") ; ensemble_afficher(e4) ; 
	printf("\n") ;
	element_ajouter(e4,e2) ;
	element_ajouter(e4,b2) ;
	printf("E4 après : ") ; ensemble_afficher(e4) ;




	// Suppression d'un élement dans un ensemble ----------------------------------------------------------------
	printf("\n \n# SUPPRESSION D'ELEMENTS : \n") ;
	printf("E2 avant : ") ;     ensemble_afficher(e2) ;
	printf("\n") ;
	element_supprimer(e2, a) ;
	element_supprimer(e2, c2) ;
	element_supprimer(e2, b) ;
	printf("E2 après : ") ;     ensemble_afficher(e2) ;




	// Déterminer le nombre d'éléments des ensembles ----------------------------------------------------------
	printf("\n \n# NOMBRE D'ELEMENTS DES ENSEMBLES :\n") ;
	printf("Ensemble E1 : %d élements. \n", nombre_elements(e)) ;
	printf("Ensemble E2 : %d élements. \n", nombre_elements(e2)) ;
	printf("Ensemble E3 : %d élements. \n", nombre_elements(e3)) ;




	// Les ensembles ont-ils même cardinalité ? -> 1 si c'est vrai, 0 sinon. ----------------------------------
	printf("\n# MEME CARDINALITE ?\n") ;
	if(ensemble_meme_cardinalite(e, e3) == 1) // -> Ce qui est VRAI !
	{
		printf("Ensembles E1 et E3 : Les ensembles ont même cardinalité.") ; // -> Doit s'afficher
	}
	else
	{
		printf("Ensembles E1 et E3 : Les ensembles n'ont pas même cardinalité.") ;
	}

	printf("\n") ;

	if(ensemble_meme_cardinalite(e, e2) == 1) // -> Ce qui est FAUX !
	{
		printf("Ensembles E1 et E2 : Les ensembles ont même cardinalité.") ;
	}
	else
	{
		printf("Ensembles E1 et E2 : Les ensembles n'ont pas même cardinalité.") ; // -> Doit s'afficher
	}




	// Les ensembles sont-ils égaux ? -> 1 s'ils le sont, 0 sinon. --------------------------------------------
	printf("\n \n# EGALITE ? (Au niveau des éléments)\n") ;
	if(ensembles_egaux(e, e3) == 1) // -> Ce qui est VRAI !
	{
		printf("Ensembles E1 et E3 : Les ensembles possèdent les mêmes éléments.") ; // -> Doit s'afficher
	}
	else
	{
		printf("Ensembles E1 et E3 : Les ensembles ne possèdent pas les mêmes éléments.") ;
	}

	printf("\n") ;

	if(ensembles_egaux(e, e2) == 1) // -> Ce qui est FAUX !
	{
		printf("Ensembles E1 et E2 : Les ensembles possèdent les mêmes éléments.") ;
	}
	else
	{
		printf("Ensembles E1 et E2 : Les ensembles ne possèdent pas les mêmes éléments.") ; // -> Doit s'afficher
	}




/************ LES OPERATIONS ENSEMBLISTES *************************************************************************/
	printf("\n \n \n \n# OPERATIONS ENSEMBLISTES : \n") ;


	// UNION de deux ensembles --------------------------------------------------------------------------------
	printf("Union entre E1 et E3 : ") ;
	ensemble_afficher( ensemble_union(e, e3)) ; // -> Les occurences n'ont pas été prises en compte !
	printf("\n") ;
	printf("Union entre E1 et E3 : ") ;
	ensemble_afficher( ensemble_union(e, e2)) ;

	printf("\n \n") ;


	// INTERSECTION de deux ensembles -------------------------------------------------------------------------
	printf("Intersection entre E1 et E3 : ") ;
	ensemble_afficher( ensemble_intersection(e, e3)) ;
	printf("\n") ;
	printf("Intersection entre E1 et E2 : ") ;
	ensemble_afficher( ensemble_intersection(e, e2)) ;

	printf("\n \n") ;


	// DIFFERENCE de deux ensembles ---------------------------------------------------------------------------
	printf("Difference entre E1 et E3 : ") ;
	ensemble_afficher( ensemble_difference(e, e3)) ;
	printf("\n") ;
	printf("Difference entre E1 et E2 : ") ;
	ensemble_afficher( ensemble_difference(e, e2)) ;

	printf("\n \n") ;


	// DIFFERENCE SYMETRIQUE de deux ensembles -----------------------------------------------------------------
	printf("Difference Symétrique entre E1 et E3 : ") ;
	ensemble_afficher( ensemble_difference_symetrique(e, e3)) ;
	printf("\n") ;
	printf("Difference Symétrique entre E1 et E2 : ") ;
	ensemble_afficher( ensemble_difference_symetrique(e, e2)) ;


/******************************************************************************************************************/
	printf("\n\n") ;

	// Destruction des ensembles ------------------------------------------------------------------------------
	ensemble_detruire(e) ;
	ensemble_detruire(e2) ;
	ensemble_detruire(e3) ;
	ensemble_detruire(e4) ;



	return 0 ;
}











