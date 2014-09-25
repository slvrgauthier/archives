/**
 * \file : ensemble.c
 * \brief : Définition des fonctions sur les Ensembles
 * \author CARBONNEL Jessie, LY Julie
 * \version 0.4
 * \date 10 octobre 2012
*/


#include <stdio.h>
#include <stdlib.h>
#include "ensemble.h"
#include "typesBase/typeBase.h"



/* -------------------------- Création d'un ensemble vide ------------------------- */
Ensemble ensemble_creer()
{
  	Ensemble e = malloc(sizeof(Ensemble));
  	e->type = 5;
	e->objet=(ensemble)malloc(sizeof(ensemble));

	((ensemble)e->objet)->premier = NULL;

  return e ;
}


/* ----------------------------- Détruire un ensemble ----------------------------- */
void ensemble_detruire(Ensemble e)
{
	while(((ensemble)e->objet)->premier != NULL)
	{
            Element aSupprimer = ((ensemble)e->objet)->premier;
            if((aSupprimer->elt)->type == 5)
            {
                ensemble_detruire(aSupprimer->elt);
            }
            else
            {
                Detruire(aSupprimer->elt);
            }
            ((ensemble)e->objet)->premier = (((ensemble)e->objet)->premier)->suivant;
            free(aSupprimer);
	}
	free(e->objet);
	free(e);
}


/* ------------------------------ Cloner un ensemble ------------------------------ */
Ensemble ensemble_cloner(Ensemble e)
{
	Ensemble e2 = ensemble_creer();
	Ensemble e3 = ensemble_creer();

	Element aux = ((ensemble)e->objet)->premier;
	while(aux != NULL)
	{
		element_ajouter(e2,aux->elt);
		aux = aux->suivant;
	}

	// Réinverser l'ensemble pour l'avoir dans le même ordre que 'e'
	aux = ((ensemble)e2->objet)->premier;
	while(aux != NULL)
	{
		element_ajouter(e3,aux->elt);
		aux = aux->suivant;
	}

	ensemble_detruire(e2);

	return e3;
}


/* ----------------- Afficher tous les éléments de l'ensemble ------------------- */
void ensemble_afficher(Ensemble e)
{
	Element aux = ((ensemble)e->objet)->premier;

	printf("{ ") ;

	while(aux != NULL)
	{
		if((aux->elt)->type == 5)
		{

		ensemble_afficher(aux->elt);
		}
		else
		{
		Affiche(aux->elt);
		}

		aux = aux->suivant;
		if(aux != NULL) { printf(", "); }
	}
	printf(" }");

}


/* ------------------ L'élément est-il présent dans l'ensemble ? ------------------ */
// ================ > Renvoie 1 si l'élément ets présent, 0 sinon < ================= //
int element_present(Ensemble e, Type t)
{
	int booleen = 0;
	Element aux = ((ensemble)e->objet)->premier;

	while(aux != NULL)
	{
	    if(((aux->elt)->type == 5) && t->type==5)
	    {
	        booleen = ensembles_egaux(t,aux->elt);
	    }
	    else if(((aux->elt)->type == 5) && t->type!=5)
	    {
	     //   booleen reste à 0
	    }
	     else if(((aux->elt)->type != 5) && t->type==5)
	    {
	       // booleen reste à 0
	    }
	    else
	    {
	        if(Egal(t, aux->elt) == 0)
		{
			booleen = 1;
		}
	    }
		aux = aux->suivant;
	}

	return booleen;
}


/* ---------------------- Ajouter un élément dans l'ensemble --------------------- */
void element_ajouter(Ensemble e, Type t)
{
    	if(element_present(e,t) == 0)
	{
		Element element = malloc(sizeof(Element));
		if((t)->type == 5)
		{
			element->elt = ensemble_cloner(t);
		}
		else
		{
			element->elt = Clone(t);
		}
	
		if(((ensemble)e->objet)->premier == NULL)
		{
			element->suivant = NULL;
			((ensemble)e->objet)->premier = element;
		}
		else
		{
			element->suivant = ((ensemble)e->objet)->premier;
			((ensemble)e->objet)->premier = element;
		}
    	}
}


/* --------------------- Supprimer un élément dans un ensemble -------------------- */
void element_supprimer(Ensemble e, Type t)	
{
	if(element_present(e,t))
	{
		Ensemble e2 = ensemble_creer();
	
		while(((ensemble)e->objet)->premier != NULL)
		{
			Element aux = ((ensemble)e->objet)->premier;
			
			if( (t->type == 5) && ((aux->elt)->type == 5))
			{
				if(!ensembles_egaux(t,aux->elt))
				{
					element_ajouter(e2,aux->elt);
				}
			}
			else if( (t->type == 5) && ((aux->elt)->type != 5))
			{
				element_ajouter(e2,aux->elt);
			}
			else if( (t->type != 5) && ((aux->elt)->type == 5))
			{
				element_ajouter(e2,aux->elt);
			}
			else if(Egal(t, aux->elt) == 1)
			{
				element_ajouter(e2,aux->elt);
			}
	
			Detruire(aux->elt);
			((ensemble)e->objet)->premier = (((ensemble)e->objet)->premier)->suivant;
			free(aux);
		}
	
		((ensemble)e->objet)->premier = ((ensemble)e2->objet)->premier;
		free(e2->objet);
		free(e2);
	}
}


/* ---------------- Déterminer le nombre d'éléments d'un ensemble ----------------- */
int nombre_elements(Ensemble e)
{
	int compt = 0;
	Element aux = ((ensemble)e->objet)->premier;

	while(aux != NULL)
	{
		compt++;
		aux = aux->suivant;
	}

	return compt;
}


/* --------------- Les deux ensembles ont-ils la même cardinalité ? --------------- */
// ======== > Renvoie 1 si les deux ensembles ont même cardinalité, 0 sinon ========= //
int ensemble_meme_cardinalite(Ensemble e1, Ensemble e2)
{
	int booleen = 0 ;
	if(nombre_elements(e1) == nombre_elements(e2))
	{
		booleen = 1 ;
	}

	return booleen ;
}


/* --------------------- Les deux ensembles sont-ils égaux ? ---------------------- */
int ensembles_egaux(Ensemble e1, Ensemble e2)
{
	int booleen = 1;
	if(ensemble_meme_cardinalite(e1,e2) == 0)
	{
		booleen = 0;
	}
	else
	{
		Element aux = ((ensemble)e1->objet)->premier;
		while(aux != NULL)
		{
			if(element_present(e2,aux->elt) == 0)
			{
				booleen = 0;
			}
			aux = aux->suivant;
		}
	}

	return booleen;
}


/* ---------------------------- Union de deux ensembles --------------------------- */
Ensemble ensemble_union(Ensemble e1, Ensemble e2)
{
	Ensemble e3 = ensemble_cloner(e1);
	Element aux = ((ensemble)e2->objet)->premier;
	while(aux != NULL)
	{
		element_ajouter(e3,aux->elt);
		aux = aux->suivant;
	}
	return e3;
}


/* ------------------------ Intersection de deux ensembles ------------------------ */
Ensemble ensemble_intersection(Ensemble e1, Ensemble e2)
{
	Ensemble e3 = ensemble_creer();


	Element aux = ((ensemble)e1->objet)->premier;
	while(aux != NULL)
	{
		if(element_present(e2,aux->elt))
		{
			element_ajouter(e3,aux->elt);
		}
		aux = aux->suivant;
	}

	aux = ((ensemble)e2->objet)->premier;
	while(aux != NULL)
	{
		if(element_present(e1,aux->elt))
		{
			element_ajouter(e3,aux->elt);
		}
		aux = aux->suivant;
	}

	return e3;
}


/* ----------------------- Difference entre deux ensembles ------------------------ */
Ensemble ensemble_difference(Ensemble e1, Ensemble e2)
{
	Ensemble e3 = ensemble_creer();


	Element aux = ((ensemble)e1->objet)->premier;
	while(aux != NULL)
	{
		if(element_present(e2,aux->elt) == 0)
		{
			element_ajouter(e3,aux->elt);
		}
		aux = aux->suivant;
	}

	return e3;
}


/* ------------------ Difference symétrique entre deux ensembles ------------------ */
Ensemble ensemble_difference_symetrique(Ensemble e1, Ensemble e2)
{
	Ensemble e3 = ensemble_difference(ensemble_union(e1,e2), ensemble_intersection(e1,e2)) ;

	return e3;
}

