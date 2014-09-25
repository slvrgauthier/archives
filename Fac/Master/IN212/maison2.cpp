///////////////////////////////////////////////////////////////////////////////
// IUT de Provence, site d'Arles                                      2003-2004
// D�partement Informatique
// 2�me ann�e
// ----------------------------------------------------------------------------
// IN - Synth�se d'images - Rendu r�aliste
// Auteur : S�bastien Thon
// ----------------------------------------------------------------------------
// Base du TP 2
// Programme permettant d'ajouter des textures � une sc�ne compos�e d'un sol,
// de maisons et d'arbres.
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "tga.h"

#ifndef M_PI
#define M_PI	3.1415926535897932384626433832795
#endif

#define KEY_ESC 27										// Code ASCII de la touche Echap

#define MAISON  1										// Code identificant la display list de la maison
#define ARBRE   2										// Code identificant la display list de l'arbre

int		SCREEN_WIDTH =640;								// Largeur de la fen�tre OpenGL
int		SCREEN_HEIGHT=480;								// Hauteur de la fen�tre OpenGl

float	xpos = 0, zpos = -50;							// Position de la cam�ra
int		angle_x = 0, angle_y = 0;						// Orientation de la cam�ra
int		mouse_x = 0, mouse_y = 0;						// Position de la souris

// Param�tres de la source de lumi�re 0 (directionnelle)
GLfloat Light0Position[]= { 4.0f, 4.0f, 2.0f, 0.0f };
GLfloat Light0Ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat Light0Diffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat Light0Specular[]= { 0.3f, 0.3f, 0.3f, 1.0f };

// Param�tres de la source de lumi�re 1 (ponctuelle)
GLfloat Light1Position[]= { 4.0f, 8.0f, 2.0f, 1.0f };
GLfloat Light1Ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat Light1Diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat Light1Specular[]= { 0.3f, 0.3f, 0.3f, 1.0f };


// Param�tres du mat�riau utilis� pour les murs
GLfloat MatAmbient_mur[] = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat MatDiffuse_mur[] = {0.9f, 0.9f, 0.9f, 1.0f};
GLfloat MatSpecular_mur[]= {0.1f, 0.1f, 0.1f, 1.0f};
GLfloat MatShininess_mur[1]={5.0f};

// Param�tres du mat�riau utilis� pour les toits
GLfloat MatAmbient_toit[] = {0.5f, 0.0f, 0.0f, 1.0f};
GLfloat MatDiffuse_toit[] = {0.9f, 0.0f, 0.0f, 1.0f};
GLfloat MatSpecular_toit[]= {0.1f, 0.1f, 0.1f, 1.0f};
GLfloat MatShininess_toit[1]={50.0f};

// Param�tres du mat�riau utilis� pour le sol
GLfloat MatAmbient_sol[] = {0.0f, 0.5f, 0.0f, 1.0f};
GLfloat MatDiffuse_sol[] = {0.0f, 0.7f, 0.0f, 1.0f};
GLfloat MatSpecular_sol[]= {0.1f, 0.1f, 0.1f, 1.0f};
GLfloat MatShininess_sol[1]={5.0f};

// Param�tres du mat�riau utilis� pour la sph�re repr�sentant une source de lumi�re
GLfloat MatAmbient_lumiere[] = {1.0f, 1.0f, 0.0f, 1.0f};
GLfloat MatDiffuse_lumiere[] = {1.0f, 1.0f, 0.0f, 1.0f};
GLfloat MatSpecular_lumiere[]= {0.9f, 0.9f, 0.9f, 1.0f};
GLfloat MatShininess_lumiere[1]={150.0f};

// Param�tres du mat�riau utilis� pour les troncs d'arbre
GLfloat MatAmbient_tronc[] = {0.5f, 0.4f, 0.2f, 1.0f};
GLfloat MatDiffuse_tronc[] = {0.9f, 0.4f, 0.2f, 1.0f};
GLfloat MatSpecular_tronc[]= {0.1f, 0.1f, 0.1f, 1.0f};
GLfloat MatShininess_tronc[1]={5.0f};

// Param�tres du mat�riau utilis� pour les feuillages d'arbres
GLfloat MatAmbient_feuilles[] = {0.0f, 0.4f, 0.0f, 1.0f};
GLfloat MatDiffuse_feuilles[] = {0.0f, 0.7f, 0.0f, 1.0f};
GLfloat MatSpecular_feuilles[]= {0.1f, 0.1f, 0.1f, 1.0f};
GLfloat MatShininess_feuilles[1]={5.0f};

// Couleur du brouillard
GLfloat fogColor[4]= {0.6f, 0.6f, 0.7f, 0.0f};


//*****************************************************************
//* A FAIRE :
//* D�clarer une constante pour le nombre de textures (5)
//*****************************************************************
const int nbText = 5;

//*****************************************************************
//* A FAIRE :
//* D�clarer une constante pour chacune des textures :
//*    - mur
//*    - fa�ade
//*    - toit
//*    - herbe
//* Ex:
//*   #define TEXT_MUR		0
//*****************************************************************
#define TEXT_MUR 0
#define TEXT_FACADE 1
#define TEXT_TOIT 2
#define TEXT_HERBE 3
#define TEXT_TEST 4

//*****************************************************************
//* A FAIRE :
//* D�clarer un tableau "textures" de GLuint ayant autant de cases
//* qu'il y a de textures (utiliser la constante d�clar�e plus haut)
//* Ce tableau servira � stocker les identificateurs donn�s par la
//* fonction glGenTextures() correspondant � chaque texture.
//*****************************************************************
GLuint textures[5];

///////////////////////////////////////////////////////////////////////////////
// Chargement d'une image et d�finition de la texture correspondante.
//-----------------------------------------------------------------------------
// Param�tres :
//    nom    (in): nom du fichier TGA � charger.
//    numero (in): identificateur (contenu dans textures[]) de la texture � charger.
//    mipmap (in): bool�en indiquant s on veut utiliser la texture en tant que
//                 mipmap (true) ou non (false).
// Retour :
//    true si la texture a �t� charg�e, false sinon.
///////////////////////////////////////////////////////////////////////////////
bool charge_texture( char *nom, GLuint indice, bool mipmap )
{
//*****************************************************************
//* A FAIRE :
//*  - Charger une image avec la fonction load_tga().
//*  - Si load_tga() retourne NULL, alors quitter la fonction
//*    en retournant false.
//*  - Utiliser glBindTexture() pour en faire la texture courante,
//*    sur laquelle porteront les op�rations suivantes.
//*  - Utiliser glTexEnvf() pour sp�cifier le mode de m�lange.
//*  - Sp�cifier le mode de bouclage.
//*  - Pour charger l'image en m�moire vid�o, tester la valeur du
//*    bool�en mipmap :
//*       + Si mipmap == false
//*           - gluBuild2DMipmaps()
//*           - Sp�cifier le mode de filtrage.
//*       + Si mipmap == true
//*           - glTexImage2D()
//*           - Sp�cifier le mode de filtrage.
//*  - Supprimer le tableau dynamique allou� par load_tga(),
//*    l'image ayant �t� recopi�e en m�moire vid�o.
//*****************************************************************
	BYTE* img;
	int width, height;
	img = load_tga(nom,&width,&height);
	if(img == NULL) { return false; }
	
	glBindTexture(GL_TEXTURE_2D,textures[indice]);
	if(mipmap) {
		glTexImage2D(GL_TEXTURE_2D,0,3,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,img);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // GL_LINEAR , GL_NEAREST
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	else {
		gluBuild2DMipmaps(GL_TEXTURE_2D,3,width,height,GL_RGB,GL_UNSIGNED_BYTE,img);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // GL_DECAL , GL_MODULATE , GL_BLEND
	
	delete[] img;
	
	return true;
}



///////////////////////////////////////////////////////////////////////////////
// Chargement des textures.
//-----------------------------------------------------------------------------
// Param�tres :
//    _
// Retour :
//    true si toutes les textures ont �t� charg�es, false sinon.
///////////////////////////////////////////////////////////////////////////////
bool charge_textures()
{
//*****************************************************************
//* A FAIRE :
//*  - appeler glGenTextures() pour demander � OpenGL de remplir
//*    le tableau "textures" avec autant d'identificateurs qu'il y
//*    a de textures.
//*  - appeler charge_texture() pour chaque texture, en fournissant
//*    comme identificateur celui plac� dans le tableau "textures",
//*    et comme nom de fichier :
//*      - mur.tga
//*      - facade.tga
//*      - toit.tga
//*      - herbe.tga
//*  - si l'un des appels � charge_texture() retourne false, alors
//*    quitter la fonction en retournant false.
//*****************************************************************
	glGenTextures(5,textures);
	bool mipmap = false;
	if(
		charge_texture("texture/mur.tga", TEXT_MUR, mipmap)
	&&  charge_texture("texture/facade.tga", TEXT_FACADE, mipmap)
	&&  charge_texture("texture/toit.tga", TEXT_TOIT, mipmap)
	&&  charge_texture("texture/herbe.tga", TEXT_HERBE, mipmap)
	&&  charge_texture("texture/test.tga", TEXT_TEST, mipmap)
	) {
		return true;
	}
	else {
		return false;
	}
}



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
	glClearColor(0.6f, 0.6f, 0.7f, 1.0f);				// Couleur servant � effacer la fen�tre (celle du brouillard)
    glShadeModel(GL_SMOOTH);							// Mod�le d'ombrage : lissage de Gouraud
	glEnable(GL_CULL_FACE);								// Ne traite pas les faces cach�es
	glEnable(GL_DEPTH_TEST);							// Active le Z-Buffer
	glDepthFunc(GL_LEQUAL);								// Fonctionnement du Z-Buffer
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Active la correction de perspective (pour ombrage, texture, ...)

	glLightfv(GL_LIGHT0, GL_AMBIENT, Light0Ambient);	// Couleur ambiante de la source de lumi�re 0 (directionnelle)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light0Diffuse);	// Couleur diffuse de la source de lumi�re 0
	glLightfv(GL_LIGHT0, GL_SPECULAR,Light0Specular);	// Couleur sp�culaire de la source de lumi�re 0
	glLightfv(GL_LIGHT0, GL_POSITION,Light0Position);	// Direction de la source de lumi�re 0
	glEnable(GL_LIGHT0);								// Activation de la source de lumi�re 0

	glLightfv(GL_LIGHT1, GL_AMBIENT, Light1Ambient);	// Couleur ambiante de la source de lumi�re 1
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Light1Diffuse);	// Couleur diffuse de la source de lumi�re 1
	glLightfv(GL_LIGHT1, GL_SPECULAR,Light1Specular);	// Couleur sp�culaire de la source de lumi�re 1
	glLightfv(GL_LIGHT1, GL_POSITION,Light1Position);	// Position de la source de lumi�re 1
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.02);	// Att�nuation de la source de lumi�re 1
	glEnable(GL_LIGHT1);								// Activation de la source de lumi�re 1

	glEnable(GL_LIGHTING);								// Activation de l'�clairage g�n�ral

	glFogi(GL_FOG_MODE, GL_LINEAR);						// Mode d'att�nuation du brouillard (lin�aire)
	glFogfv(GL_FOG_COLOR, fogColor);					// Couleur du brouillard
	glFogf(GL_FOG_START, 20.0f);						// Distance � laquelle d�bute le brouillard
	glFogf(GL_FOG_END, 80.0f);							// Distance � laquelle le brouillard est maximal
	glEnable(GL_FOG);									// Activation du brouillard
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
	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient_sol);	// Mat�riau courant
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse_sol);
	glMaterialfv(GL_FRONT, GL_SPECULAR,MatSpecular_sol);
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess_sol);

//*****************************************************************
//* A FAIRE :
//*  - Activer le mode d'utilisation de textures.
//*  - D�clarer la texture d'herbe comme texture courante avec 
//*    glBindTexture() en sp�cifiant l'identificateur de la
//*    texture :  textures[TXT_HERBE].
//*  - Associer � chaque point3D du quad suivant les coordonn�es
//*    d'un point (s,t) dans la texture, en faisant pr�c�der chaque
//*    appel � glVertex3d() par un glTexCoord2f().
//*****************************************************************
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,textures[TEXT_HERBE]);

	glNormal3f( 0.0f, 1.0f, 0.0f);						// Normale du quadrilat�re

	glBegin(GL_QUADS);									// Affichage d'un quadrilat�re
		glTexCoord2f(0,0);
		glVertex3d(-20, 0, -20);
		glTexCoord2f(0,1);
		glVertex3d(-20, 0,  20);
		glTexCoord2f(1,1);
		glVertex3d( 20, 0,  20);
		glTexCoord2f(1,0);
		glVertex3d( 20, 0, -20);
	glEnd();

//*****************************************************************
//* A FAIRE :
//*  - D�sactiver le mode d'utilisation de textures si la sc�ne
//*    doit comporter des objets non-textur�s.
//*****************************************************************
	glDisable(GL_TEXTURE_2D);
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
	glPushMatrix();										// Sauve la matrice de vue actuelle
	glTranslatef(xp, yp, zp);							// Positionne l'arbre avec une translation
	glCallList(ARBRE);									// Appelle la display list de l'arbre
	glPopMatrix();										// Restaure la matrice de vue
}



///////////////////////////////////////////////////////////////////////////////
// Affiche une sph�re � l'emplacement de la source de lumi�re ponctuelle.
//-----------------------------------------------------------------------------
// Param�tres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void affiche_soleil()
{
	// Utilise le mat�riau cr�e pour cet objet
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MatAmbient_lumiere);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MatDiffuse_lumiere);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,MatSpecular_lumiere);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess_lumiere);

	glPushMatrix();										// Sauve la matrice de vue actuelle
	glTranslatef(Light1Position[0], Light1Position[1], Light1Position[2]);	// Positionne la sph�re
	glutSolidSphere(0.5, 20, 20);						// Affiche une sph�re
	glPopMatrix();										// Restaure la matrice de vue
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
	affiche_soleil();
	affiche_sol();

	affiche_maison( -10,  0,  0, 10 );
	affiche_maison(  10,  0, -8, 80 );
	affiche_maison(   4,  0, 10, 30 );

	affiche_arbre( -9,  0,-12 );
	affiche_arbre( -11, 0, 11 );
	affiche_arbre(  12, 0,  2 );

	glutSwapBuffers();									// Affiche la sc�ne (affichage en double buffer)
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

	// On re-sp�cifie la position des sources de lumi�re avec pour qu'elles
	// soient aussi affect�es par la translation et la rotation qu'on vient
	// d'appliquer � la sc�ne.
	glLightfv(GL_LIGHT0, GL_POSITION,Light0Position);
	glLightfv(GL_LIGHT1, GL_POSITION,Light1Position);

	// Affiche la sc�ne.
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
	SCREEN_WIDTH  = width;
	SCREEN_HEIGHT = height;
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
	float speed = 1.0f;						// Vitesse de d�placement de la source de lumi�re

	switch (key)
	{
		case KEY_ESC:						// 'ECHAP' :
			exit(1);						// on quitte le programme
			break;

		case 56 :							// '8': on d�place la source de lumi�re 1
			Light1Position[2] -=speed;		// selon z-
			glutPostRedisplay();			// et on demande le r�affichage.
			break;

		case 50 :							// '2': on d�place la source de lumi�re 1
			Light1Position[2] +=speed;		// selon z+
			glutPostRedisplay();			// et on demande le r�affichage.
			break;

		case 52 :							// '4': on d�place la source de lumi�re 1
			Light1Position[0] -=speed;		// selon x-
			glutPostRedisplay();			// et on demande le r�affichage.
			break;

		case 54 :							// '6': on d�place la source de lumi�re 1
			Light1Position[0] +=speed;		// selon x+
			glutPostRedisplay();			// et on demande le r�affichage.
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
	glNewList(MAISON, GL_COMPILE);

//*****************************************************************
//* A FAIRE :
//*  - Activer le mode d'utilisation de textures.
//*****************************************************************

		// On sp�cifie comme mat�riau courant celui correspondant au mur
		glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient_mur);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse_mur);
		glMaterialfv(GL_FRONT, GL_SPECULAR,MatSpecular_mur);
		glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess_mur);

//*****************************************************************
//* A FAIRE :
//*  - D�clarer la texture de mur comme texture courante avec 
//*    glBindTexture() en sp�cifiant l'indice de la texture :
//*    textures[TXT_MUR].
//*  - Associer � chaque point3D des polygones suivants les
//*    coordonn�es d'un point (s,t) dans la texture, en faisant
//*    pr�c�der chaque appel � glVertex3d() par un glTexCoord2f().
//*****************************************************************
		glEnable(GL_TEXTURE_2D);
//		glBindTexture(GL_TEXTURE_2D,textures[TEXT_TEST]);
		glBindTexture(GL_TEXTURE_2D,textures[TEXT_MUR]);

		// Mur de face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(0,1);
			glVertex3d(-4, 0, 5);
			glTexCoord2f(1,1);
			glVertex3d( 4, 0, 5);
			glTexCoord2f(1,0);
			glVertex3d( 4, 5, 5);
			glTexCoord2f(0,0);
			glVertex3d(-4, 5, 5);
		glEnd();
		
		// Mur arri�re
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(1,1);
			glVertex3d(-4, 0, -5);
			glTexCoord2f(1,0);
			glVertex3d(-4, 5, -5);
			glTexCoord2f(0,0);
			glVertex3d( 4, 5, -5);
			glTexCoord2f(0,1);
			glVertex3d( 4, 0, -5);
		glEnd();

		// Mur droit
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(1,1);
			glVertex3d(4, 0, -5);
			glTexCoord2f(1,0);
			glVertex3d(4, 5, -5);
			glTexCoord2f(0,0);
			glVertex3d(4, 5,  5);
			glTexCoord2f(0,1);
			glVertex3d(4, 0,  5);
		glEnd();
		
		// Triangle avant
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLES);
			glTexCoord2f(0,1);
			glVertex3d(-4, 5,   5);
			glTexCoord2f(1,1);
			glVertex3d( 4, 5,   5);
			glTexCoord2f(0.5,0.5);
			glVertex3d( 0, 7.5, 5);
		glEnd();

		// Triangle arri�re
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glBegin(GL_TRIANGLES);
			glTexCoord2f(0,1);
			glVertex3d( 4, 5,   -5);
			glTexCoord2f(1,1);
			glVertex3d(-4, 5,   -5);
			glTexCoord2f(0.5,0.5);
			glVertex3d( 0, 7.5, -5);
		glEnd();

//*****************************************************************
//* A FAIRE :
//*  - D�clarer la texture de fa�ade comme texture courante avec 
//*    glBindTexture() en sp�cifiant l'indice de la texture :
//*    textures[TXT_FACADE].
//*  - Associer � chaque point3D du quad suivant les
//*    coordonn�es d'un point (s,t) dans la texture, en faisant
//*    pr�c�der chaque appel � glVertex3d() par un glTexCoord2f().
//*****************************************************************
		glBindTexture(GL_TEXTURE_2D,textures[TEXT_FACADE]);

		// Mur gauche
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(0,1);
			glVertex3d(-4, 0, -5);
			glTexCoord2f(1,1);
			glVertex3d(-4, 0,  5);
			glTexCoord2f(1,0);
			glVertex3d(-4, 5,  5);
			glTexCoord2f(0,0);
			glVertex3d(-4, 5, -5);
		glEnd();


		// On sp�cifie comme mat�riau courant celui correspondant au toit
		glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient_toit);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse_toit);
		glMaterialfv(GL_FRONT, GL_SPECULAR,MatSpecular_toit);
		glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess_toit);

//*****************************************************************
//* A FAIRE :
//*  - D�clarer la texture de toit comme texture courante avec 
//*    glBindTexture() en sp�cifiant l'indice de la texture :
//*    textures[TXT_TOIT].
//*  - Associer � chaque point3D des quads suivants les
//*    coordonn�es d'un point (s,t) dans la texture, en faisant
//*    pr�c�der chaque appel � glVertex3d() par un glTexCoord2f().
//*****************************************************************
		glBindTexture(GL_TEXTURE_2D,textures[TEXT_TOIT]);

		// Toit droit
		glNormal3f( 0.6f, 0.8f, 0.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(0,0);
			glVertex3d(0, 7.5, 5);
			glTexCoord2f(0,1);
			glVertex3d(4, 5, 5);
			glTexCoord2f(1,1);
			glVertex3d(4, 5, -5);
			glTexCoord2f(1,0);
			glVertex3d(0, 7.5, -5);
		glEnd();

		// Toit gauche
		glNormal3f( -0.6f, 0.8f, 0.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(1,0);
			glVertex3d(0, 7.5, 5);
			glTexCoord2f(0,0);
			glVertex3d(0, 7.5, -5);
			glTexCoord2f(0,1);
			glVertex3d(-4, 5, -5);
			glTexCoord2f(1,1);
			glVertex3d(-4, 5, 5);
		glEnd();

//*****************************************************************
//* A FAIRE :
//*  - D�sactiver le mode d'utilisation de textures si la sc�ne
//*    doit comporter des objets non-textur�s.
//*****************************************************************
		glDisable(GL_TEXTURE_2D);

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
	glNewList(ARBRE, GL_COMPILE);

		// On sp�cifie comme mat�riau courant celui correspondant au tronc d'arbre
		glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient_tronc);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse_tronc);
		glMaterialfv(GL_FRONT, GL_SPECULAR,MatSpecular_tronc);
		glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess_tronc);

		glPushMatrix();						// On sauve la matrice modelview
		glRotatef(270, 1,0,0);				// Un rotation destin�e � mettre dans le sens de y...
		glutSolidCone ( 1, 6, 15, 15);		// ...un c�ne
		glPopMatrix();						// On restaure la matrice modelview


		// On sp�cifie comme mat�riau courant celui correspondant au feuillage d'arbre
		glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient_feuilles);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse_feuilles);
		glMaterialfv(GL_FRONT, GL_SPECULAR,MatSpecular_feuilles);
		glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess_feuilles);

		glPushMatrix();						// On sauve la matrice modelview
		glTranslatef(0, 6, 0);				// On translate au sommet du c�ne...
		glutSolidSphere(3, 20, 20);			// ...une sph�re
		glPopMatrix();						// On restaure la matrice modelview

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
	charge_textures();						// Chargement des textures
	construit_maison();						// Cr�ation de la display list de la maison
	construit_arbre();						// Cr�ation de la display list de l'arbre
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
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Maison");

	// Intitialisation d'autres param�tres d'OpenGL
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
