//============================= Includes : ===============================
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h> /* include gl.h and glu.h with */

//============================= Macros : ===============================
#define PI (3.141592653589793)
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT  600
#define PREC_MAX  49
#define PREC_MIN  10
#define VIT_MAX 0.35
#define VIT_MIN 0.05
#define NB_PTS  15

//============================= Variables Globales : ===============================
int keys[256];
int skeys[256];
typedef struct Point{ int enable; double x; double y; double z;}Point;
Point pts[NB_PTS]={{0,0,0,0}};
Point modele[NB_PTS][PREC_MAX]={{{0,0,0,0}}};

int precHorizontal=PREC_MIN;
int pause=0, wireframe=1, fill=1, undo=0, redo=0;
double angleX=0.0, angleY=0.0, angleZ=0.0;
double vitesse=VIT_MIN;
int mb1d=0,mb2d=0;  //Mouse Button 1/2 Down
int indPoint=-1;  //Indice du point sélectionné

/*float MatSpec[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float MatDif[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float MatAmb[4] = {0.3f, 0.3f, 0.3f, 1.0f};*/
 
float Light1Pos[4] = {1.0, 0.0, 1.0, 0.0};
/*float Light1Dif[4] = {1.0f, 0.2f, 0.2f, 1.0f};
float Light1Spec[4] = {1.0f, 0.2f, 0.2f, 1.0f};
float Light1Amb[4] = {0.5f, 0.5f, 0.5f, 1.0f};
float Light1Dir[3] = {0.0f, 1.0f, 0.0f};*/ 

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
  int onPoint(int x, int y);
  void addPoint(int x, int y);
  void delPoint(int i);
void motion(int x, int y);

int actPoint();
int Modele3D(int nb_pts);
void Rendu3D(int nb_pts);

void menu(int option);

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
  
//Menu
  int precMenu=glutCreateMenu(menu);
  glutAddMenuEntry("Increase (+)",220);
  glutAddMenuEntry("Decrease (-)",221);
  
  int viewMenu=glutCreateMenu(menu);
  glutAddMenuEntry("Wireframe (w)",20);
  glutAddMenuEntry("Fill (f)",21);
  glutAddSubMenu("Precision",precMenu);
  
  int mainMenu=glutCreateMenu(menu);
  glutAddMenuEntry("Load (à implémenter)",0);
  glutAddMenuEntry("Save (à implémenter)",1);
  glutAddSubMenu("View",viewMenu);
  glutAddMenuEntry("Undo (z)",3);
  glutAddMenuEntry("Redo (y)",4);
  glutAddMenuEntry("Pause (p)",6);
  glutAddMenuEntry("Clear (c)",7);
  glutAddMenuEntry("Replace (r)",8);
  glutAddMenuEntry("Aide (à implémenter)",9);
  glutAddMenuEntry("Close (Esc)",10);
  
  glutAttachMenu(GLUT_MIDDLE_BUTTON);

//Boucle d'évènements
  glutMainLoop();

return EXIT_SUCCESS;
}

//============================= Fonctions : ===============================
void InitGL(){
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);
  
  /*glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,MatSpec);
  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,MatDif);
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,MatAmb);
 
  glLightfv(GL_LIGHT0, GL_DIFFUSE, Light1Dif);
  glLightfv(GL_LIGHT0, GL_SPECULAR, Light1Spec);
  glLightfv(GL_LIGHT0, GL_AMBIENT, Light1Amb);
  glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, 90);*/
 
  //glEnable(GL_LIGHTING);
  //glEnable(GL_LIGHT0);
  //glLightfv(GL_LIGHT0, GL_POSITION, Light1Pos);
  //glShadeModel(GL_FLAT);
}

void Draw(){
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0,SCREEN_WIDTH,0,SCREEN_HEIGHT,-(SCREEN_HEIGHT+1),SCREEN_HEIGHT+1);
  
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
  
//Segments :
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

//glLightfv(GL_LIGHT0, GL_POSITION, Light1Pos);
//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Light1Dir);

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
    if(pause==0)
      angleY=angleY+vitesse;
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
    case '+': if(precHorizontal<PREC_MAX) precHorizontal+=13; break;
    case '-': if(precHorizontal>PREC_MIN) precHorizontal-=13; break;
    case 'p': pause=(pause==1? 0 : 1); break;
    case 'w': wireframe=(wireframe==1? 0 : 1); break;
    case 'f': fill=(fill==1? 0 : 1); break;
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
  switch(key){
    
  }
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
  switch(key){
    
  }
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

int onPoint(int x, int y){
  for(int i=0;i<NB_PTS;i++)
    if(pts[i].x>x-5 && pts[i].x<x+5 && pts[i].y>y-5 && pts[i].y<y+5)
      return i;
  return -1;
}

void addPoint(int x, int y){
  int i=0;
  while(i<NB_PTS && pts[i].enable==1)
    i++;
  if(i<NB_PTS){
    pts[i].enable=1;
    pts[i].x=x;
    pts[i].y=y;
    undo=redo=0;
    }
}

void delPoint(int i){
  if(i<NB_PTS && i!=-1){
    while(i<NB_PTS-1){
      pts[i].enable=pts[i+1].enable;
      pts[i].x=pts[i+1].x;
      pts[i].y=pts[i+1].y;
      i++;
    }
    pts[i].enable=0;
    undo=redo=0;
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

int actPoint(){
  int nb_pts=0;  //nombre de points créés
  for(int i=0;i<NB_PTS;i++)
    if(pts[i].enable==1)
      nb_pts++;
  return nb_pts;
}

int Modele3D(int nb_pts){
  if(nb_pts>1){
    double theta=2*PI/precHorizontal;
    modele[0][0].enable=1;
    modele[0][0].x=0;  //placement sur l'axe central du premier point
    modele[0][0].y=pts[0].y-SCREEN_HEIGHT/2;
    modele[0][0].z=pts[0].z;
    for(int i=1;i<nb_pts-1;i++){  //jusqu'à l'avant dernier point
      modele[i][0].enable=1;
      modele[i][0].x=pts[i].x-SCREEN_WIDTH/4;
      modele[i][0].y=pts[i].y-SCREEN_HEIGHT/2;
      modele[i][0].z=pts[i].z;
      for(int j=1;j<=precHorizontal;j++){
        modele[i][j].enable=1;
        modele[i][j].x=cos(theta)*modele[i][j-1].x + sin(theta)*modele[i][j-1].z;
        modele[i][j].y=modele[i][j-1].y;
        modele[i][j].z=cos(theta)*modele[i][j-1].z - sin(theta)*modele[i][j-1].x;
      }
    }
    modele[nb_pts-1][0].enable=1;
    modele[nb_pts-1][0].x=0;
    modele[nb_pts-1][0].y=pts[nb_pts-1].y-SCREEN_HEIGHT/2;
    modele[nb_pts-1][0].z=pts[nb_pts-1].z;
  }
  return nb_pts;
}

void Rendu3D(int nb_pts){
  if(nb_pts>1){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
      glTranslated(3*SCREEN_WIDTH/4,SCREEN_HEIGHT/2,0);
      glRotated(angleX,1,0,0);
      glRotated(angleY,0,1,0);
      glRotated(angleZ,0,0,1);
      
//Base initiale :
      if(fill){
        glBegin(GL_TRIANGLE_FAN);
          glColor3ub(220,115,10);
          glVertex3d(modele[0][0].x,modele[0][0].y,modele[0][0].z);
          for(int i=0;i<=precHorizontal;i++){
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
	      glVertex3d(modele[i-1][j].x,modele[i-1][j].y,modele[i-1][j].z);
	      glVertex3d(modele[i][j].x,modele[i][j].y,modele[i][j].z);
	      glVertex3d(modele[i][(j+1)%precHorizontal].x,modele[i][(j+1)%precHorizontal].y,modele[i][(j+1)%precHorizontal].z);
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
        glVertex3d(modele[nb_pts-1][0].x,modele[nb_pts-1][0].y,modele[nb_pts-1][0].z);
          for(int i=0;i<=precHorizontal;i++){
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
    //glLightfv(GL_LIGHT0, GL_POSITION, Light1Pos);
    //glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Light1Dir);
  glPopMatrix();
  }
}

void menu(int option){
  switch(option){
    case 0: break; 
    case 1: break;
      case 20: wireframe=(wireframe==1? 0 : 1); break;
      case 21: fill=(fill==1? 0 : 1); break;
        case 220: if(precHorizontal<PREC_MAX) precHorizontal+=13; break;
        case 221: if(precHorizontal>PREC_MIN) precHorizontal-=13; break;
    case 3: if(actPoint()>0){
		pts[actPoint()-1].enable=0;
		undo++;
		redo--;
	      }
	      break;
    case 4: if(redo<undo){
	        pts[actPoint()].enable=1;
		undo--;
		redo++;
              }
	      break;
    case 6: pause=(pause==1? 0 : 1); break;
    case 7: for(int i=0;i<NB_PTS;i++) pts[i].enable=0; break;
    case 8: angleX=angleZ=0.0; break;
    case 9: break;
    case 10: exit(EXIT_SUCCESS); break;
  }
}

// gcc -std=c99 -Wall -lGL -lGLU -lglut -lm -otest main.c
