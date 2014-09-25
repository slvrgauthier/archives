/**
 * \file auto_nd.h
 * \brief Header des Automates indéterministes.
 * \author Gauthier Silvère
 * 
 * Fichier de définition des types, structures et fonctions concernant les automates indéterministes.
 * 
 */

#ifndef AUTO_ND_H
#define AUTO_ND_H

#include "../TypesBase/TypeBase.h"
#include "../Ensembles/ensemble.h"
//#include "../Grammaires/grammaire.h"
//#include "../Automate_D/auto_d.h"

/** 
 * Types abstraits utilisés pour les automates indéterministes.
 */
typedef Entier Etat;
typedef Ensemble EnsembleEtat;
typedef Ensemble EnsembleCar;
typedef Ensemble EnsembleTransition;

/** 
 * \struct Transition
 * \brief Objet fonction de transition.
 * 
 * Transition est un pointeur sur un triplet (e,a,e') représentant une transition par la fonction delta d'un automate.
 */
typedef struct Transition {
  Etat initial;/*!< Etat de départ de la transition. */
  Car alpha;/*!< Lettre ASCII de transition. */
  Etat final;/*!< Etat d'arrivée de la transition. */
}* Transition;

/** 
 * \struct Automate_ND
 * \brief Objet automate indéterministe.
 * 
 * Automate_ND est un pointeur sur un ensemble d'ensembles définissant un automate indéterministe. Il comprend un alphabet ASCII (sigma), un ensemble total d'états (E), un ensemble d'états initiaux (I), un ensemble d'états finaux (F) et un ensemble de transitions représentant la fonction delta d'un automate (delta).
 */
typedef struct Automate_ND {
  EnsembleCar sigma;/*!< Alphabet ASCII. */
  EnsembleEtat E;/*!< Ensemble total d'états. */
  EnsembleEtat I;/*!< Ensemble d'états initiaux. */
  EnsembleEtat F;/*!< Ensemble d'états finaux. */
  EnsembleTransition delta;/*!< Fonction de transition. */
} *Automate_ND;

//======================================================================
//==============================Fonctions de base :=====================
/** 
 * \fn Automate_ND auto_nd_creer()
 * \brief Création d'un automate indéterministe vide.
 * 
 * \return Instance nouvelle d'un Automate_ND alloué d'ensembles vides.
 */
Automate_ND auto_nd_creer();

/** 
 * \fn Automate_ND auto_nd_creerP(EnsembleCar s, EnsembleEtat e, EnsembleEtat i, EnsembleEtat f, EnsembleTransition d)
 * \brief Création d'un automate indéterministe non vide.
 * 
 * \param[in] s Alphabet sigma. Peux être vide.
 * \param[in] e Ensemble total d'états E. Peux être vide.
 * \param[in] i pour I. Peux être vide.
 * \param[in] f pour F. Peux être vide.
 * \param[in] d pour delta. Peux être vide.
 * \return Instance nouvelle d'un Automate_ND alloué des ensembles passés en paramètres.
 */
Automate_ND auto_nd_creerP(EnsembleCar s, EnsembleEtat e, EnsembleEtat i, EnsembleEtat f, EnsembleTransition d);

/** 
 * \fn auto_nd_detruire(Automate_ND auto_nd)
 * \brief Destruction d'un automate indéterministe.
 * 
 * \param[in,out] auto_nd Automate à détruire.
 * \return 0 si aucune erreur, 1 sinon.
 */
Entier auto_nd_detruire(Automate_ND auto_nd);

/** 
 * \fn Automate_ND auto_nd_clone(Automate_ND auto_nd)
 * \brief Clonage d'un automate indéterministe.
 * 
 * \param[in] auto_nd Automate à cloner.
 * \return Instance nouvelle d'un Automate_ND alloué d'ensembles identiques à auto_nd (par copie).
 */
Automate_ND auto_nd_clone(Automate_ND auto_nd);

/** 
 * \fn String auto_nd_chaine(Automate_ND auto_nd)
 * \brief Description d'un automate indéterministe.
 * 
 * \param[in] auto_nd Automate à décrire.
 * \return Chaîne de caractères décrivant l'automate indéterministe passé en paramètre.
 */
String auto_nd_chaine(Automate_ND auto_nd);

//======================================================================
//==============================Tests :=================================
/**
 * \fn Entier auto_nd_appartient?(String mot, Automate_ND auto_nd)
 * \brief Test d'appartenance d'un mot au langage d'un automate indéterministe.
 * 
 * \param[in] mot Mot à tester.
 * \param[in] auto_nd Automate sur lequel faire le test.
 * \return 1 si appartenance, 0 sinon.
 */
Entier auto_nd_appartient(String mot, Automate_ND auto_nd);

/**
 * \fn Entier auto_nd_accessible?(Etat e, Automate_ND auto_nd)
 * \brief Test d'accessibilité d'un état d'un automate indéterministe.
 * 
 * \param[in] e Etat à tester.
 * \param[in] auto_nd Automate sur lequel faire le test.
 * \return 1 si accessibilité, 0 sinon.
 */
Entier auto_nd_accessible(Etat e, Automate_ND auto_nd);

/**
 * \fn Entier auto_nd_coaccessible?(Etat e, Automate_ND auto_nd)
 * \brief Test de co-accessibilité d'un état d'un automate indéterministe.
 * 
 * \param[in] e Etat à tester.
 * \param[in] auto_nd Automate sur lequel faire le test.
 * \return 1 si co-accessibilité, 0 sinon.
 */
Entier auto_nd_coaccessible(Etat e, Automate_ND auto_nd);

/**
 * \fn Entier auto_nd_jumeaux?(Automate_ND auto_nd1, Automate_ND auto_nd2)
 * \brief Test de gémélité (clone) entre deux automates indéterministes.
 * 
 * \param[in] auto_nd1 Premier automate à tester.
 * \param[in] auto_nd2 Deuxième automate à tester.
 * \return 1 si gémélité, 0 sinon.
 */
Entier auto_nd_jumeaux(Automate_ND auto_nd1, Automate_ND auto_nd2);

/**
 * \fn Entier auto_nd_equivalents?(Automate_ND auto_nd1, Automate_ND auto_nd2)
 * \brief Test d'équivalence (langage) de deux automates indéterministes.
 * 
 * \param[in] auto_nd1 Premier automate à tester.
 * \param[in] auto_nd2 Deuxième automate à tester.
 * \return 1 si équivalence, 0 sinon.
 */
Entier auto_nd_equivalents(Automate_ND auto_nd1, Automate_ND auto_nd2);

//======================================================================
//==============================Attributs :=============================
/**
 * \fn Entier auto_nd_nbLettres(Automate_ND auto_nd)
 * \brief Nombre de lettre de l'alphabet d'un automate indéterministe.
 * 
 * \param[in] auto_nd Automate à interroger.
 * \return Le nombre (entier) de lettres de sigma.
 */
Entier auto_nd_nbLettres(Automate_ND auto_nd);

/**
 * \fn Entier auto_nd_nbEtats(Automate_ND auto_nd)
 * \brief Nombre d'états total d'un automate indéterministe.
 * 
 * \param[in] auto_nd Automate à interroger.
 * \return Le nombre (entier) d'états de E.
 */
Entier auto_nd_nbEtats(Automate_ND auto_nd);

/**
 * \fn Entier auto_nd_nbInitiaux(Automate_ND auto_nd)
 * \brief Nombre d'états initiaux d'un automate indéterministe.
 * 
 * \param[in] auto_nd Automate à interroger.
 * \return Le nombre (entier) d'états de I.
 */
Entier auto_nd_nbInitiaux(Automate_ND auto_nd);

/**
 * \fn Entier auto_nd_nbFinaux(Automate_ND auto_nd)
 * \brief Nombre d'états finaux d'un automate indéterministe.
 * 
 * \param[in] auto_nd Automate à interroger.
 * \return Le nombre (entier) d'états de F.
 */
Entier auto_nd_nbFinaux(Automate_ND auto_nd);

/**
 * \fn Entier auto_nd_nbTransitions(Automate_ND auto_nd)
 * \brief Nombre de transitions d'un automate indéterministe.
 * 
 * \param[in] auto_nd Automate à interroger.
 * \return Le nombre (entier) de transitions de delta.
 */
Entier auto_nd_nbTransitions(Automate_ND auto_nd);

//======================================================================
//==============================Ajouts :================================
/**
 * \fn Entier auto_nd_ajoutLettre(Car c, Automate_ND auto_nd)
 * \brief Ajoute une lettre ASCII à l'alphabet d'un automate indéterministe.
 * 
 * \param[in] c Lettre ASCII à ajouter. Les doublons sont gérés.
 * \param[in,out] auto_nd Automate auquel ajouter.
 */
void auto_nd_ajoutLettre(Car c, Automate_ND auto_nd);

/**
 * \fn void auto_nd_ajoutEtat(Etat e, Automate_ND auto_nd)
 * \brief Ajoute un état (non initial, non final) à un automate indéterministe.
 * 
 * \param[in] e Etat à ajouter. Les doublons sont gérés.
 * \param[in,out] auto_nd Automate auquel ajouter.
 */
void auto_nd_ajoutEtat(Etat e, Automate_ND auto_nd);

/**
 * \fn void auto_nd_ajoutInitial(Etat i, Automate_ND auto_nd)
 * \brief Ajoute un état initial à un automate indéterministe.
 * 
 * \param[in] i Etat initial à ajouter. Les doublons sont gérés.
 * \param[in,out] auto_nd Automate auquel ajouter.
 */
void auto_nd_ajoutInitial(Etat i, Automate_ND auto_nd);

/**
 * \fn void auto_nd_ajoutFinal(Etat f, Automate_ND auto_nd)
 * \brief Ajoute un état final à un automate indéterministe.
 * 
 * \param[in] f Etat final à ajouter. Les doublons sont gérés.
 * \param[in,out] auto_nd Automate auquel ajouter.
 */
void auto_nd_ajoutFinal(Etat f, Automate_ND auto_nd);

/**
 * \fn void auto_nd_ajoutTransition(Transition t, Automate_ND auto_nd)
 * \brief Ajoute une transition à un automate indéterministe.
 * 
 * \param[in] t Transition à ajouter. Les doublons sont gérés.
 * \param[in,out] auto_nd Automate auquel ajouter.
 */
void auto_nd_ajoutTransition(Transition t, Automate_ND auto_nd);

//======================================================================
//==============================Suppressions :==========================
/**
 * \fn void auto_nd_supprLettre(Car c, Automate_ND auto_nd)
 * \brief Retire une lettre ASCII à l'alphabet d'un automate indéterministe.
 * 
 * \param[in] c Lettre ASCII à retirer.
 * \param[in,out] auto_nd Automate auquel retirer.
 */
void auto_nd_supprLettre(Car c, Automate_ND auto_nd);

/**
 * \fn void auto_nd_supprEtat(Etat e, Automate_ND auto_nd)
 * \brief Retire un état à un automate indéterministe.
 * 
 * \param[in] e Etat à retirer. Peut être initial, quelconque ou final.
 * \param[in,out] auto_nd Automate auquel retirer.
 */
void auto_nd_supprEtat(Etat e, Automate_ND auto_nd);

/**
 * \fn void auto_nd_supprTransition(Transition t, Automate_ND auto_nd)
 * \brief Retire une transition à un automate indéterministe.
 * 
 * \param[in] t Transition à retirer.
 * \param[in,out] auto_nd Automate auquel retirer.
 */
void auto_nd_supprTransition(Transition t, Automate_ND auto_nd);

//======================================================================
//==============================Divers :================================
/**
 * \fn Automate_ND auto_nd_completer(Automate_ND auto_nd)
 * \brief Complète un automate indéterministe.
 * 
 * \param[in] auto_nd Automate à compléter. Peut être complet.
 * \return Un Automate_ND correspondant à l'automate paramètre complété.
 */
Automate_ND auto_nd_completer(Automate_ND auto_nd);

/**
 * \fn Automate_ND auto_nd_reduire(Automate_ND auto_nd)
 * \brief Réduit un automate indéterministe.
 * 
 * \param[in] auto_nd Automate à compléter. Peut être réduit.
 * \return Un Automate_ND correspondant à l'automate paramètre réduit.
 */
Automate_ND auto_nd_reduire(Automate_ND auto_nd);

/**
 * \fn String auto_nd_listeMots(Entier debut, Entier fin, Automate_ND auto_nd)
 * \brief Liste les mots (suivant une fourchette de longueur) appartenants au langage d'un automate indéterministe.
 * 
 * \param[in] debut Nombre minimal de lettres ASCII. Doit être positif.
 * \param[in] fin Nombre maximal de lettres ASCII. Doit être positif et supérieur à début.
 * \param[in] auto_nd Automate à interroger.
 * \return Une chaîne de caractères correspondant à la liste des mots de longueur 'debut' à longueur 'fin'.
 */
String auto_nd_listeMots(Entier debut, Entier fin, Automate_ND auto_nd);

/**
 * \fn String auto_nd_listeMotsAlpha(Entier debut, Entier fin, Automate_ND auto_nd)
 * \brief Liste lexicographiquement les mots (suivant une fourchette de longueur) appartenants au langage d'un automate indéterministe.
 * 
 * \param[in] debut Nombre minimal de lettres ASCII. Doit être positif.
 * \param[in] fin Nombre maximal de lettres ASCII. Doit être positif et supérieur à début.
 * \param[in] auto_nd Automate à interroger.
 * \return Une chaîne de caractères correspondant à la liste des mots de longueur 'debut' à longueur 'fin', rangée en ordre lexicographique.
 */
String auto_nd_listeMotsAlpha(Entier debut, Entier fin, Automate_ND auto_nd);

//======================================================================
//==============================Chemins et traces :=====================
/**
 * \fn String auto_nd_chemin(String mot, Automate_ND auto_nd)
 * \brief Fourni un chemin possible d'un mot pour un automate indéterministe donné.
 * 
 * \param[in] mot Chaine de caractères ASCII à tester.
 * \param[in] auto_nd Automate à interroger.
 * \return Une chaine de caractères correspondant au chemin parcouru, s'il existe. NULL sinon.
 */
String auto_nd_chemin(String mot, Automate_ND auto_nd);

/**
 * \fn String auto_nd_chemins(String mot, Automate_ND auto_nd)
 * \brief Fourni la liste de tous les chemins possible d'un mot pour un automate indéterministe donné.
 * 
 * \param[in] mot Chaine de caractères ASCII à tester.
 * \param[in] auto_nd Automate à interroger.
 * \return Une chaine de caractères correspondant à la liste des chemins parcourus, s'ils existent. NULL sinon.
 */
String auto_nd_chemins(String mot, Automate_ND auto_nd);

/**
 * \fn Entier auto_nd_nbCheminsPossibles(String mot, Automate_ND auto_nd)
 * \brief Nombre de chemins possibles d'un mot pour un automate indéterministe donné.
 * 
 * \param[in] mot Chaine de caractères ASCII à tester.
 * \param[in] auto_nd Automate à interroger.
 * \return Un entier correspondant au nombre total de chemins possibles.
 */
Entier auto_nd_nbCheminsPossibles(String mot, Automate_ND auto_nd);

// String auto_nd_trace(String mot, Automate_ND auto_nd);
// String auto_nd_traces(String mot, Automate_ND auto_nd);

#endif
