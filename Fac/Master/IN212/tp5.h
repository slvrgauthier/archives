typedef struct SphereVolume {
  int rayon;
  Point centre;
} SphereVolume;

bool dansSphere(SphereVolume C, double xi, double xi1, double yi, double yi1, double zi, double zi1) {
  double x = C.centre.getX();
  double y = C.centre.getY();
  double z = C.centre.getZ();
  double r2 = pow(C.rayon,2);
  return (pow(xi-x,2)+pow(yi-y,2)+pow(zi-z,2) <= r2 && pow(xi-x,2)+pow(yi-y,2)+pow(zi1-z,2) <= r2 && pow(xi-x,2)+pow(yi1-y,2)+pow(zi-z,2) <= r2 && pow(xi-x,2)+pow(yi1-y,2)+pow(zi1-z,2) <= r2 && pow(xi1-x,2)+pow(yi-y,2)+pow(zi-z,2) <= r2 && pow(xi1-x,2)+pow(yi-y,2)+pow(zi1-z,2) <= r2 && pow(xi1-x,2)+pow(yi1-y,2)+pow(zi-z,2) <= r2 && pow(xi1-x,2)+pow(yi1-y,2)+pow(zi1-z,2) <= r2);
             
}

bool intersection(vector<SphereVolume> V, double xi, double xi1, double yi, double yi1, double zi, double zi1) {
  for(int i(0);i<V.size();++i) {
    if(!(dansSphere(V[i],xi,xi1,yi,yi1,zi,zi1))) {
      return false;
    }
  }
  return true;
}

bool unio(vector<SphereVolume> V, double xi, double xi1, double yi, double yi1, double zi, double zi1) {
  for(int i(0);i<V.size();++i) {
    if(dansSphere(V[i],xi,xi1,yi,yi1,zi,zi1)) {
      return true;
    }
  }
  return false;
}

bool difference(vector<SphereVolume> V, double xi, double xi1, double yi, double yi1, double zi, double zi1) {
  bool result = false;
  for(int i(0);i<V.size();i+=2) {
    if(dansSphere(V[i],xi,xi1,yi,yi1,zi,zi1)) {
      result = true;
    }
  }
  for(int i(1);i<V.size();i+=2) {
    if(dansSphere(V[i],xi,xi1,yi,yi1,zi,zi1)) {
      result = false;
    }
  }
  return result;
}

void afficheSphereVolume(vector<SphereVolume> V, int div, int OPERATOR) { // 0:aucun, 1:intersection, 2:union, 3:différence
  for(int i(0);i<V.size();++i) {
    SphereVolume C = V[i];
    for(int x(0);x<(div-1);++x) {
      double xi = C.centre.getX() + C.rayon*(2*(double)x/(div-1)-1);
      double xi1 = C.centre.getX() + C.rayon*(2*(double)(x+1)/(div-1)-1);

      for(int y(0);y<(div-1);++y) {
        double yi = C.centre.getY() + C.rayon*(2*(double)y/(div-1)-1);
        double yi1 = C.centre.getY() + C.rayon*(2*(double)(y+1)/(div-1)-1);

        for(int z(0);z<(div-1);++z) {
          double zi = C.centre.getZ() + C.rayon*(2*(double)z/(div-1)-1);
          double zi1 = C.centre.getZ() + C.rayon*(2*(double)(z+1)/(div-1)-1);
         
          bool draw = false;
          if(OPERATOR == 0) { draw = dansSphere(C,xi,xi1,yi,yi1,zi,zi1); }
          if(OPERATOR == 1) { draw = intersection(V,xi,xi1,yi,yi1,zi,zi1); }
          if(OPERATOR == 2) { draw = unio(V,xi,xi1,yi,yi1,zi,zi1); }
          if(OPERATOR == 3) { draw = difference(V,xi,xi1,yi,yi1,zi,zi1); }

          if(draw) {
            if(filled) {
              glColor3f(1,1,1);
              glBegin(GL_QUADS);
                glVertex3f(xi,yi,zi); //face
                glVertex3f(xi1,yi,zi);
                glVertex3f(xi1,yi1,zi);
                glVertex3f(xi,yi1,zi);

                glVertex3f(xi,yi,zi); //gauche
                glVertex3f(xi,yi1,zi);
                glVertex3f(xi,yi1,zi1);
                glVertex3f(xi,yi,zi1);

                glVertex3f(xi1,yi,zi); //droite
                glVertex3f(xi1,yi1,zi);
                glVertex3f(xi1,yi1,zi1);
                glVertex3f(xi1,yi,zi1);

                glVertex3f(xi,yi,zi1); //fond
                glVertex3f(xi1,yi,zi1);
                glVertex3f(xi1,yi1,zi1);
                glVertex3f(xi,yi1,zi1);

                glVertex3f(xi,yi,zi); //bas
                glVertex3f(xi1,yi,zi);
                glVertex3f(xi1,yi,zi1);
                glVertex3f(xi,yi,zi1);

                glVertex3f(xi,yi1,zi); //haut
                glVertex3f(xi1,yi1,zi);
                glVertex3f(xi1,yi1,zi1);
                glVertex3f(xi,yi1,zi1);
              glEnd();
            }
            if(wireframe) {
              glColor3f(0.25,0.25,0.25);
              glBegin(GL_LINE_LOOP);
                glVertex3f(xi,yi,zi); //face
                glVertex3f(xi1,yi,zi);
                glVertex3f(xi1,yi1,zi);
                glVertex3f(xi,yi1,zi);
              glEnd();
  
              glBegin(GL_LINE_LOOP);
                glVertex3f(xi,yi,zi); //gauche
                glVertex3f(xi,yi1,zi);
                glVertex3f(xi,yi1,zi1);
                glVertex3f(xi,yi,zi1);
              glEnd();
  
              glBegin(GL_LINE_LOOP);
                glVertex3f(xi1,yi,zi); //droite
                glVertex3f(xi1,yi1,zi);
                glVertex3f(xi1,yi1,zi1);
                glVertex3f(xi1,yi,zi1);
              glEnd();

              glBegin(GL_LINE_LOOP);
                glVertex3f(xi,yi,zi1); //fond
                glVertex3f(xi1,yi,zi1);
                glVertex3f(xi1,yi1,zi1);
                glVertex3f(xi,yi1,zi1);
              glEnd();

              glBegin(GL_LINE_LOOP);
                glVertex3f(xi,yi,zi); //bas
                glVertex3f(xi1,yi,zi);
                glVertex3f(xi1,yi,zi1);
                glVertex3f(xi,yi,zi1);
              glEnd();
  
              glBegin(GL_LINE_LOOP);
                glVertex3f(xi,yi1,zi); //haut
                glVertex3f(xi1,yi1,zi);
                glVertex3f(xi1,yi1,zi1);
                glVertex3f(xi,yi1,zi1);
              glEnd();
            }
          }
        }
      }
    }
  }
}

void afficheSphereVolume(vector<Point> centres, vector<int> rayons, int div, int OPERATOR) {
  vector<SphereVolume> V;
  for(int i(0);i<centres.size();++i) {
    SphereVolume C;
    C.centre = centres[i];
    C.rayon = rayons[i];
    V.push_back(C);
  }    
  afficheSphereVolume(V,div,OPERATOR);
}

vector<Point> boite(vector<SphereVolume> V) {
  vector<Point> B;
  double xi(0), xi1(0), yi(0), yi1(0), zi(0), zi1(0);
  for(int i(0);i<V.size();++i) {
    xi = min(xi,V[i].centre.getX()-V[i].rayon);
    xi1 = max(xi1,V[i].centre.getX()+V[i].rayon);
    yi = min(yi,V[i].centre.getY()-V[i].rayon);
    yi1 = max(yi1,V[i].centre.getY()+V[i].rayon);
    zi = min(zi,V[i].centre.getZ()-V[i].rayon);
    zi1 = max(zi1,V[i].centre.getZ()+V[i].rayon);
  }
  B.push_back(Point(xi,yi,zi));
  B.push_back(Point(xi,yi,zi1));
  B.push_back(Point(xi,yi1,zi));
  B.push_back(Point(xi,yi1,zi1));
  B.push_back(Point(xi1,yi,zi));
  B.push_back(Point(xi1,yi,zi1));
  B.push_back(Point(xi1,yi1,zi));
  B.push_back(Point(xi1,yi1,zi1));
  return B;
}

vector<Point> boite(vector<Point> centres, vector<int> rayons) {
  vector<SphereVolume> V;
  for(int i(0);i<centres.size();++i) {
    SphereVolume C;
    C.centre = centres[i];
    C.rayon = rayons[i];
    V.push_back(C);
  }    
  return boite(V);
}

void afficherBoite(vector<Point> B) {
  glColor3f(0.5,0.5,0.5);
  double xi=B[0].getX(), yi=B[0].getY(), zi=B[0].getZ();
  double xi1=B[7].getX(), yi1=B[7].getY(), zi1=B[7].getZ();
  glBegin(GL_LINE_LOOP);
    glVertex3f(xi,yi,zi); //face
    glVertex3f(xi1,yi,zi);
    glVertex3f(xi1,yi1,zi);
    glVertex3f(xi,yi1,zi);
  glEnd();
  
  glBegin(GL_LINE_LOOP);
    glVertex3f(xi,yi,zi); //gauche
    glVertex3f(xi,yi1,zi);
    glVertex3f(xi,yi1,zi1);
    glVertex3f(xi,yi,zi1);
  glEnd();
  
  glBegin(GL_LINE_LOOP);
    glVertex3f(xi1,yi,zi); //droite
    glVertex3f(xi1,yi1,zi);
    glVertex3f(xi1,yi1,zi1);
    glVertex3f(xi1,yi,zi1);
  glEnd();

  glBegin(GL_LINE_LOOP);
    glVertex3f(xi,yi,zi1); //fond
    glVertex3f(xi1,yi,zi1);
    glVertex3f(xi1,yi1,zi1);
    glVertex3f(xi,yi1,zi1);
  glEnd();

  glBegin(GL_LINE_LOOP);
    glVertex3f(xi,yi,zi); //bas
    glVertex3f(xi1,yi,zi);
    glVertex3f(xi1,yi,zi1);
    glVertex3f(xi,yi,zi1);
  glEnd();
  
  glBegin(GL_LINE_LOOP);
    glVertex3f(xi,yi1,zi); //haut
    glVertex3f(xi1,yi1,zi);
    glVertex3f(xi1,yi1,zi1);
    glVertex3f(xi,yi1,zi1);
  glEnd();
}
