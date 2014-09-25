/*========================================================================
Nom: var.c              auteur: Gauthier Silvère
Maj:  16/4/2012         Creation: 22/3/2012
Projet: Gabarit3D
--------------------------------------------------------------------------
Specification:
Ce fichier contient les variables globales du logiciel.
=========================================================================*/

#include "def.h"
#include "var.h"

// initialisation du tableau Gabarit
Point pts[NB_PTS]={{0,0,0,0}};

// initialisation du tableau Modèle
Point modele[NB_PTS][PREC_MAX]={{{0,0,0,0}}};

int precHorizontal=PREC_MIN;

int pause=0, wireframe=1, fill=1, undo=0, redo=0, light=0;

double angleX=0.0, angleY=0.0, angleZ=0.0;

double vitesse=VIT_MIN;

int mb1d=0,mb2d=0;  //Mouse Button 1/2 Down

int indPoint=-1;  //Indice du point sélectionné
