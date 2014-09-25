/*========================================================================
Nom: model.h            auteur: Gauthier Silvère
Maj:  11/4/2012         Creation: 12/3/2012
Projet: Gabarit3D
--------------------------------------------------------------------------
Specification:
Ce fichier contient les entêtes des fonctions nécessaires au calcul du 
modèle 3D.
=========================================================================*/

#ifndef MODEL_H
#define MODEL_H


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h> /* inclut également gl.h et glu.h */

#include "def.h"
#include "var.h"


int Modele3D(int nb_pts);

#endif
