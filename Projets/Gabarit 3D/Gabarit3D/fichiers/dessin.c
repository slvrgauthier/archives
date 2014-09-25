/*========================================================================
Nom: dessin.c           auteur: Gauthier Silvère
Maj:  11/4/2012         Creation: 12/3/2012
Projet: Gabarit3D
--------------------------------------------------------------------------
Specification:
Ce fichier contient les fonctions nécessaires au rendu de la fenêtre.
=========================================================================*/

#include "dessin.h"

void Draw(){  
  glClearColor(255,255,255,0); //Fond blanc
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//Axe y :
  glPushMatrix();
  glTranslated(SCREEN_WIDTH/4,0,0);
  glLineWidth(1);
  glBegin(GL_LINES);
    glColor3ub(0,0,0);
    for(int i=0;i<SCREEN_HEIGHT;i+=10)
      glVertex2d(0,i);
  glEnd();
  glPopMatrix();
  
//Trait central :
  glPushMatrix();
  glTranslated(SCREEN_WIDTH/2,0,0);
  glLineWidth(2);
  glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2d(0,0);
    glVertex2d(0,SCREEN_HEIGHT);
  glEnd();
  glLineWidth(1);
  
//Fond bleu :
  glTranslated(1,0,-SCREEN_HEIGHT);
  glBegin(GL_QUADS);
    glColor3ub(0,0,0);
    glNormal3f(0.0,0.0,1.0);
    glVertex2d(0,0);
    glVertex2d((SCREEN_WIDTH/2)-1,0);
    glColor3ub(45,150,225);
    glVertex2d((SCREEN_WIDTH/2)-1,SCREEN_HEIGHT);
    glVertex2d(0,SCREEN_HEIGHT);
  glEnd();
  glPopMatrix();

//Points :
  glPushMatrix();
  for(int i=0;i<NB_PTS;i++)
    if(pts[i].enable==1){
      glBegin(GL_QUADS);
        glColor3ub(0,0,0);
	glVertex2d(pts[i].x-2,pts[i].y-2);
	glVertex2d(pts[i].x-2,pts[i].y+2);
	glVertex2d(pts[i].x+2,pts[i].y+2);
	glVertex2d(pts[i].x+2,pts[i].y-2);
      glEnd();
    }   
  glPopMatrix();
  
//Segments reliant les points :
  glPushMatrix();
    glBegin(GL_LINE_STRIP);
      glColor3ub(0,0,0);
      for(int i=0;i<NB_PTS;i++)
        if(pts[i].enable==1)
          glVertex2d(pts[i].x,pts[i].y);
    glEnd();
  glPopMatrix();
  
  
//Figure 3D :
  Rendu3D(Modele3D(actPoint()));

  glFlush();
    
  glutSwapBuffers();
}
