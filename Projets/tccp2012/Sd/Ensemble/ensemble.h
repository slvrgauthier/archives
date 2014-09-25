/**
 * \file : ensemble.h
 * \brief : Déclaration des fonctions sur les Ensembles
 * \author CARBONNEL Jessie, LY Julie
 * \version 0.4
 * \date 10 octobre 2012
*/

#ifndef _ENSEMBLE_H
#define _ENSEMBLE_H

#include "typesBase/typeBase.h"


/**
 *@mainpage Projet SD : Ensemble
 *Cette bibliothèque s'attardera sur les ensembles (non ordonnés).

Vous retrouverez les fontions essentielles au développement d'un ensemble ainsi que les opérations ensemblistes (tel que l'union ou l'intersection) sur deux ensembles.

\b Remarque \b : Notre code reprend le travail de LAMEIRA Yannick et VERDIER Frédéric concernant les types de base.
La documentation de leur code source ne sera pas généré ici. Je vous invite donc à vous rediriger vers leur documentation pour de plus amples renseignements concernant ces types de base.
 
 *@author CARBONNEL Jessie, LY Julie
*/



/**
 * \struct Ensemble
 * \brief Struture de Type Ensemble
 * Cette struture permet la création du type 'Ensemble'. Ce type sera appelé par un int égal à 5.
 */
typedef struct Type* Ensemble ;

/**
 * \struct Element
 * \brief Struture d'un élement
 * Cette struture permet de créer un élement.
 */
typedef struct Element* Element ;
struct Element
{
	Type elt;
	Element suivant;
};

/**
 * \struct ensemble
 * \brief Struture d'un ensemble
 * Cette struture permet de créer un ensemble.
 */
typedef struct ensemble* ensemble;
struct ensemble
{
	Element premier;        // Pointeur vers le deuxième element de l'ensemble
};






/**
 * \fn Ensemble ensemble_creer()
 * \brief Création d'un ensemble vide.
 *
 * \return Renvoie un ensemble vide.
*/
Ensemble ensemble_creer() ;



/**
 * \fn void ensemble_detruire(Ensemble e)
 * \brief Detruire un ensemble.
 *
 * \param e L'ensemble à détruire.
 * \return Ne renvoie rien.
 *
 * Permet de détruire un ensemble correctement (sans fuite mémoire).
*/
void ensemble_detruire(Ensemble e) ;



/**
 * \fn Ensemble ensemble_cloner(Ensemble e)
 * \brief Cloner un ensemble.
 *
 * \param e L'ensemble à cloner.
 * \return Renvoie un ensemble.
 *
*/
Ensemble ensemble_cloner(Ensemble e) ;



/**
 * \fn void ensemble_afficher(Ensemble e)
 * \brief Afficher les éléments d'un ensemble.
 *
 * \param e L'ensemble dont on veut afficher tous les éléments.
 * \return Ne renvoie rien.
*/
void ensemble_afficher(Ensemble e) ;



/**
 * \fn int element_present(Ensemble e, Type t)
 * \brief Indique si un élément est présent dans un ensemble.
 *
 * \param e L'ensemble dans lequel on veut déterminer si un élément est présent ou non.
 * \param t Un type quelconque qui représente l'élément dont on déclare la présence ou non présence dans l'ensemble.
 * \return Renvoie 1 si l'élément est présent, 0 sinon.
*/
int element_present(Ensemble e, Type t) ;



/**
 * \fn void element_ajouter(Ensemble e, Type t)
 * \brief Ajouter un élément dans un ensemble.
 *
 * \param e L'ensemble dans lequel on veut ajouter un élément.
 * \param t Un type quelconque qui représente l'élément à ajouter dans l'ensemble.
 * \return Ne renvoie rien.
 *
 * Permet d'ajouter un élément dans l'ensemble passé en paramètre à la condition qu'il ne s'y trouve pas déjà.
 * Possibilité d'ajouter un ensemble dans un ensemble.
*/
void element_ajouter(Ensemble e, Type t) ;



/**
 * \fn void element_supprimer(Ensemble e, Type t)
 * \brief Supprimer un élément dans un ensemble.
 *
 * \param e Un ensemble dans lequel on veut supprimer un élément.
 * \param t Un type quelconque qui représente l'élément à supprimer.
 * \return Ne renvoie rien.
*/
void element_supprimer(Ensemble e, Type t);



/**
 * \fn int nombre_elements(Ensemble e)
 * \brief Indique le nombre d'éléments d'un ensemble.
 *
 * \param e L'ensemble dont on veut connaitre le nombre d'éléments.
 * \return Renvoie le nombre d'éléments de l'ensemble.
 *
 * Remarque : Un élement 'ensemble' compte pour un seul élément.
*/
int nombre_elements(Ensemble e);



/**
 * \fn int ensembles_egaux(Ensemble e1, Ensemble e2)
 * \brief Indique si deux ensembles sont égaux.
 *
 * \param e1 L'ensemble à comparer avec e2.
 * \param e2 L'ensemble à comparer avec e1.
 * \return Renvoie 1 si les deux ensembles sont égaux, 0 sinon.
 *
 * Permet de déterminer si deux ensembles sont égaux, c'est-à-dire s'ils possèdent les mêmes éléments.
 * Remarque : Dans le cas d'un élément 'ensemble' dans e1, on test également si tous ses éléments sont égaux aux éléments de l'élément 'ensemble' de e2.
*/
int ensembles_egaux(Ensemble e1, Ensemble e2);



/**
 * \fn int ensemble_meme_cardinalite(Ensemble e1, Ensemble e2)
 * \brief Indique si deux ensembles ont la même cardinalité.
 *
 * \param e1 L'ensemble à comparer avec e2.
 * \param e2 L'ensemble à comparer avec e1.
 * \return Renvoie 1 si les deux ensembles ont la même cardinalité, 0 sinon.
 *
 * Permet de déterminer si deux ensembles possèdent le même nombre d'éléments.
*/
int ensemble_meme_cardinalite(Ensemble e1, Ensemble e2);



/**
 * \fn Ensemble ensemble_union(Ensemble e1, Ensemble e2)
 * \brief L'union de deux ensembles.
 *
 * \param e1 Un ensemble 1.
 * \param e2 Un ensemble 2.
 * \return Renvoie un ensemble étant l'union des deux ensembles passés en paramètre.
 *
 * Permet de créer un ensemble qui contiendra tous les éléments de l'ensemble e1 et tous les éléments de l'ensemble e2.
 * Les possibles occurences ne seront pas traitées.
*/
Ensemble ensemble_union(Ensemble e1, Ensemble e2);



/**
 * \fn Ensemble ensemble_intersection(Ensemble e1, Ensemble e2)
 * \brief L'intersection de deux ensembles.
 *
 * \param e1 Un ensemble 1.
 * \param e2 Un ensemble 2.
 * \return Renvoie un ensemble étant l'intersection des deux ensembles passés en paramètre.
 *
 * Permet de créer un ensemble e3 qui contiendra tous éléments tel que si x appartient à e1 ET e2, x n'appartient pas à e3.
 * Les possibles occurences ne seront pas traitées.
*/
Ensemble ensemble_intersection(Ensemble e1, Ensemble e2);



/**
 * \fn Ensemble ensemble_difference(Ensemble e1, Ensemble e2)
 * \brief La différence de deux ensembles.
 *
 * \param e1 L'ensemble qui subira la différence avec e2.
 * \param e2 Un ensemble.
 * \return Renvoie un ensemble étant la différence des deux ensembles passés en paramètre.
 *
 * Permet de créer un ensemble e3 qui contiendra tous les éléments de e1 privés des éléments de e2.
*/
Ensemble ensemble_difference(Ensemble e1, Ensemble e2);



/**
 * \fn Ensemble ensemble_difference_symetrique(Ensemble e1, Ensemble e2)
 * \brief La différence symétrique de deux ensembles.
 *
 * \param e1 Un ensemble 1.
 * \param e2 Un ensemble 2.
 * \return Renvoie un ensemble étant la différence symetrique des deux ensembles passés en paramètre.
 *
 * Permet de créer un ensemble e3 qui contiendra l'union de e1 et e2 privée de l'intersection de e1 et e2.
*/
Ensemble ensemble_difference_symetrique(Ensemble e1, Ensemble e2);



#endif



