//g++ -otest test.cc -lSDL -lGL -lGLU
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define LARGEUR_ECRAN  800
#define HAUTEUR_ECRAN  600

void dessinerRepere(unsigned int echelle);

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetCaption("Exercice : une grue", NULL);
    SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_OPENGL);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluOrtho2D(0,LARGEUR_ECRAN,0,HAUTEUR_ECRAN);

 
    bool continuer = true;
    SDL_Event event;
    SDL_EnableKeyRepeat(10,10);

    double angle1=0,angle2=-90,longueur=100;
    
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = false;
	    case SDL_KEYDOWN:
		switch(event.key.keysym.sym)
		{
		    case SDLK_ESCAPE:
			continuer = false;
			break;
		    case SDLK_UP:
			if(longueur>100)
			  longueur--;
			break;
		    case SDLK_DOWN:
			if(longueur<250)
			  longueur++;
			break;
		    case SDLK_RIGHT:
			if(angle1>-80){
			  angle1--;
			  angle2+=0.5;
			}
			break;
		    case SDLK_LEFT:
			if(angle1<0){
			  angle1++;
			  angle2-=0.5;
			}
			break;
		}
		break;
        }
 
        glClear(GL_COLOR_BUFFER_BIT);
//Base :
	glPushMatrix();
	glTranslated(50,50,0);
	glBegin(GL_QUADS);
            glColor3ub(255,50,0);
            glVertex2d(0,0);
            glVertex2d(0,50);
            glVertex2d(150,50);
            glVertex2d(150,0);
	glEnd();
//Grand Bras :
	glTranslated(75,50,0);
	glRotated(angle1,0,0,1);
	glBegin(GL_QUADS);
	    glColor3ub(150,100,0);
	    glVertex2d(20,0);
	    glVertex2d(-20,0);
	    glVertex2d(-20,450);
	    glVertex2d(20,450);
	glEnd();
//Petit Bras :
	glTranslated(0,450,0);
	glRotated(angle2,0,0,1);
	glBegin(GL_QUADS);
	    glColor3ub(50,150,0);
	    glVertex2d(-10,0);
	    glVertex2d(10,0);
	    glVertex2d(10,150);
	    glVertex2d(-10,150);
	glEnd();
//Fil :
	glTranslated(0,150,0);
	glRotated(180-(angle1+angle2),0,0,1);
	glBegin(GL_QUADS);
	    glColor3ub(255,255,255);
	    glVertex2d(-1,0);
	    glVertex2d(1,0);
	    glVertex2d(1,longueur);
	    glVertex2d(-1,longueur);
	glEnd();
//Caisse :
	glTranslated(0,longueur,0);
	glBegin(GL_QUADS);
	    glColor3ub(0,200,0);
	    glVertex2d(-10,0);
	    glVertex2d(10,0);
	    glVertex2d(10,20);
	    glVertex2d(-10,20);
	glEnd();
	glPopMatrix();
	
	
        glFlush();
        SDL_GL_SwapBuffers();
    }
    SDL_Quit();
 
    return 0;
}

void dessinerRepere(unsigned int echelle = 1)
{
    glPushMatrix();
    glScalef(echelle,echelle,echelle);
    glBegin(GL_LINES);
    glColor3ub(0,0,255);
    glVertex2i(0,0);
    glVertex2i(1,0);
    glColor3ub(0,255,0);
    glVertex2i(0,0);
    glVertex2i(0,1);
    glEnd();
    glPopMatrix();
}
