///////////////////////////////////////////////////////////////////////////////
// IUT de Provence, site d'Arles                                      2003-2004
// D�partement Informatique
// 2�me ann�e
// ----------------------------------------------------------------------------
// IN - Synth�se d'images - Rendu r�aliste
// Auteur : S�bastien Thon
// ----------------------------------------------------------------------------
// Base du TP 1
// Base d'un programme permettant d'afficher une sc�ne compos�e d'un sol, de
// maisons et d'arbres. On placera des sources de lumi�re, on sp�cifiera les
// mat�riaux des diff�rents objets et on utilisera un effet de brouillard.
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h> 
#include <iostream>
using namespace std;

#define WIDTH   640										// Largeur de la fen�tre OpenGL
#define HEIGHT  480										// Hauteur de la fen�tre OpenGl

#define KEY_ESC 27										// Code ASCII de la touche Echap

#define MAISON  1										// Code identificant la display list de la maison
#define ARBRE   2										// Code identificant la display list de l'arbre

float	xpos = 0, zpos = -50;							// Position de la cam�ra
int		angle_x = 0, angle_y = 0;						// Orientation de la cam�ra
int		mouse_x = 0, mouse_y = 0;						// Position de la souris
float	xlum = 15, ylum = 10, zlum = 15;				// Position de la lumi�re
bool 	fog = false;

//*****************************************************************
//* A FAIRE :
//* D�clarer des tableaux contenant les caract�ristiques (Ambient,
//* diffus, sp�culaire) pour diff�rents mat�riaux :
//*    - sol
//*    - mur de maison
//*    - toit de maison
//*    - tronc d'arbre
//*    - feuillage d'arbre
//* Ex:
//*   GLfloat MatAmbient_sol[] = {0.0f, 0.5f, 0.0f, 1.0f};
//*   GLfloat MatDiffuse_sol[] = {0.0f, 0.7f, 0.0f, 1.0f};
//*   GLfloat MatSpecular_sol[]= {0.1f, 0.1f, 0.1f, 1.0f};
//*   GLfloat MatShininess_sol[1]={5.0f};
//*****************************************************************



///////////////////////////////////////////////////////////////////////////////
// Intitialisation de certains param�tres d'OpenGL.
//-----------------------------------------------------------------------------
// Param�tres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid initGL()
{
	glClearColor(0.0, 0.0, 0.0, 1);							// Couleur servant � effacer la fen�tre (noir)
    glShadeModel(GL_SMOOTH);							// Mod�le d'ombrage : lissage de Gouraud
	glEnable(GL_CULL_FACE);								// Ne traite pas les faces cach�es
	glEnable(GL_DEPTH_TEST);							// Active le Z-Buffer
	glDepthFunc(GL_LEQUAL);								// Mode de fonctionnement du Z-Buffer
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Active la correction de perspective (pour ombrage, texture, ...)


	//*****************************************************************
	//* A FAIRE :
	//*
	//* 1. Cr�er la source de lumi�re 0 (GL_LIGHT0) en tant que source de
	//*    lumi�re directionnelle, en pr�cisant :
	//*      - sa position
	//*      - sa couleur ambiante
	//*      - sa couleur diffuse
	//*      - sa couleur sp�culaire
	//*
	//* 2. Activer la source de lumi�re 0.
	//*
	//* 3. Activer l'�clairage g�n�ral
	//*****************************************************************
	GLfloat direction[] = { 1.0, 1.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, direction);
	GLfloat Light0Dif[4] = {1.0f, 0.2f, 0.2f, 1.0f};
	GLfloat Light0Spec[4]= {1.0f, 0.2f, 0.2f, 1.0f};
	GLfloat Light0Amb[4] = {0.5f, 0.5f, 0.5f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light0Dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Light0Spec);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Light0Amb);
	
	glEnable(GL_LIGHT0);
	glDisable(GL_LIGHT0);
	
	GLfloat Light1Dif[4] = {0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat Light1Spec[4]= {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat Light1Amb[4] = {0.2f, 0.2f, 0.2f, 1.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Light1Dif);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Light1Spec);
	glLightfv(GL_LIGHT1, GL_AMBIENT, Light1Amb);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5f);
	
	glEnable(GL_LIGHT1);
	//glDisable(GL_LIGHT1);
	
	glEnable(GL_LIGHTING);
	
	GLfloat fogColor[4]= {0.5f,0.5f,0.5f,0.5f};
	glFogf(GL_FOG_MODE, GL_EXP2); // ou GL_EXP2
	glFogf(GL_FOG_DENSITY, 0.05f); // d�faut : 1.0f
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_START, 10.0);
	glFogf(GL_FOG_END, 15.0);
	//glEnable(GL_FOG);
}



///////////////////////////////////////////////////////////////////////////////
// Affiche le sol de la sc�ne.
//-----------------------------------------------------------------------------
// Param�tres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void affiche_sol()
{
	//*****************************************************************
	//* A FAIRE :
	//* Remplacer le glColor3f() suivant par l'utilisation du mat�riau
	//* cr�e pour le sol.
	//*****************************************************************
	GLfloat MatSpec[4] = {0.1f, 1.0f, 0.1f, 1.0f};
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpec);
	GLfloat MatDiff[4] = {0.1f, 0.5f, 0.1f, 1.0f};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiff);
	GLfloat MatAmb[4] = {0.1f, 0.2f, 0.1f, 1.0f};
	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmb);
	GLfloat MatEmi[4] = {0.1f, 0.25f, 0.1f, 1.0f};
	glMaterialfv(GL_FRONT, GL_EMISSION, MatEmi);							// Couleur courante : vert

	glBegin(GL_QUADS);									// Affichage d'un quadrilat�re
		glVertex3d(-20, 0, -20);
		glVertex3d(-20, 0,  20);
		glVertex3d( 20, 0,  20);
		glVertex3d( 20, 0, -20);
	glEnd();
}



///////////////////////////////////////////////////////////////////////////////
// Affiche une maison.
//-----------------------------------------------------------------------------
// Param�tres :
//    xp,yp,zp (in) : position de la maison.
//    yr       (in) : angle de rotation (en degr�s) de la maison p/r � l'axe y.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void affiche_maison( float xp, float yp, float zp, float yr )
{
	glPushMatrix();										// Sauve la matrice de vue actuelle
	glTranslatef(xp, yp, zp);							// Positionne la maison avec une translation
	glRotatef(yr, 0,1,0);								// et une rotation
	glCallList(MAISON);									// Appelle la display list de la maison
	glPopMatrix();										// Restaure la matrice de vue
}



///////////////////////////////////////////////////////////////////////////////
// Affiche un arbre.
//-----------------------------------------------------------------------------
// Param�tres :
//    xp,yp,zp (in) : position de l'arbre.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void affiche_arbre( float xp, float yp, float zp )
{
	//*****************************************************************
	//* A FAIRE :
	//* Afficher un arbre en faisant appel � sa display list.
	//*****************************************************************
	glPushMatrix();
	glTranslatef(xp, yp, zp);
	glCallList(ARBRE);
	glPopMatrix();
}



///////////////////////////////////////////////////////////////////////////////
// Affiche les diff�rents objets de la sc�ne.
//-----------------------------------------------------------------------------
// Param�tres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void affiche_scene()
{
	affiche_sol();

	//*****************************************************************
	//* A FAIRE :
	//* Afficher quelques maisons et quelques arbres.
	//*****************************************************************
	affiche_maison( 0, 0, 0, 0 );
	affiche_maison( -10, 1, -5, 0 );
	affiche_maison( 10, -1, 5, 0 );
	affiche_arbre(10,0,-5);
	affiche_arbre(-10,0,5);
	
	glPushMatrix();
		glTranslatef(xlum,ylum,zlum);
		GLfloat position[] = { 0.0, 0.0, 0.0, 1.0 };
		glLightfv(GL_LIGHT1, GL_POSITION, position);
		GLfloat MatSpec[4] = {1.0f, 1.0f, 0.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpec);
		GLfloat MatDiff[4] = {0.8f, 0.8f, 0.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiff);
		GLfloat MatAmb[4] = {0.5f, 0.5f, 0.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmb);
		GLfloat MatEmi[4] = {0.5f, 1.0f, 0.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_EMISSION, MatEmi);			// Couleur courante : jaune
		glutSolidSphere(1,10,10); //lumiere
	glPopMatrix();
	
	glutSwapBuffers();							// Affiche la sc�ne (affichage en double buffer)
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : affichage dans la fen�tre.
//-----------------------------------------------------------------------------
// Param�tres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_display()
{
	// On efface les pixels de l'image (color buffer) et le Z-Buffer (depth buffer).
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// On initialise la matrice de vue avec la matrice identit�.
	glLoadIdentity();

	// On applique une translation et une rotation � la sc�ne pour simuler
	// un d�placement de cam�ra.
	glTranslatef(xpos,0,zpos);
	glRotatef(angle_x, 1,0,0);
	glRotatef(angle_y, 0,1,0);

	//*****************************************************************
	//* A FAIRE :
	//* Re-sp�cifier la position des sources de lumi�re avec
	//* glLightfv() pour qu'elles soient aussi affect�es par la
	//* translation et la rotation qu'on vient d'appliquer � la sc�ne.
	//*****************************************************************

	// On affiche la sc�ne.
	affiche_scene();

	// On force OpenGL � afficher avant de passer � la suite.
	glFlush();
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : redimensionnement de la fen�tre.
//-----------------------------------------------------------------------------
// Param�tres :
//    width, height (in) : nouvelles largeur et hauteur de la fen�tre.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,1000.0f);

	glMatrixMode(GL_MODELVIEW);
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : gestion des �v�nements clavier.
//-----------------------------------------------------------------------------
// Param�tres :
//    key (in) : code ascii de la touche utilis�e.
//    x,y (in) : coordonn�es de la souris.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case KEY_ESC:						// 'ECHAP' :
			exit(1);						// on quitte le programme
			break;
			
		case 'd': zlum++; glutPostRedisplay(); break;
		case 'e': zlum--; glutPostRedisplay(); break;
		case 'f': xlum++; glutPostRedisplay(); break;
		case 's': xlum--; glutPostRedisplay(); break;
		case 't': ylum++; glutPostRedisplay(); break;
		case 'g': ylum--; glutPostRedisplay(); break;
		case 'a': 
			if(fog) {
				fog=false; 
				glDisable(GL_FOG); 
				glClearColor(0.0, 0.0, 0.0, 1);
				
			} else {
				fog=true; 
				glEnable(GL_FOG);
				glClearColor(0.5, 0.5, 0.5, 1);
			} 
			glutPostRedisplay(); 
			break;
	}
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : gestion des touches speciales du clavier.
//-----------------------------------------------------------------------------
// Param�tres :
//    key (in) : code ascii de la touche utilis�e.
//    x,y (in) : coordonn�es de la souris.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_special(int key, int x, int y)
{
	float speed = 1.0f;						// Vitesse de d�placement de la cam�ra

	switch (key)
	{
		case GLUT_KEY_UP:					// Fl�che vers le haut : 
			zpos += speed;					// on d�place la cam�ra selon z-
			glutPostRedisplay();			// et on demande le r�affichage.
			break;

		case GLUT_KEY_DOWN:					// Fl�che vers le bas :
			zpos -= speed;					// on d�place la cam�ra selon z+
			glutPostRedisplay();			// et on demande le r�affichage.
			break;

		case GLUT_KEY_LEFT:					// Fl�che vers la gauche :
			xpos += speed;					// on d�place la cam�ra selon x-
			glutPostRedisplay();			// et on demande le r�affichage.
			break;

		case GLUT_KEY_RIGHT:				// Fl�che vers la droite :
			xpos -= speed;					// on d�place la cam�ra selon x+
			glutPostRedisplay();			// et on demande le r�affichage.
			break;
	}
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : gestion de clics souris.
//-----------------------------------------------------------------------------
// Param�tres :
//    button (in) : code du bouton utilis�.
//    state  (in) : �tat du bouton.
//    x,y    (in) : coordonn�es de la souris.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		mouse_x = x;
		mouse_y = y;
	}
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : gestion des d�placements de la souris.
//-----------------------------------------------------------------------------
// Param�tres :
//    x,y    (in) : coordonn�es de la souris.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_motion(int x, int y)
{
	angle_x += y - mouse_y;						// Modifie la direction de vue de la cam�ra
	angle_y += x - mouse_x;						// en fonction de la position de la souris
	mouse_x = x;
	mouse_y = y;
	glutPostRedisplay();						// Demande le r�affichage
}



///////////////////////////////////////////////////////////////////////////////
// Construit une maison dans une display-list.
//-----------------------------------------------------------------------------
// Param�tres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void construit_maison()
{
	//*****************************************************************
	//* A FAIRE :
	//* Associer une normale � chacun des polygones suivants.
	//*****************************************************************

	glNewList(MAISON, GL_COMPILE);

	//*****************************************************************
	//* A FAIRE :
	//* Remplacer le glColor3f() suivant par l'utilisation du mat�riau
	//* cr�e pour les murs (glMaterialfv()).
	//*****************************************************************
		GLfloat MatSpec[4] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpec);
		GLfloat MatDiff[4] = {0.8f, 0.8f, 0.8f, 1.0f};
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiff);
		GLfloat MatAmb[4] = {0.5f, 0.5f, 0.5f, 1.0f};
		glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmb);
		GLfloat MatEmi[4] = {0.5f, 0.5f, 0.5f, 1.0f};
		glMaterialfv(GL_FRONT, GL_EMISSION, MatEmi);			// Couleur courante : blanc

		// Mur de face
		glNormal3f(0.0f,0.0f,1.0f);
		glBegin(GL_QUADS);
			glVertex3d(-4, 0, 5);
			glVertex3d( 4, 0, 5);
			glVertex3d( 4, 5, 5);
			glVertex3d(-4, 5, 5);
		glEnd();

		// Mur arri�re
		glNormal3f(0.0f,0.0f,-1.0f);
		glBegin(GL_QUADS);
			glVertex3d(-4, 0, -5);
			glVertex3d(-4, 5, -5);
			glVertex3d( 4, 5, -5);
			glVertex3d( 4, 0, -5);
		glEnd();

		// Mur gauche
		glNormal3f(-1.0f,0.0f,0.0f);
		glBegin(GL_QUADS);
			glVertex3d(-4, 0, -5);
			glVertex3d(-4, 0,  5);
			glVertex3d(-4, 5,  5);
			glVertex3d(-4, 5, -5);
		glEnd();

		// Mur droit
		glNormal3f(1.0f,0.0f,0.0f);
		glBegin(GL_QUADS);
			glVertex3d(4, 0, -5);
			glVertex3d(4, 5, -5);
			glVertex3d(4, 5,  5);
			glVertex3d(4, 0,  5);
		glEnd();

		// Triangle avant
		glNormal3f(0.0f,0.0f,1.0f);
		glBegin(GL_TRIANGLES);
			glVertex3d(-4, 5, 5);
			glVertex3d( 4, 5, 5);
			glVertex3d( 0, 8, 5);
		glEnd();

		// Triangle arri�re
		glNormal3f(0.0f,0.0f,-1.0f);
		glBegin(GL_TRIANGLES);
			glVertex3d( 4, 5, -5);
			glVertex3d(-4, 5, -5);
			glVertex3d( 0, 8, -5);
		glEnd();

	//*****************************************************************
	//* A FAIRE :
	//* Remplacer le glColor3f() suivant par l'utilisation du mat�riau
	//* cr�e pour le toit (glMaterialfv()).
	//*****************************************************************
		GLfloat MatSpec2[4] = {1.0f, 0.0f, 0.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpec2);
		GLfloat MatDiff2[4] = {0.8f, 0.0f, 0.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiff2);
		GLfloat MatAmb2[4] = {0.5f, 0.0f, 0.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmb2);
		GLfloat MatEmi2[4] = {0.25f, 0.0f, 0.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_EMISSION, MatEmi2);			// Couleur courante : rouge

		// Toit versant droit
		glNormal3f(1.0f,1.0f,0.0f);
		glBegin(GL_QUADS);
			glVertex3d(0, 8,  5);
			glVertex3d(4, 5,  5);
			glVertex3d(4, 5, -5);
			glVertex3d(0, 8, -5);
		glEnd();

		// Toit versant gauche
		glNormal3f(-1.0f,1.0f,0.0f);
		glBegin(GL_QUADS);
			glVertex3d( 0, 8,  5);
			glVertex3d( 0, 8, -5);
			glVertex3d(-4, 5, -5);
			glVertex3d(-4, 5,  5);
		glEnd();

	glEndList();
}



///////////////////////////////////////////////////////////////////////////////
// Construit un arbre dans une display-list.
//-----------------------------------------------------------------------------
// Param�tres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void construit_arbre()
{
	//*****************************************************************
	//* A FAIRE :
	//* Cr�er dans une display list un arbre dont le tronc sera un c�ne :
	//*     glutSolidCone()
	//* et le feuillage une sph�re :
	//*     glutSolidSphere()
	//* Pr�ciser le mat�riau pour chacun de ces �l�ments.
	//*****************************************************************
	glNewList(ARBRE, GL_COMPILE);
		
		glRotatef(-90,1,0,0);
		GLfloat MatSpec[4] = {0.5f, 0.5f, 0.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpec);
		GLfloat MatDiff[4] = {0.4f, 0.4f, 0.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiff);
		GLfloat MatAmb[4] = {0.25f, 0.25f, 0.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmb);
		GLfloat MatEmi[4] = {0.25f, 0.25f, 0.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_EMISSION, MatEmi);			// Couleur courante : marron
		glutSolidCone(1.0,8.0,10,10);
		
		glRotatef(90,1,0,0);
		glTranslatef(0.0,8.0,0.0);
		GLfloat MatSpec2[4] = {0.0f, 1.0f, 0.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpec2);
		GLfloat MatDiff2[4] = {0.0f, 0.4f, 0.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiff2);
		GLfloat MatAmb2[4] = {0.0f, 0.25f, 0.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmb2);
		GLfloat MatEmi2[4] = {0.0f, 0.25f, 0.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_EMISSION, MatEmi2);			// Couleur courante : vert
		glutSolidSphere(4.0f,100,100);

	glEndList();
}



///////////////////////////////////////////////////////////////////////////////
// Initialise la sc�ne.
//-----------------------------------------------------------------------------
// Param�tres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void initialise_scene()
{
	construit_maison();
	construit_arbre();
}



///////////////////////////////////////////////////////////////////////////////
// Fonction principale du programme.
//-----------------------------------------------------------------------------
// Param�tres :
//    argc (in) : nombre d'arguments de la ligne de commande.
//    argv (in) : tableau de cha�nes de caract�res contenant les arguments.
// Retour :
//    Un entier contenant le code de retour du programme.
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	// Initialisation de param�tres de Glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Maison");

	// Intitialisation de param�tres d'OpenGL
	initGL();

	// Initialisation de la sc�ne
	initialise_scene();

	// D�claration des fonctions de call-back.
	glutDisplayFunc(&callback_display);
	glutReshapeFunc(&callback_reshape);
	glutKeyboardFunc(&callback_keyboard);
	glutSpecialFunc(&callback_special);
	glutMouseFunc(&callback_mouse);
	glutMotionFunc(&callback_motion);

	// Boucle principale de Glut.
	glutMainLoop();

	// Code de retour
	return 1;
}
