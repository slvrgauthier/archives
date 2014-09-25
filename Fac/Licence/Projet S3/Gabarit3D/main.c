/*========================================================================
Nom: main.c             auteur: Gauthier Silvère
Maj:  11/4/2012         Creation: 12/3/2012
Projet: Gabarit3D
--------------------------------------------------------------------------
Specification:
Ce fichier contient la boucle principale du programme.
=========================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h> /* inclut également gl.h et glu.h */

#include "def.h"
#include "var.h"
#include "fonc.h"
#include "glutfonc.h"
#include "dessin.h"
#include "model.h"
#include "rendu.h"

int main(int argc, char* argv[], char* env[]){

//Initialisation Glut et parametrage de la fenetre
  glutInit(&argc,argv);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow("Modelisation 3D depuis un gabarit");
  
  InitGL();  //paramétrage de OpenGL
  
//Fonctions de callback
  glutDisplayFunc(Draw);        //dessin
  glutVisibilityFunc(visible);  //visibilité : idle
  glutReshapeFunc(Reshape);     //parametrage de OpenGL selon la fenêtre
  glutKeyboardFunc(keydown);    //appuie sur une touche normale
  glutKeyboardUpFunc(keyup);    //relache la touche normale
  glutSpecialFunc(specdown);    //appuie sur une touche speciale
  glutSpecialUpFunc(specup);    //relache la touche speciale
  glutMouseFunc(mousedown);     //appuie ou relache un boutton souris
  glutMotionFunc(motion);       //cliquer glisser
  
//Menu
  int precMenu=glutCreateMenu(menu);
  glutAddMenuEntry("Increase (+)",220);
  glutAddMenuEntry("Decrease (-)",221);
  
  int vitMenu=glutCreateMenu(menu);
  glutAddMenuEntry("Increase (PgUp)",230);
  glutAddMenuEntry("Decrease (PgDn)",231);
  
  int viewMenu=glutCreateMenu(menu);
  glutAddMenuEntry("Wireframe (w)",20);
  glutAddMenuEntry("Fill (f)",21);
  glutAddMenuEntry("Light (l)",22);
  glutAddSubMenu("Precision",precMenu);
  glutAddSubMenu("Vitesse",vitMenu);
  
  int mainMenu=glutCreateMenu(menu);
  //glutAddMenuEntry("Load (à implémenter)",0);
  //glutAddMenuEntry("Save (à implémenter)",1);
  glutAddSubMenu("View",viewMenu);
  glutAddMenuEntry("Undo (z)",3);
  glutAddMenuEntry("Redo (y)",4);
  glutAddMenuEntry("Pause (p)",6);
  glutAddMenuEntry("Clear (c)",7);
  glutAddMenuEntry("Replace (r)",8);
  //glutAddMenuEntry("Aide (à implémenter)",9);
  glutAddMenuEntry("Close (Esc)",10);
  
  glutAttachMenu(GLUT_MIDDLE_BUTTON);

//Boucle d'évènements
  glutMainLoop();

return EXIT_SUCCESS;
}
