/*========================================================================
Nom: rendu.h            auteur: Gauthier Silvère
Maj:  11/4/2012         Creation: 12/3/2012
Projet: Gabarit3D
--------------------------------------------------------------------------
Specification:
Ce fichier contient les entêtes des fonctions nécessaires au rendu 3D de 
l'objet.
=========================================================================*/

#ifndef RENDU_H
#define RENDU_H


#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h> /* inclut également gl.h et glu.h */

#include "def.h"
#include "var.h"


void Rendu3D(int nb_pts);

#endif
