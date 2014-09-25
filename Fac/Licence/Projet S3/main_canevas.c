//============================= Includes : ===============================
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h> /* include gl.h and glu.h with */

//============================= Macros : ===============================
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT  600

//============================= Variables Globales : ===============================
int keys[256];
int skeys[256];

//============================= Prototypes : ===============================
void InitGL();
void Draw();
void visible(int vis);
void Idle();
void Reshape(int width, int height);
void keydown(unsigned char key, int x, int y);
void keyup(unsigned char key, int x, int y);
void specdown(int key, int x, int y);
void specup(int key, int x, int y);
void mousedown(int button, int state, int x, int y);
void motion(int x, int y);

//============================= Main : ===============================
int main(int argc, char* argv[], char* env[]){

//Initialisation Glut et parametrage de la fenetre
  glutInit(&argc,argv);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow("Modelisation 3D depuis un gabarit");
  
  InitGL();
  
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
  
//Boucle d'évènements
  glutMainLoop();

return EXIT_SUCCESS;
}

//============================= Fonctions : ===============================
void InitGL(){
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);
}

void Draw(){
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0,SCREEN_WIDTH,0,SCREEN_HEIGHT,-SCREEN_WIDTH/4,SCREEN_WIDTH/4);
  
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

  glFlush();
    
  glutSwapBuffers();
}

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
  }
}

void Reshape(int width, int height){
  glViewport(0,0,width,height);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluLookAt(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0,SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0,0,1,0);
} 

void keydown(unsigned char key, int x, int y){
  keys[key] = 1;
  switch(key){
    case 27: exit(EXIT_SUCCESS); break;  //echap
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
    case GLUT_KEY_LEFT: /*instructions*/; break;
  }
}
 
void specup(int key, int x, int y){
  skeys[key] = 0;
  switch(key){
    /*case ... : instructions*/
  }
}

void mousedown(int button, int state, int x, int y){
  switch(button){
    case GLUT_LEFT_BUTTON:
      switch(state){
	case GLUT_DOWN:
	  /*instructions*/;
      }
  }
}

void motion(int x, int y){
  if(x>0 && x<SCREEN_WIDTH && y>0 && y<SCREEN_HEIGHT){
     /*instructions*/
  }
}


// gcc -std=c99 -Wall -lGL -lGLU -lglut -oprojet main.c
