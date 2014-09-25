/*========================================================================
Nom: glutfonc.h         auteur: Gauthier Silvère
Maj:  11/4/2012         Creation: 12/3/2012
Projet: Gabarit3D
--------------------------------------------------------------------------
Specification:
Ce fichier contient les entêtes des fonctions associées à glut.
=========================================================================*/

#ifndef GLUTFONC_H
#define GLUTFONC_H


#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h> /* inclut également gl.h et glu.h */

#include "def.h"
#include "var.h"
#include "fonc.h"


// fonction appelée lorsque la fenêtre est minimisée ou rétablie
void visible(int vis);

// fonction appelée continuellement pour rafraîchir la fenêtre
void Idle();

// fonction appelée lors d'un redimensionnement de la fenêtre
void Reshape(int width, int height);

// fonction appelée lors d'un appui sur une touche clavier ASCII
void keydown(unsigned char key, int x, int y);

// fonction appelée lors d'un relâchement de touche clavier ASCII
void keyup(unsigned char key, int x, int y);

// fonction appelée lors d'un appui sur une touche clavier spéciale
void specdown(int key, int x, int y);

// fonction appelée lors d'un relâchement d'une touche clavier spéciale
void specup(int key, int x, int y);

// fonction appelée lors d'un appui sur un bouton de souris
void mousedown(int button, int state, int x, int y);

// fonction appelée lors d'un déplacement de souris
void motion(int x, int y);


#endif
