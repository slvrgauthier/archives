/*========================================================================
Nom: fonc.h             auteur: Gauthier Silvère
Maj:  11/4/2012         Creation: 12/3/2012
Projet: Gabarit3D
--------------------------------------------------------------------------
Specification:
Ce fichier contient les entêtes des fonctions supplémentaires.
=========================================================================*/

#ifndef FONC_H
#define FONC_H


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h> /* inclut également gl.h et glu.h */

#include "def.h"
#include "var.h"


// initialisation de OpenGL
void InitGL();

// fonction indiquant si le pointeur souris est sur un point
int onPoint(int x, int y);

// ajout d'un point s'il n'existe pas dans la limite de points construits
void addPoint(int x, int y);

// suppression d'un point
void delPoint(int i);

// récupération du nombre de points actifs
int actPoint();

// fonction appelée lors d'un choix dans le menu déroulant
void menu(int option);

// calcul de la normale pour chaque point
float* Normale(int i, int j);

#endif
