typedef struct Cylindre {
  Point* meridiens;
  int taille;
  Point centre;
  Vector direction;
} Cylindre;

Cylindre facettiseCylindre(int r, int h, int m, Vector v, Point p) {
  Cylindre C;
  C.direction = v;
  C.centre = p;
  Point* meridiens = (Point*) malloc(2*m*sizeof(Point));
  
  for(int i=0;i<m;i++) {
    double teta = 2*M_PI*i/m;
    meridiens[2*i] = Point(r*cos(teta), r*sin(teta), -(double)h/2); //bas
    meridiens[2*i+1] = Point(r*cos(teta), r*sin(teta), (double)h/2); //haut
  }
  
  C.meridiens = meridiens;
  C.taille = m;
  
  return C;
}

void afficheCylindre(Cylindre C) { //selon p et v
  glBegin(GL_TRIANGLE_STRIP);
  float u=1.0;
  
  for(int i=0;i<C.taille;i++) { 
    u = (u==1.0)?0.5:1.0;
    for(int j=0;j<2;j++) {
      glColor3f(u, u, u);
      glVertex3f(C.meridiens[2*i+j].getX(), C.meridiens[2*i+j].getY(), C.meridiens[2*i+j].getZ());
    }
  }
  u = (u==1.0)?0.5:1.0;
  glColor3f(u, u, u);
  glVertex3f(C.meridiens[0].getX(), C.meridiens[0].getY(), C.meridiens[0].getZ());
  glVertex3f(C.meridiens[1].getX(), C.meridiens[1].getY(), C.meridiens[1].getZ());
  
  glEnd();
  
  for(int j=0;j<2;j++) {
    glBegin(GL_POLYGON);
    for(int i=0;i<C.taille;i++) {
      u = (u==1.0)?0.5:1.0;
      glColor3f(u, u, u);
      glVertex3f(C.meridiens[2*i].getX(), C.meridiens[2*i].getY(), C.meridiens[2*i].getZ());
    }
    glEnd();
  }
  
}

typedef struct Cone {
  Point* meridiens;
  int taille;
  Point sommet;
  Vector direction;
} Cone;

Cone facettiseCone(int r, int h, int m, Vector v, Point p) {
  Cone C;
  C.direction = v;
  C.sommet = p;
  Point* meridiens = (Point*) malloc(2*m*sizeof(Point));
  
  for(int i=0;i<m;i++) {
    double teta = 2*M_PI*i/m;
    meridiens[2*i] = Point(0, 0, -(double)h/2); //bas
    meridiens[2*i+1] = Point(r*cos(teta), r*sin(teta), (double)h/2); //haut
  }
  
  C.meridiens = meridiens;
  C.taille = m;
  
  return C;
}

void afficheCone(Cone C) { //selon p et v
  glBegin(GL_TRIANGLE_STRIP);
  float u=1.0;
  
  for(int i=0;i<C.taille;i++) { 
    u = (u==1.0)?0.5:1.0;
    for(int j=0;j<2;j++) {
      glColor3f(u, u, u);
      glVertex3f(C.meridiens[2*i+j].getX(), C.meridiens[2*i+j].getY(), C.meridiens[2*i+j].getZ());
    }
  }
  u = (u==1.0)?0.5:1.0;
  glColor3f(u, u, u);
  glVertex3f(C.meridiens[0].getX(), C.meridiens[0].getY(), C.meridiens[0].getZ());
  glVertex3f(C.meridiens[1].getX(), C.meridiens[1].getY(), C.meridiens[1].getZ());
  
  glEnd();
  
  for(int j=0;j<2;j++) {
    glBegin(GL_POLYGON);
    for(int i=0;i<C.taille;i++) {
      u = (u==1.0)?0.5:1.0;
      glColor3f(u, u, u);
      glVertex3f(C.meridiens[2*i].getX(), C.meridiens[2*i].getY(), C.meridiens[2*i].getZ());
    }
    glEnd();
  }
  
}


typedef struct Sphere {
  Point* meridiens;
  int m;
  int p;
  Point centre;
} Sphere;

Sphere facettiseSphere(int r, int p, int m, Point centre) {
  Sphere C;
  C.centre = centre;
  C.p = p;
  C.m = m;
  Point* meridiens = (Point*) malloc(p*m*sizeof(Point));
  
  for(int i=0;i<m;i++) {
    double teta = 2*M_PI*i/(m-1);
    for(int j=0;j<p;j++) {
      double phi = M_PI*j/(p-1);
      meridiens[i*p+j] = Point(r*sin(phi)*cos(teta), r*sin(phi)*sin(teta), r*cos(phi));
    }
  }
  
  C.meridiens = meridiens;
  
  return C;
}

void afficheSphere(Sphere C) { //selon centre
  glColor3f(1,1,1);
  
  if(filled) {
    for(int i=0;i<C.m;i++) { 
      glBegin(GL_TRIANGLE_STRIP);
      for(int j=0;j<C.p;j++) {
	for(int k=0;k<2;k++) {
	  glVertex3f(C.meridiens[C.p*((i+k)%C.m)+j].getX(), C.meridiens[C.p*((i+k)%C.m)+j].getY(), C.meridiens[C.p*((i+k)%C.m)+j].getZ());
	}
      }
      glEnd();
    }
  }
  
  glColor3f(0.2,0.2,0.2);
  
  if(wireframe) {
    for(int i=0;i<C.m;i++) { 
      glBegin(GL_LINE_LOOP);
      for(int j=0;j<C.p;j++) {
	for(int k=0;k<2;k++) {
	  glVertex3f(C.meridiens[C.p*((i+k)%C.m)+j].getX(), C.meridiens[C.p*((i+k)%C.m)+j].getY(), C.meridiens[C.p*((i+k)%C.m)+j].getZ());
	}
	for(int k=1;k>-1;k--) {
	  glVertex3f(C.meridiens[C.p*((i+k)%C.m)+j].getX(), C.meridiens[C.p*((i+k)%C.m)+j].getY(), C.meridiens[C.p*((i+k)%C.m)+j].getZ());
	}
      }
      glEnd();
    }
  }
}

