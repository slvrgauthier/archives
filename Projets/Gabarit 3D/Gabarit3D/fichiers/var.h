/*========================================================================
Nom: var.h              auteur: Gauthier Silvère
Maj:  16/4/2012         Creation: 22/3/2012
Projet: Gabarit3D
--------------------------------------------------------------------------
Specification:
Ce fichier contient les déclarations des variables globales du logiciel.
=========================================================================*/

#ifndef VAR_H
#define VAR_H


// déclaration du tableau de caractères ASCII
int keys[256];

// déclaration du tableau de caractères spéciaux
int skeys[256];

// déclaration de la structure de donnée permettant de stocker un point
typedef struct Point{ int enable; double x; double y; double z;}Point;

// déclaration du tableau Gabarit
extern Point pts[NB_PTS];

// déclaration du tableau Modèle
extern Point modele[NB_PTS][PREC_MAX];

// définition de la précision horizontale actuelle
extern int precHorizontal;

// définition des booléens utiles aux options
extern int pause, wireframe, fill, undo, redo, light;

// définition des angles de rotation courants
extern double angleX, angleY, angleZ;

// définition de la vitesse de rotation courante
extern double vitesse;

// déclaration de booléens indiquant l'état des boutons de souris
extern int mb1d, mb2d;

// déclaration d'un entier utile à plusieurs fonctions
extern int indPoint;

// déclaration du tableau de normale
float N[3];

#endif
