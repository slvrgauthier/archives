/**
 * \file test_auto_nd.c
 * \brief Tests des Automates indéterministes.
 * \author Gauthier Silvère
 * 
 * Fichier de tests fonctionnels des automates indéterministes.
 * (non terminé car devait être repris par Abderrahim)
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include "auto_nd.h"

int main(int argc, char** argv, char** env) {

//===========Base
  
  //Ensemble...sigma,E,I,F,delta
  
  Automate_ND auto_nd1=auto_nd_creer();
  printf("Auto_nd1 : %s\n",auto_nd_chaine(auto_nd1));
  
  Automate_ND auto_nd2=auto_nd_creer();//P(sigma,E,I,F,delta);
  printf("Auto_nd2 : %s\n",auto_nd_chaine(auto_nd2));
  
  Automate_ND auto_nd3=auto_nd_clone(auto_nd2);
  printf("Auto_nd3 : %s\n",auto_nd_chaine(auto_nd3));
  
  auto_nd_detruire(auto_nd3);
  printf("Auto_nd3 : %s\n",auto_nd_chaine(auto_nd3));
  
  auto_nd3=auto_nd_clone(auto_nd2);
  printf("Auto_nd3 : %s\n",auto_nd_chaine(auto_nd3));

//===========Tests

  Etat e;
  String m;
  
  printf("Appartient : %d\n",auto_nd_appartient(m, auto_nd2));

  printf("Accessible : %d\n",auto_nd_accessible(e, auto_nd2));

  printf("Coaccessible : %d\n",auto_nd_coaccessible(e, auto_nd2));

  printf("Jumeuax : %d\n",auto_nd_jumeaux(auto_nd2, auto_nd3));

  printf("Equivalents : %d\n",auto_nd_equivalents(auto_nd2, auto_nd3));

//===========Attributs

  printf("NbLettres : %d\n",auto_nd_nbLettres(auto_nd2));

  printf("NbEtats : %d\n",auto_nd_nbEtats(auto_nd2));

  printf("NbInitiaux : %d\n",auto_nd_nbInitiaux(auto_nd2));

  printf("NbFinaux : %d\n",auto_nd_nbFinaux(auto_nd2));

  printf("NbTransitions : %d\n",auto_nd_nbTransitions(auto_nd2));

//===========Ajouts :

  Transition t;
  
  auto_nd_ajoutLettre('z', auto_nd2);
  printf("Auto_nd2 : %s\n",auto_nd_chaine(auto_nd2));

  auto_nd_ajoutEtat(e, auto_nd2);
  printf("Auto_nd2 : %s\n",auto_nd_chaine(auto_nd2));

  auto_nd_ajoutInitial(e, auto_nd2);
  printf("Auto_nd2 : %s\n",auto_nd_chaine(auto_nd2));

  auto_nd_ajoutFinal(e, auto_nd2);
  printf("Auto_nd2 : %s\n",auto_nd_chaine(auto_nd2));

  auto_nd_ajoutTransition(t, auto_nd2);
  printf("Auto_nd2 : %s\n",auto_nd_chaine(auto_nd2));

//===========Suppressions :

  auto_nd_supprLettre('z', auto_nd2);
  printf("Auto_nd2 : %s\n",auto_nd_chaine(auto_nd2));

  auto_nd_supprEtat(e, auto_nd2);
  printf("Auto_nd2 : %s\n",auto_nd_chaine(auto_nd2));

  auto_nd_supprTransition(t, auto_nd2);
  printf("Auto_nd2 : %s\n",auto_nd_chaine(auto_nd2));

//===========Divers :

  printf("Auto_nd1 : %s\n",auto_nd_chaine(auto_nd1));
  auto_nd1=auto_nd_completer(auto_nd2);
  printf("Auto_nd1 : %s\n",auto_nd_chaine(auto_nd1));

  printf("Auto_nd3 : %s\n",auto_nd_chaine(auto_nd3));
  auto_nd3=auto_nd_reduire(auto_nd2);
  printf("Auto_nd3 : %s\n",auto_nd_chaine(auto_nd3));

  printf("ListeMots : %s\n",auto_nd_listeMots(0, 3, auto_nd2));

  printf("ListeMotsAlpha : %s\n",auto_nd_listeMotsAlpha(0, 3, auto_nd2));

//===========Chemins et traces :

  printf("Chemin : %s\n",auto_nd_chemin(m, auto_nd2));

  printf("Chemins : %s\n",auto_nd_chemins(m, auto_nd2));

  printf("NbCheminsPossibles : %d\n",auto_nd_nbCheminsPossibles(m, auto_nd2));

// String auto_nd_trace(m, auto_nd2);
// String auto_nd_traces(m, auto_nd2);

  
  return 0;
}
