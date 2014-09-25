/*========================================================================
Nom: rendu.c            auteur: Gauthier Silvère
Maj:  11/4/2012         Creation: 12/3/2012
Projet: Gabarit3D
--------------------------------------------------------------------------
Specification:
Ce fichier contient les fonctions nécessaires au rendu 3D de l'objet.
=========================================================================*/

#include "rendu.h"
#include "fonc.h"

void Rendu3D(int nb_pts){
  //if(nb_pts>1){
    glPushMatrix();
      glTranslated(3*SCREEN_WIDTH/4,SCREEN_HEIGHT/2,0);
      glRotated(angleX,1,0,0);
      glRotated(angleY,0,1,0);
      glRotated(angleZ,0,0,1);
      
//Base initiale :
      if(fill){
        glBegin(GL_TRIANGLE_FAN);
          glColor3ub(220,115,10);
	    glNormal3f(0.0,1.0,0.0);
          glVertex3d(modele[0][0].x,modele[0][0].y,modele[0][0].z);  //point fixe
          for(int i=0;i<=precHorizontal;i++){
	      glNormal3fv(Normale(1.0,(float)(i%precHorizontal)));
            glVertex3d(modele[1][i%precHorizontal].x,modele[1][i%precHorizontal].y,modele[1][i%precHorizontal].z);
          }
        glEnd();
      }
      if(wireframe){
        glBegin(GL_LINE_LOOP);
          glColor3ub(0,0,0);
          for(int i=0;i<precHorizontal;i++){
            glVertex3d(modele[0][0].x,modele[0][0].y,modele[0][0].z);
            glVertex3d(modele[1][i].x,modele[1][i].y,modele[1][i].z);
	    glVertex3d(modele[1][(i+1)%precHorizontal].x,modele[1][(i+1)%precHorizontal].y,modele[1][(i+1)%precHorizontal].z);
          }
        glEnd();
      }
      
//Milieu :
    for(int i=2;i<nb_pts-1;i++){
	for(int j=0;j<=precHorizontal;j++){
	  if(fill){
            glBegin(GL_QUADS);
              glColor3ub(220,115,10);
	        glNormal3fv(Normale((float)i-1,(float)j));
	      glVertex3d(modele[i-1][j].x,modele[i-1][j].y,modele[i-1][j].z);
	        glNormal3fv(Normale((float)i,(float)j));
	      glVertex3d(modele[i][j].x,modele[i][j].y,modele[i][j].z);
	        glNormal3fv(Normale((float)i,(float)((j+1)%precHorizontal)));
	      glVertex3d(modele[i][(j+1)%precHorizontal].x,modele[i][(j+1)%precHorizontal].y,modele[i][(j+1)%precHorizontal].z);
	        glNormal3fv(Normale((float)i-1,(float)((j+1)%precHorizontal)));
	      glVertex3d(modele[i-1][(j+1)%precHorizontal].x,modele[i-1][(j+1)%precHorizontal].y,modele[i-1][(j+1)%precHorizontal].z);
	    glEnd();
	  }
	  if(wireframe){
	    glBegin(GL_LINE_LOOP);
              glColor3ub(0,0,0);
	      glVertex3d(modele[i-1][j].x,modele[i-1][j].y,modele[i-1][j].z);
	      glVertex3d(modele[i][j].x,modele[i][j].y,modele[i][j].z);
	      glVertex3d(modele[i][(j+1)%precHorizontal].x,modele[i][(j+1)%precHorizontal].y,modele[i][(j+1)%precHorizontal].z);
	      glVertex3d(modele[i-1][(j+1)%precHorizontal].x,modele[i-1][(j+1)%precHorizontal].y,modele[i-1][(j+1)%precHorizontal].z);
	    glEnd();
	  }
	}
    }
    
//Base finale :
    if(fill){
      glBegin(GL_TRIANGLE_FAN);
        glColor3ub(220,115,10);
	  glNormal3f(0.0,-1.0,0.0);
        glVertex3d(modele[nb_pts-1][0].x,modele[nb_pts-1][0].y,modele[nb_pts-1][0].z);  //point fixe
          for(int i=0;i<=precHorizontal;i++){
	      glNormal3fv(Normale((float)nb_pts-2,(float)(i%precHorizontal)));
            glVertex3d(modele[nb_pts-2][i%precHorizontal].x,modele[nb_pts-2][i%precHorizontal].y,modele[nb_pts-2][i%precHorizontal].z);
          }
      glEnd();
    }
    if(wireframe){
      glBegin(GL_LINE_LOOP);
        glColor3ub(0,0,0);
          for(int i=0;i<=precHorizontal;i++){
            glVertex3d(modele[nb_pts-1][0].x,modele[nb_pts-1][0].y,modele[nb_pts-1][0].z);
            glVertex3d(modele[nb_pts-2][i].x,modele[nb_pts-2][i].y,modele[nb_pts-2][i].z);
            glVertex3d(modele[nb_pts-2][(i+1)%precHorizontal].x,modele[nb_pts-2][(i+1)%precHorizontal].y,modele[nb_pts-2][(i+1)%precHorizontal].z);
          }
      glEnd();
    }
  glPopMatrix();
  //}
}
