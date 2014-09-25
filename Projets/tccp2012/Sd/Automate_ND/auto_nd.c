/**
 * \file auto_nd.c
 * \brief Code des Automates indéterministes.
 * \author Gauthier Silvère
 * 
 * Fichier d'implémentation fonctions concernant les automates indéterministes.
 * (non terminé par manque de temps, travaillant seul...)
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "auto_nd.h"

//======================================================================
//==============================Fonctions de base :=====================

Automate_ND auto_nd_creer() {
  Automate_ND auto_nd;
  auto_nd->sigma=ensemble_creer();
  auto_nd->E=ensemble_creer();
  auto_nd->I=ensemble_creer();
  auto_nd->F=ensemble_creer();
  auto_nd->delta=ensemble_creer();
  return auto_nd;
}

Automate_ND auto_nd_creerP(EnsembleCar s, EnsembleEtat e, EnsembleEtat i, EnsembleEtat f, EnsembleTransition d) {
  Automate_ND auto_nd;
  auto_nd->sigma=ensemble_clone(s);
  auto_nd->E=ensemble_clone(e);
  auto_nd->I=ensemble_clone(i);
  auto_nd->F=ensemble_clone(f);
  auto_nd->delta=ensemble_clone(d);
  return auto_nd;
}

Entier auto_nd_detruire(Automate_ND auto_nd) {
  if(ensemble_detruire(auto_nd->sigma) || ensemble_detruire(auto_nd->E) || ensemble_detruire(auto_nd->I) || ensemble_detruire(auto_nd->F) || ensemble_detruire(auto_nd->delta)) {
    printf("Erreur dans la destruction des Ensembles");
    return 1; }
  else
    return 0;
}

Automate_ND auto_nd_clone(Automate_ND auto_nd) {
  return auto_nd_creer(auto_nd->sigma, auto_nd->E, auto_nd->I, auto_nd->F, auto_nd->delta);
}

String auto_nd_chaine(Automate_ND auto_nd) {
  char* s = "Cet automate est défini par : \nl'alphabet ";
  strcat(s, ensemble_chaine(auto_nd->sigma)); 
  strcat(s, "\nl'ensemble d'états "); 
  strcat(s, ensemble_chaine(auto_nd->E));
  strcat(s, "\nles états initiaux "); 
  strcat(s, ensemble_chaine(auto_nd->I));
  strcat(s, "\nles états finaux "); 
  strcat(s, ensemble_chaine(auto_nd->F));
  strcat(s, "\nles transitions "); 
  strcat(s, ensemble_chaine(auto_nd->delta));
  strcat(s, "\n");
  
  return String_Creer(s);
}

//======================================================================
//==============================Tests :=================================

Entier auto_nd_appartient(String mot, Automate_ND auto_nd);

Entier auto_nd_accessible(Etat e, Automate_ND auto_nd);

Entier auto_nd_coaccessible(Etat e, Automate_ND auto_nd);

Entier auto_nd_jumeaux(Automate_ND auto_nd1, Automate_ND auto_nd2);

Entier auto_nd_equivalents(Automate_ND auto_nd1, Automate_ND auto_nd2);

//======================================================================
//==============================Attributs :=============================

Entier auto_nd_nbLettres(Automate_ND auto_nd);

Entier auto_nd_nbEtats(Automate_ND auto_nd);

Entier auto_nd_nbInitiaux(Automate_ND auto_nd);

Entier auto_nd_nbFinaux(Automate_ND auto_nd);

Entier auto_nd_nbTransitions(Automate_ND auto_nd);

//======================================================================
//==============================Ajouts :================================

void auto_nd_ajoutLettre(Car c, Automate_ND auto_nd);

void auto_nd_ajoutEtat(Etat e, Automate_ND auto_nd);

void auto_nd_ajoutInitial(Etat i, Automate_ND auto_nd);

void auto_nd_ajoutFinal(Etat f, Automate_ND auto_nd);

void auto_nd_ajoutTransition(Transition t, Automate_ND auto_nd);

//======================================================================
//==============================Suppressions :==========================

void auto_nd_supprLettre(Car c, Automate_ND auto_nd);

void auto_nd_supprEtat(Etat e, Automate_ND auto_nd);

void auto_nd_supprTransition(Transition t, Automate_ND auto_nd);

//======================================================================
//==============================Divers :================================

Automate_ND auto_nd_completer(Automate_ND auto_nd);

Automate_ND auto_nd_reduire(Automate_ND auto_nd);

String auto_nd_listeMots(Entier debut, Entier fin, Automate_ND auto_nd);

String auto_nd_listeMotsAlpha(Entier debut, Entier fin, Automate_ND auto_nd);

//======================================================================
//==============================Chemins et traces :=====================

String auto_nd_chemin(String mot, Automate_ND auto_nd);

String auto_nd_chemins(String mot, Automate_ND auto_nd);

Entier auto_nd_nbCheminsPossibles(String mot, Automate_ND auto_nd);

// String auto_nd_trace(String mot, Automate_ND auto_nd);
// String auto_nd_traces(String mot, Automate_ND auto_nd);
