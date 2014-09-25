class Triangle {
	public:
		Point m_a;
		Point m_b;
		Point m_c;

	public:
		Triangle() { m_a = m_b = m_c = Point(); }
		Triangle(const Point a, const Point b, const Point c) { m_a = a; m_b = b; m_c = c; }
		~Triangle() {};

		void afficher() { m_a.placer(); m_b.placer(); m_c.placer(); }
};

vector<Triangle> maillageCylindre(int r, int h, int m, Vector v, Point p) {
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

  vector<Triangle> maillage;
  for(int i=0;i<C.taille;i++) {
	  maillage.push_back(Triangle(C.meridiens[2*(i%C.taille)], C.meridiens[2*(i%C.taille)+1], C.meridiens[2*((i+1)%C.taille)]));
	  maillage.push_back(Triangle(C.meridiens[2*(i%C.taille)+1], C.meridiens[2*((i+1)%C.taille)], C.meridiens[2*((i+1)%C.taille)+1]));
  }
  
  Point centreFace(p.getX(),p.getY(),-(double)h/2);
  for(int i=0;i<C.taille;i++) {
	maillage.push_back(Triangle(centreFace,C.meridiens[2*(i%C.taille)],C.meridiens[2*((i+1)%C.taille)]));
  }
  centreFace = Point(p.getX(),p.getY(),(double)h/2);
  for(int i=0;i<C.taille;i++) {
	maillage.push_back(Triangle(centreFace,C.meridiens[2*(i%C.taille)+1],C.meridiens[2*((i+1)%C.taille)+1]));
  }

  return maillage;
}

vector<Triangle> maillageSphere(int r, int p, int m, Point centre) {
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
  
  vector<Triangle> maillage;
    for(int i=0;i<C.m;i++) { 
      for(int j=0;j<C.p-1;j++) {
	      maillage.push_back(Triangle(C.meridiens[C.p*(i%C.m)+j], C.meridiens[C.p*((i+1)%C.m)+j], C.meridiens[C.p*(i%C.m)+j+1]));
	      maillage.push_back(Triangle(C.meridiens[C.p*(i%C.m)+j+1], C.meridiens[C.p*((i+1)%C.m)+j], C.meridiens[C.p*((i+1)%C.m)+j+1]));
      }
    }

  return maillage;
}

void afficherMaillage(vector<Triangle> v) {
  glColor3f(1,1,1);
  if(filled) {
    glBegin(GL_TRIANGLES);
    for(int i(0) ; i < v.size() ; ++i) {
      v[i].afficher();
    }
    glEnd();
  }
  glColor3f(0.1,0.1,0.1);
  if(wireframe) {
    for(int i(0) ; i < v.size() ; ++i) {
      glBegin(GL_LINE_LOOP);
        v[i].afficher();
      glEnd();
    }
  }
}

double angleDiedre(Triangle t1, Triangle t2) {
	int communs = 0;
	if(t1.m_a.equals(t2.m_a) || t1.m_a.equals(t2.m_b) || t1.m_a.equals(t2.m_c)) {
		++communs;
	}
	if(t1.m_b.equals(t2.m_a) || t1.m_b.equals(t2.m_b) || t1.m_b.equals(t2.m_c)) {
		++communs;
	}
	if(t1.m_c.equals(t2.m_a) || t1.m_c.equals(t2.m_b) || t1.m_c.equals(t2.m_c)) {
		++communs;
	}
	if(communs < 2) {
		return -1;
	}
	
	// t = ABC
	Vector AB(t1.m_b.getX()-t1.m_a.getX(), t1.m_b.getY()-t1.m_a.getY(), t1.m_b.getZ()-t1.m_a.getZ());
	Vector AC(t1.m_c.getX()-t1.m_a.getX(), t1.m_c.getY()-t1.m_a.getY(), t1.m_c.getZ()-t1.m_a.getZ());
	Vector N1(AB.Vectoriel(AC));
	
	AB = Vector(t2.m_b.getX()-t2.m_a.getX(), t2.m_b.getY()-t2.m_a.getY(), t2.m_b.getZ()-t2.m_a.getZ());
	AC = Vector(t2.m_c.getX()-t2.m_a.getX(), t2.m_c.getY()-t2.m_a.getY(), t2.m_c.getZ()-t2.m_a.getZ());
	Vector N2(AB.Vectoriel(AC));
	
	return (M_PI-N1.Angle(N2))*180/M_PI;
}

void afficherDiedre(vector<Triangle> v, double angle) {
	glColor3f(1,0,0);
	glScalef(1.01,1.01,1.01);
	for(int i(0) ; i < v.size() ; ++i) {
		for(int j(i+1) ; j <= v.size() ; ++j) {
			Triangle t1 = v[i], t2 = v[j%v.size()];
			double tmp = angleDiedre(t1, t2);
			if(tmp > 5 && tmp < 175 && tmp < angle) {
				glBegin(GL_LINES);
				if(t1.m_a.equals(t2.m_a) || t1.m_a.equals(t2.m_b) || t1.m_a.equals(t2.m_c)) {
					t1.m_a.placer();
				}
				if(t1.m_b.equals(t2.m_a) || t1.m_b.equals(t2.m_b) || t1.m_b.equals(t2.m_c)) {
					t1.m_b.placer();
				}
				if(t1.m_c.equals(t2.m_a) || t1.m_c.equals(t2.m_b) || t1.m_c.equals(t2.m_c)) {
					t1.m_c.placer();
				}
				glEnd();
			}
		}
	}
}

vector<Triangle> maillageOff(vector<Point> sommets, vector<int> faces) {
	vector<Triangle> maillage;
	for(int i(0) ; i < faces.size() ; i+=3) {
		maillage.push_back(Triangle(sommets[faces[i]], sommets[faces[i+1]], sommets[faces[i+2]]));
	}
	return maillage;
}

