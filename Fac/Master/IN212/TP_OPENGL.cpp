///////////////////////////////////////////////////////////////////////////////
// Imagina
// ----------------------------------------------------------------------------
// IN - Synthèse d'images - Modélisation géométrique
// Auteur : Gilles Gesquière
// ----------------------------------------------------------------------------
// Base du TP 1
// programme permettant de créer des formes de bases.
// La forme représentée ici est un polygone blanc dessiné sur un fond rouge
///////////////////////////////////////////////////////////////////////////////  

#include <stdio.h>     
#include <stdlib.h>     
#include <math.h> 
#include <iostream>
#include <vector>

using namespace std;

/* Dans les salles de TP, vous avez généralement accès aux glut dans C:\Dev. Si ce n'est pas le cas, téléchargez les .h .lib ...
Vous pouvez ensuite y faire référence en spécifiant le chemin dans visual. Vous utiliserez alors #include <glut.h>. 
Si vous mettez glut dans le répertoire courant, on aura alors #include "glut.h" 
*/

int N = 80;
double angleY = 0.0, angleZ = 0.0, angleX = 0.0;
int pause = 0;
int wireframe = 1;
int filled = 1;
double vitesse = 0.025;
int operateur = 0;
int diedre = 30;
bool grille = false;

#include <GL/glut.h> 
#include "tp1.h"
#include "tp2.h"
#include "tp3.h"
#include "tp4.h"
#include "tp5.h"
#include "tp6.h"
#include "tp7.h"
#include "tp8.h"
#include "tp9.h"

#define REPERE false
int TP = 9;

// Définition de la taille de la fenêtre
#define WIDTH  480
#define HEIGHT 480
#define NMAX 20
#define NMIN 1
#define VIT_MIN 0.05
#define VIT_MAX 0.55

// Définition de la couleur de la fenêtre
#define RED   1
#define GREEN 0
#define BLUE  0
#define ALPHA 1


// Touche echap (Esc) permet de sortir du programme
#define KEY_ESC 27


// Entêtes de fonctions
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y); 
void visible(int vis);
void Idle();
void specdown(int key, int x, int y);

int main(int argc, char **argv) 
{  
  // initialisation  des paramètres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);

  // définition et .création de la fenêtre graphique, ainsi que son titre
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Plop le gros TP !");

  // initialisation de OpenGL et de la scène
  initGL();  
  init_scene();

  // choix des procédures de callback pour 
  // le tracé graphique
  glutDisplayFunc(&window_display);
  // le redimensionnement de la fenêtre
  glutReshapeFunc(&window_reshape);
  // la gestion des événements clavier
  glutKeyboardFunc(&window_key);
  
  glutVisibilityFunc(visible);  //visibilité : idle
  glutSpecialFunc(specdown);    //appuie sur une touche speciale

  // la boucle prinicipale de gestion des événements utilisateur
  glutMainLoop();  

  return 1;
}

// initialisation du fond de la fenêtre graphique : noir opaque
GLvoid initGL() 
{
  glClearColor(RED, GREEN, BLUE, ALPHA);   
  glClearColor(0.0 , 0.0 , 0.0 , 0.0);    
  glEnable(GL_DEPTH_TEST);
}

// Initialisation de la scene. Peut servir à stocker des variables de votre programme
// à initialiser
void init_scene()
{
}

// fonction de call-back pour l´affichage dans la fenêtre

GLvoid window_display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  // C'est l'endroit où l'on peut dessiner. On peut aussi faire appel
  // à une fonction (render_scene() ici) qui contient les informations 
  // que l'on veut dessiner
  render_scene();

  // trace la scène grapnique qui vient juste d'être définie
  glFlush();
}

// fonction de call-back pour le redimensionnement de la fenêtre

GLvoid window_reshape(GLsizei width, GLsizei height)
{  
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // ici, vous verrez pendant le cours sur les projections qu'en modifiant les valeurs, il est
  // possible de changer la taille de l'objet dans la fenêtre. Augmentez ces valeurs si l'objet est 
  // de trop grosse taille par rapport à la fenêtre.
  glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

  // toutes les transformations suivantes s´appliquent au modèle de vue 
  glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des événements clavier

GLvoid window_key(unsigned char key, int x, int y) 
{  
  switch (key) {    
  case KEY_ESC:  
    exit(1);                    
    break; 
      
  case '+': if(N<NMAX) N++; break;
    
  case '-': if(N>NMIN) N--; break;
   
  case 'p': pause=(pause==1? 0 : 1); break;
    
  case 'w': wireframe=(wireframe==1? 0 : 1); break;
    
  case 'f': filled=(filled==1? 0 : 1); break;

  case 'g': grille = !grille; break;
  
  case ')': diedre = (diedre+5 > 180)?180:diedre+5; break;
  case '(': diedre = (diedre-5 < 0)?0:diedre-5; break;
    
  case 'r': angleX=angleZ=0.0; break;

  case 38 : operateur = 0; break;
  case 233 : operateur = 1; break;
  case 34 : operateur = 2; break;
  case 39 : operateur = 3; break;
    
  default:
    printf ("La touche %d n´est pas active.\n", key);
    break;
  }     
}



//////////////////////////////////////////////////////////////////////////////////////////
// Fonction que vous allez modifier afin de dessiner
/////////////////////////////////////////////////////////////////////////////////////////
void render_scene()
{
//Définition de la couleur
 glColor3f(1.0, 1.0, 1.0);
 glRotated(angleX,1,0,0);
 glRotated(angleY,0,1,0);
 glRotated(angleZ,0,0,1);
 

  //  Nous créons ici un polygone. Nous pourrions aussi créer un triangle ou des lignes. Voir ci-dessous les parties 
  // en commentaires (il faut commenter le bloc qui ne vous intéresse pas et décommenter celui que vous voulez tester.
  if(REPERE) {
        glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINES);
		glVertex3f(0, 2, 0);
		glVertex3f(0, -2, 0);
		glVertex3f(2, 0, 0);
		glVertex3f(-2, 0, 0); 
		glVertex3f(0, 0, 2);
		glVertex3f(0, 0, -2); 
	glEnd();
  }
 // création d'un polygone
/*	glBegin(GL_POLYGON);
		glVertex3f(-1, -1, 0);
		glVertex3f(1, -1, 0);
		glVertex3f(1, 1, 0);
		glVertex3f(-1, 1, 0);
	glEnd();
*/


/*
// création d'un triangle
	glBegin(GL_TRIANGLES);
		glVertex3f(-1, -1, 0);
		glVertex3f(1, -1, 0);
		glVertex3f(1, 1, 0);
	glEnd();
*/
// Carrés	
/*	glBegin(GL_QUADS);
 		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(-1,-1,0);
 		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(-0.75,-1,0);
 		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(-0.75,-0.75,0);
 		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(-1,-0.75,0);
	glEnd();
	glBegin(GL_QUADS);
 		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(1,1,0);
 		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(0.75,1,0);
 		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(0.75,0.75,0);
 		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(1,0.75,0);
	glEnd();
	glBegin(GL_QUADS);
 		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(1,-1,0);
 		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(0.75,-1,0);
 		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(0.75,-0.75,0);
 		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(1,-0.75,0);
	glEnd();
	glBegin(GL_QUADS);
 		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(-1,1,0);
 		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(-0.75,1,0);
 		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(-0.75,0.75,0);
 		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(-1,0.75,0);
	glEnd();
*/
  switch(TP) {
	case 1: {
		// Points et Lignes (exercice 3 à rendre)
		Point p = Point(1,1,0.0);
		p.afficher();
		Vector v = Vector(2.0,3.0,1.0);
		v.afficher(0.0,0.0,0.0);
			Point p2 = p.ProjectOnLine(Point(0.0,0.0,0.0), v);
		p2.afficher();
		glColor3f(0.0,0.5,1.0);
			glBegin(GL_LINES);
			glVertex3f(p.getX(),p.getY(),p.getZ());
			glVertex3f(p2.getX(),p2.getY(),p2.getZ());
		glEnd();
		
		break;
	}
	case 2: {
		glColor3f(0.5, 0.5, 0.5);
		Point tabP[4] = {Point(-1.5,1.0,0.0),Point(-0.5,1.5,0.0),Point(0.5,0.5,0.0), Point(1.5,1.0,0.0)};
		DrawCurve(tabP, (long)4, false);

		glColor3f(1.0, 1.0, 1.0);
		Point P0 = tabP[0], P1 = tabP[3];
		Vector V0(1.0,1.0,0.0), V1(1.0,-1.0,0.0);
		V0.afficher(P0.getX(),P0.getY(),P0.getZ()); V1.afficher(P1.getX(),P1.getY(),P1.getZ());
		glColor3f(1.0, 0.0, 0.0);
		DrawCurve(HermiteCubicCurve(P0,P1,V0,V1,100),100, false);

		for(int i=0;i<4;i++) {
		tabP[i].setY(tabP[i].getY()-1);
		}
		glColor3f(0.0, 1.0, 0.0);
		DrawCurve(BezierCurveByBernstein(tabP,4,100),100, false);

		for(int i=0;i<4;i++) {
		tabP[i].setY(tabP[i].getY()-1);
		}
		
		Point* curve = BezierCurveByCasteljau(tabP,4,100);
		
		glColor3f(1.0, 1.0, 1.0);
		DrawCurve(curve,100, false);
		
		break;
	}
	case 3: {
		Point Pu[4] = {Point(-2.0,1.5,0.0),Point(-1.0,2.0,0.0),Point(0.0,1.0,0.0), Point(1.0,1.5,0.0)};
		Point Qu[4] = {Point(-1.5,0.5,0.0),Point(-0.5,1.0,0.0),Point(0.5,1.0,0.0), Point(1.5,0.5,0.0)};
		long u = 50, v = 20;
		SurfaceReglee(Pu, Qu, 4, u, v);

		Point Pu2[4] = {Point(-2.0,0.5,0.0),Point(-1.0,1.0,0.0),Point(0.0,0.0,0.0), Point(1.0,0.5,0.0)};
		Point Qu2[4] = {Point(-1.5,0.5,0.0),Point(-0.5,-1.0,0.0),Point(0.5,0.0,0.0), Point(1.5,-0.5,0.0)};
		SurfaceReglee(Pu2, Qu2, 4, u, v);
		
		break;
	}
	case 4: {
		glRotated(90,1,0,0);
		//glRotated(45,0,1,0);
		//glRotated(45,0,0,1);
		if(REPERE) {
			glColor3f(0.5, 0.5, 0.5);
			glBegin(GL_LINES);
				glVertex3f(0, 2, 0);
				glVertex3f(0, -2, 0);
				glVertex3f(2, 0, 0);
				glVertex3f(-2, 0, 0); 
				glVertex3f(0, 0, 2);
				glVertex3f(0, 0, -2); 
			glEnd();
		}
		//afficheCylindre(facettiseCylindre(1,2,10,Vector(0,0,1),Point(0,0,0)));
		//afficheCone(facettiseCone(1,2,10,Vector(0,0,1),Point(0,0,0)));
		afficheSphere(facettiseSphere(1,N,N,Point(0,0,0)));
		
		break;
	}
	case 5: {
		vector<Point> V1;
		vector<int> V2;
		V1.push_back(Point(-0.5,-0.5,0));
		V1.push_back(Point(0.5,0.5,0));
		V2.push_back(1);
		V2.push_back(1);
		afficheSphereVolume(V1,V2,N, operateur);
		afficherBoite(boite(V1,V2));
		
		break;
	}
	case 6: {
		vector<Point> sommets;
		vector<int> faces;
		switch(operateur) {
		case 0: lireOff("buddha.off",sommets,faces); break;
		case 1: lireOff("bunny.off",sommets,faces); break;
		case 2: lireOff("max.off",sommets,faces); break;
		case 3: lireOff("triceratops.off",sommets,faces); break;
		}
		glOrtho(XMIN, XMAX, YMIN, YMAX, ZMIN, ZMAX);
		afficherOff(sommets,faces);
		
		break;
	}
	case 7: {
		vector<Point> sommets;
		vector<int> faces;
		lireOff("MeshSegmentation.off",sommets,faces);
		glOrtho(XMIN, XMAX, YMIN, YMAX, ZMIN, ZMAX);
		
		vector<Triangle> maillage = maillageOff(sommets, faces);
		if(filled) {afficherMaillage(maillage);}
		afficherDiedre(maillage, diedre);
		
		break;
	}
	case 8: {
		vector<Point> sommets;
		vector<int> faces;
		lireOff("MeshSegmentation.off",sommets,faces);
		glOrtho(XMIN, XMAX, YMIN, YMAX, ZMIN, ZMAX);
		vector<Triangle> maillage = maillageOff(sommets, faces);
		afficherTR(segmentationMaillage(maillage));
		break;
	}
	case 9: {
		vector<Point> sommets;
		vector<int> faces;
		lireOff("MeshSegmentation.off",sommets,faces);
		glOrtho(XMIN, XMAX, YMIN, YMAX, ZMIN, ZMAX);
		vector<Triangle> maillage = maillageOff(sommets, faces);
		if(grille) {afficherGrille(N, min(XMIN,min(YMIN,ZMIN)), max(XMAX,max(YMAX,ZMAX)));}
		simplifierMaillage(maillage, N, min(XMIN,min(YMIN,ZMIN)), max(XMAX,max(YMAX,ZMAX)));
		afficherMaillage(maillage);
		break;
	}
  }
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
    if(pause == 0) angleY=angleY+vitesse;
  }
}

void specdown(int key, int x, int y){
  switch(key){
    case GLUT_KEY_LEFT: angleZ--; break;
    
    case GLUT_KEY_RIGHT: angleZ++; break;
    
    case GLUT_KEY_UP: angleX--; break;
    
    case GLUT_KEY_DOWN: angleX++; break;
    
    case GLUT_KEY_PAGE_DOWN: if(vitesse>VIT_MIN) vitesse-=0.1; break;
    
    case GLUT_KEY_PAGE_UP: if(vitesse<VIT_MAX) vitesse+=0.1; break;
  }
}
