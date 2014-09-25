/*========================================================================
Nom: fonc.c             auteur: Gauthier Silvère
Maj:  11/4/2012         Creation: 12/3/2012
Projet: Gabarit3D
--------------------------------------------------------------------------
Specification:
Ce fichier contient les fonctions supplémentaires.
=========================================================================*/

#include "fonc.h"

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
 
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glShadeModel(GL_SMOOTH);
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

int actPoint(){
  int nb_pts=0;  //nombre de points créés
  for(int i=0;i<NB_PTS;i++)
    if(pts[i].enable==1)
      nb_pts++;
  return nb_pts;
}

void menu(int option){
  switch(option){
    case 0: break;
    
    case 1: break;
    
      case 20: wireframe=(wireframe==1? 0 : 1); break;
      case 21: fill=(fill==1? 0 : 1); break;
      case 22: light=(light==1? 0 : 1); if(light==0) glEnable(GL_LIGHTING); else glDisable(GL_LIGHTING); break;
      
        case 220: if(precHorizontal<PREC_MAX) precHorizontal+=13; break;
        case 221: if(precHorizontal>PREC_MIN) precHorizontal-=13; break;
      
        case 230: if(vitesse<VIT_MAX) vitesse+=0.1; break;
        case 231: if(vitesse>VIT_MIN) vitesse-=0.1; break;
	
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

float* Normale(int i, int j){  // 0 -> x ; 1 -> y ; 2 -> z
  float u1[3],u2[3],u3[3],u4[3];
  float n1[3],n2[3],n3[3],n4[3];
  
  if(i>0 && i<actPoint()-1){
    
    u1[0]=modele[i][j-1].x - modele[i][j].x ;
    u1[1]=modele[i][j-1].y - modele[i][j].y ;
    u1[2]=modele[i][j-1].z - modele[i][j].z ;
  
    u2[0]=modele[i+1][j].x - modele[i][j].x ;
    u2[1]=modele[i+1][j].y - modele[i][j].y ;
    u2[2]=modele[i+1][j].z - modele[i][j].z ;
  
    u3[0]=modele[i][j+1].x - modele[i][j].x ;
    u3[1]=modele[i][j+1].y - modele[i][j].y ;
    u3[2]=modele[i][j+1].z - modele[i][j].z ;
  
    u4[0]=modele[i-1][j].x - modele[i][j].x ;
    u4[1]=modele[i-1][j].y - modele[i][j].y ;
    u4[2]=modele[i-1][j].z - modele[i][j].z ;
    
    
    n1[0]=u4[1]*u1[2] - u4[2]*u1[1] ;
    n1[0]=u4[2]*u1[0] - u4[0]*u1[2] ;
    n1[0]=u4[0]*u1[1] - u4[1]*u1[0] ;
    
    n2[0]=u1[1]*u2[2] - u1[2]*u2[1] ;
    n2[0]=u1[2]*u2[0] - u1[0]*u2[2] ;
    n2[0]=u1[0]*u2[1] - u1[1]*u2[0] ;
    
    n3[0]=u2[1]*u3[2] - u2[2]*u3[1] ;
    n3[0]=u2[2]*u3[0] - u2[0]*u3[2] ;
    n3[0]=u2[0]*u3[1] - u2[1]*u3[0] ;
    
    n4[0]=u3[1]*u4[2] - u3[2]*u4[1] ;
    n4[0]=u3[2]*u4[0] - u3[0]*u4[2] ;
    n4[0]=u3[0]*u4[1] - u3[1]*u4[0] ;
    
    
    N[0]=n1[0] + n2[0] + n3[0] + n4[0] ;
    N[1]=n1[1] + n2[1] + n3[1] + n4[1] ;
    N[2]=n1[2] + n2[2] + n3[2] + n4[2] ;
    
    
    float l = sqrt( N[0]*N[0] + N[1]*N[1] + N[2]*N[2] );
    
    N[0] = N[0]/l;
    N[1] = N[1]/l;
    N[2] = N[2]/l;
  }
  return N;
}
