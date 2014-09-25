/*========================================================================
Nom: glutfonc.c         auteur: Gauthier Silvère
Maj:  11/4/2012         Creation: 12/3/2012
Projet: Gabarit3D
--------------------------------------------------------------------------
Specification:
Ce fichier contient les fonctions associées à glut.
=========================================================================*/

#include "glutfonc.h"

void visible(int vis){
  if (vis == GLUT_VISIBLE)
    glutIdleFunc(Idle);
  else
    glutIdleFunc(NULL);
}

void Idle(){
  int nWaitUntil = glutGet(GLUT_ELAPSED_TIME);
  int nTimer = glutGet(GLUT_ELAPSED_TIME);
  if(nTimer >= nWaitUntil){
    glutPostRedisplay();
    nWaitUntil = nTimer + (1000 / 20);
    if(pause==0)
      angleY=angleY+vitesse;
  }
}

void Reshape(int width, int height){
  glViewport(0,0,width,height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0,SCREEN_WIDTH,0,SCREEN_HEIGHT,-(SCREEN_HEIGHT+1),SCREEN_HEIGHT+1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  float pos[4]={3*SCREEN_WIDTH/4,3*SCREEN_HEIGHT/4,10,1};
  glLightfv(GL_LIGHT0, GL_POSITION, pos);
}

void keydown(unsigned char key, int x, int y){
  keys[key] = 1;
  switch(key){
    case 27: exit(EXIT_SUCCESS); break;  //echap
      
    case '+': if(precHorizontal<PREC_MAX) precHorizontal+=13; break;
    
    case '-': if(precHorizontal>PREC_MIN) precHorizontal-=13; break;
    
    case 'p': pause=(pause==1? 0 : 1); break;
    
    case 'w': wireframe=(wireframe==1? 0 : 1); break;
    
    case 'f': fill=(fill==1? 0 : 1); break;
    
    case 'l': light=(light==1? 0 : 1); if(light==0) glEnable(GL_LIGHTING); else glDisable(GL_LIGHTING); break;
    
    case 'z': if(actPoint()>0){
		pts[actPoint()-1].enable=0;
		undo++;
		redo--;
	      }
	      break;
	      
    case 'y': if(redo<undo){
	        pts[actPoint()].enable=1;
		undo--;
		redo++;
              }
	      break;
	      
    case 'c': for(int i=0;i<NB_PTS;i++) pts[i].enable=0; break;
    
    case 'r': angleX=angleZ=0.0; break;
  }
}

void keyup(unsigned char key, int x, int y){
  keys[key] = 0;
}
 
void specdown(int key, int x, int y){
  skeys[key] = 1;
  switch(key){
    case GLUT_KEY_LEFT: angleZ--; break;
    
    case GLUT_KEY_RIGHT: angleZ++; break;
    
    case GLUT_KEY_UP: angleX--; break;
    
    case GLUT_KEY_DOWN: angleX++; break;
    
    case GLUT_KEY_PAGE_DOWN: if(vitesse>VIT_MIN) vitesse-=0.1; break;
    
    case GLUT_KEY_PAGE_UP: if(vitesse<VIT_MAX) vitesse+=0.1; break;
  }
}
 
void specup(int key, int x, int y){
  skeys[key] = 0;
}

void mousedown(int button, int state, int x, int y){
  switch(button){
    case GLUT_LEFT_BUTTON:
      switch(state){
	case GLUT_DOWN:
	  mb1d=1;
          if(x>0 && x<SCREEN_WIDTH/2 && y>0 && y<SCREEN_HEIGHT){
	    int i=onPoint(x,SCREEN_HEIGHT-y);
	    if(i==-1)
	      addPoint(x,SCREEN_HEIGHT-y);  //repere souris != repere fenetre
	    else
	      indPoint=i;
	  }
	  break;
	case GLUT_UP:
	  mb1d=0;
	  indPoint=-1;
	  break;
      }
      break;
    case GLUT_RIGHT_BUTTON:
      switch(state){
	case GLUT_DOWN:
	  mb2d=1;
	  int i=onPoint(x,SCREEN_HEIGHT-y);  //repere souris != repere fenetre
	  if(i!=-1)
	      delPoint(i);
	  break;
	case GLUT_UP:
	  mb2d=0;
      }
  }
}

void motion(int x, int y){
  if(mb1d==1)
    if(x>0 && x<SCREEN_WIDTH/2 && y>0 && y<SCREEN_HEIGHT){
      if(indPoint!=-1){                            // -> gérer les collisions
        pts[indPoint].x=x;
        pts[indPoint].y=SCREEN_HEIGHT-y;
      }
    }
}
