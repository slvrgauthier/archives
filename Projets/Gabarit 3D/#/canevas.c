//============================= Includes : ===============================
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
 
 
//============================= Variables Globales : ===============================
bool keys[256];
bool skeys[256];
float deep = -6.0f;		//profondeur
float xrot = 0.0f;		//rotation sur l'axe x
float yrot = 0.0f;		//rotation sur l'axe y
float xspeed = 0.0f;	//vitesse de rotation x
float yspeed = 0.0f;	//vitesse de rotation y
 
 
//============================= Prototypes : ===============================
void glutResize(int width, int height);
int InitGL(GLvoid);
void DrawGLScene(GLvoid);
void keydown(unsigned char key, int x, int y);
void keyup(unsigned char key, int x, int y);
void specdown(int key, int x, int y);
void specup(int key, int x, int y);


//============================= Main : ===============================
int main(int arg, char **argc)
{
	//ici, on va initialiser les propriétés de la fenetre que l'on va créer
	//commen on va afficher (le '|' permet d'utiliser plusieurs éléments dans
	//un seul argument grace au code binaire: chaque élément a le '1' dans une rangéé,
	//et avec '|' (or), plusieurs rangées auront des 1 pour avoir plusieurs fonctionnalités
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA | GLUT_MULTISAMPLE );
	//ici, on définit les coordonnées de la position de la fenetre dans l'écran
    glutInitWindowPosition( 0, 0 );
	//ici, la taille de la fenetre
    glutInitWindowSize( 800, 600 );
 
	//ici on initialize le tout par rapport aux ressources (args) et on crée la fenetre
	glutInit(&arg, argc);
	glutCreateWindow("première fenetre glut");
 
	//ici, on appelle la fonction InitGL(), que l'on va implémenter plus tard
	// et qui va contenir toutes les initialisations de l'opengl: emplacement des textures,
	//des 'lights', du 'blending' etc...
	InitGL();
 
	//ici, on dit à glut quelles fonction il devra utiliser dans la boucle principale (glutMainLoop())
	//en mettant comme argument le pointeur de la fonction écrite. Elles seront appelées dans la boucle
	//principale quand il y en aura besoin
	glutDisplayFunc(DrawGLScene);	//fonction d'affichage: c'est le code principal de votre programme
	glutReshapeFunc(glutResize);	//appelée en cas de 'resize' de la fenetre
	glutKeyboardFunc(keydown);		//appelée quand l'utilisateur appuie sur une touche normale
	glutKeyboardUpFunc(keyup);		//relache la touche normale
	glutSpecialFunc(specdown);		//appuie sur une touche spéciale (F1, flèches...)
	glutSpecialUpFunc(specup);		//relache la touche spéciale

	glutMainLoop();				//boucle du programme
 
	return 1;
}


//============================= Fonctions : ===============================
void glutResize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
      /* modify this line to change perspective values */
	gluPerspective(45.0, (float)width/(float)height, 1.0, 300.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
 
int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glMatrixMode(GL_PROJECTION);
   // Set the persepctive.  View angel 45, aspect ration 1, near plance 1
   // and the far clipping plane at 200.  The last two mean to start drawing
   // from 1 unit in front of you up to 200 units far.
   gluPerspective(45, 1.3, 0.1, 200.0);
 
   // Change to the modelview matrix.
   glMatrixMode(GL_MODELVIEW);
   glClearColor(0.0f, 0.0f, 0.0f, 0.5f);	//Cette fonction permet d'effacer
											//l'écran avec la couleur spécifiée
 
 
	return TRUE;										// Initialization Went OK
}
 
 
void DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	if (skeys[GLUT_KEY_PAGE_UP])
	{
		deep -= 0.02f;
	}
	if (skeys[GLUT_KEY_PAGE_DOWN])
	{
		deep += 0.02f;
	}
	if (skeys[GLUT_KEY_LEFT])
		yspeed -= 0.005f;
	if (skeys[GLUT_KEY_RIGHT])
		yspeed += 0.005f;
	if (skeys[GLUT_KEY_UP])
		xspeed -= 0.005f;
	if (skeys[GLUT_KEY_DOWN])
		xspeed += 0.005f;
	if (keys['r'])
	{
		xrot = 0.0f;
		yrot = 0.0f;
		xspeed = 0.0f;
		yspeed = 0.0f;
	}
 
 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();		//on 'reset' la matrice de l'écran: origine au centre de la fenetre
 
	glTranslatef( 0.0f, 0.0f, deep);		//translation (zoom)
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
 
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);	glVertex3f( 0.0f, 1.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);	glVertex3f(-1.0f,-1.0f, 1.0f);
		glColor3f(0.0f, 0.0f, 1.0f);	glVertex3f( 1.0f,-1.0f, 1.0f);
 
		glColor3f(1.0f, 0.0f, 0.0f);	glVertex3f( 0.0f, 1.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);	glVertex3f( 1.0f,-1.0f, 1.0f);
		glColor3f(0.1f, 0.1f, 0.1f);	glVertex3f( 1.0f,-1.0f,-1.0f);
 
		glColor3f(1.0f, 0.0f, 0.0f);	glVertex3f( 0.0f, 1.0f, 0.0f);
		glColor3f(0.1f, 0.1f, 0.1f);	glVertex3f( 1.0f,-1.0f,-1.0f);
		glColor3f(0.0f, 0.0f, 1.0f);	glVertex3f(-1.0f,-1.0f,-1.0f);
 
		glColor3f(1.0f, 0.0f, 0.0f);	glVertex3f( 0.0f, 1.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);	glVertex3f(-1.0f,-1.0f,-1.0f);
		glColor3f(0.0f, 1.0f, 0.0f);	glVertex3f(-1.0f,-1.0f, 1.0f);
	glEnd();
 
	glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 1.0f);	glVertex3f( 1.0f,-1.0f, 1.0f);
		glColor3f(0.1f, 0.1f, 0.1f);	glVertex3f( 1.0f,-1.0f,-1.0f);
		glColor3f(0.0f, 0.0f, 1.0f);	glVertex3f(-1.0f,-1.0f,-1.0f);
		glColor3f(0.0f, 1.0f, 0.0f);	glVertex3f(-1.0f,-1.0f, 1.0f);
	glEnd();
 
	xrot += xspeed;
	yrot += yspeed;
 
	glutSwapBuffers();		//changement des buffers
	glutPostRedisplay();	//reaffiche le plan
}
 
void keydown(unsigned char key, int x, int y)
{
	keys[key] = true;
	switch(key)
	{
	case VK_ESCAPE: exit(0); break;
	}
}
 
void keyup(unsigned char key, int x, int y)
{
	keys[key] = false;
}
 
void specdown(int key, int x, int y)
{
	skeys[key] = true;
	switch(key)
	{
	case GLUT_KEY_F1:
		glutFullScreen();
 
	}
}
 
void specup(int key, int x, int y)
{
	skeys[key] = false;
	switch(key)
	{
 
	}
}
 