//============================= Includes : ===============================
#include <stdio.h>
#include <GL/glut.h> /* include gl.h and glu.h with */

//============================= Macros : ===============================
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT  600

//============================= Variables Globales : ===============================
int WindowName;
int keys[256];
int skeys[256];
typedef struct Point{
  int enable;
  int x;
  int y;
}Point;
Point pts[15]={0};

//============================= Prototypes : ===============================
void Draw();
void Reshape(int width, int height);
void Wait();
void keydown(unsigned char key, int x, int y);
void keyup(unsigned char key, int x, int y);
void specdown(int key, int x, int y);
void specup(int key, int x, int y);
void mousedown(int button, int state, int x, int y);
int onPoint(int x, int y);
void addPoint(int x, int y);

//============================= Main : ===============================
int main(int argc, char* argv[], char* env[]){

//Initialisation Glut et parametrage de la fenetre
  glutInit(&argc,argv);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
  WindowName=glutCreateWindow("Modelisation 3D depuis un gabarit");

//Fonctions de callback
  glutIdleFunc(Wait);
  glutReshapeFunc(Reshape);   //parametrage de OpenGL selon la fenêtre
  glutDisplayFunc(Draw);      //dessin
  glutKeyboardFunc(keydown);  //appuie sur une touche normale
  glutKeyboardUpFunc(keyup);  //relache la touche normale
  glutSpecialFunc(specdown);  //appuie sur une touche speciale
  glutSpecialUpFunc(specup);  //relache la touche speciale
  glutMouseFunc(mousedown);   //appuie ou relache un boutton souris
  
//Boucle d'évènements
  glutMainLoop();

return 0;
}

//============================= Fonctions : ===============================
void Draw(){
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  gluOrtho2D(0,SCREEN_WIDTH,0,SCREEN_HEIGHT);

  glClearColor(255,255,255,0); //Fond blanc
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//Trait central :
  glPushMatrix();
  glTranslated(SCREEN_WIDTH/2,0,0);
  glBegin(GL_QUADS);
    glColor3ub(0,0,0);
    glVertex2d(0,0);
    glVertex2d(0,SCREEN_HEIGHT);
    glVertex2d(1,SCREEN_HEIGHT);
    glVertex2d(1,0);
  glEnd();
//Fond bleu :
  glTranslated(1,0,0);
  glBegin(GL_QUADS);
    glColor3ub(0,0,0);
    glVertex2d(0,0);
    glVertex2d((SCREEN_WIDTH/2)-1,0);
    glColor3ub(45,150,225);
    glVertex2d((SCREEN_WIDTH/2)-1,SCREEN_HEIGHT);
    glVertex2d(0,SCREEN_HEIGHT);
  glEnd();
  glPopMatrix();

//Points :
  glPushMatrix();
  for(int i=0;i<15;i++)
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
  
//Segments :
  glPushMatrix();
    glBegin(GL_LINE_STRIP);
      glColor3ub(0,0,0);
      for(int i=0;i<15;i++)
        if(pts[i].enable==1)
          glVertex2d(pts[i].x,pts[i].y);
    glEnd();
  glPopMatrix();
  
  glFlush();
    
  glutSwapBuffers();
  glutPostRedisplay();
}

void Reshape(int width, int height){
  glViewport(0,0,width,height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, (float)width/(float)height, 0.1, 100);
  //glMatrixMode(GL_MODELVIEW);
} 

void Wait(){
  int nWaitUntil = glutGet(GLUT_ELAPSED_TIME);
  int nTimer = glutGet(GLUT_ELAPSED_TIME);
  if(nTimer >= nWaitUntil){
    glutPostRedisplay();
    nWaitUntil = nTimer + (1000 / 5);
  }
}

void keydown(unsigned char key, int x, int y){
  keys[key] = 1;
  switch(key){
    case 27: exit(0); break;
    //case 102: glutFullScreen(); break;
  }
}
 
void keyup(unsigned char key, int x, int y){
  keys[key] = 0;
  switch(key){
    
  }
}
 
void specdown(int key, int x, int y){
  skeys[key] = 1;
  switch(key){
    //case GLUT_KEY_F11: glutFullScreen(); break;
  }
}
 
void specup(int key, int x, int y){
  skeys[key] = 0;
  switch(key){
    
  }
}

void mousedown(int button, int state, int x, int y){
  switch(button){
    case GLUT_LEFT_BUTTON:
      switch(state){
	case GLUT_DOWN:
          if(x>0 && x<SCREEN_WIDTH/2 && y>0 && y<SCREEN_HEIGHT)
	    if(!onPoint(x,SCREEN_HEIGHT-y))
	      addPoint(x,SCREEN_HEIGHT-y);  //repere souris != repere fenetre
	  break;
      }
      break;
  }
}

int onPoint(int x, int y){
  for(int i=0;i<15;i++)
    if(pts[i].x>x-3 && pts[i].x<x+3 && pts[i].y>y-3 && pts[i].y<y+3)
      return 1;
  return 0;
}

void addPoint(int x, int y){
  int i=0;
  while(i<15 && pts[i].enable==1)
    i++;
  if(i<15){
    pts[i].enable=1;
    pts[i].x=x;
    pts[i].y=y;
    }
}

// gcc -std=c99 -Wall -lGL -lglut -otest main.c
