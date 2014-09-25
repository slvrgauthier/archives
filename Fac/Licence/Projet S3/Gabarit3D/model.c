/*========================================================================
Nom: model.c            auteur: Gauthier Silvère
Maj:  11/4/2012         Creation: 12/3/2012
Projet: Gabarit3D
--------------------------------------------------------------------------
Specification:
Ce fichier contient les fonctions nécessaires au calcul du modèle 3D.
=========================================================================*/

#include "model.h"

int Modele3D(int nb_pts){
  if(nb_pts>1){
    double theta=2*PI/precHorizontal;
    modele[0][0].enable=1;
    modele[0][0].x=0;  //placement sur l'axe central du premier point
    modele[0][0].y=pts[0].y-SCREEN_HEIGHT/2;
    modele[0][0].z=pts[0].z;
    for(int i=1;i<nb_pts-1;i++){  //jusqu'à l'avant dernier point
      modele[i][0].enable=1;
      modele[i][0].x=pts[i].x-SCREEN_WIDTH/4;
      modele[i][0].y=pts[i].y-SCREEN_HEIGHT/2;
      modele[i][0].z=pts[i].z;
      for(int j=1;j<=precHorizontal;j++){
        modele[i][j].enable=1;
        modele[i][j].x=cos(theta)*modele[i][j-1].x + sin(theta)*modele[i][j-1].z;
        modele[i][j].y=modele[i][j-1].y;
        modele[i][j].z=cos(theta)*modele[i][j-1].z - sin(theta)*modele[i][j-1].x;
      }
    }
    modele[nb_pts-1][0].enable=1;
    modele[nb_pts-1][0].x=0;  //placement sur l'axe central du dernier point
    modele[nb_pts-1][0].y=pts[nb_pts-1].y-SCREEN_HEIGHT/2;
    modele[nb_pts-1][0].z=pts[nb_pts-1].z;
  }
  return nb_pts;
}
