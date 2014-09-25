long fact(long n) { long r = 1; for(long i=2;i<=n;i++) r*=i; return r; }
double Bernstein(long i, long n, double u) { return ((double)fact(n)/(fact(i)*fact(n-i)))*pow(u,i)*pow(1.0-u,n-i); }

void DrawCurve(Point* TabPointsOfCurve, long nbPoints, bool pts) {
  glBegin(GL_LINE_STRIP);
  for(long i=0;i<nbPoints;i++) {
    glVertex3f(TabPointsOfCurve[i].getX(),TabPointsOfCurve[i].getY(),TabPointsOfCurve[i].getZ());
  }
  glEnd();
  if(pts) {
    for(long i=0;i<nbPoints;i++) {
      TabPointsOfCurve[i].afficher();
    }
  }
}

Point* HermiteCubicCurve(Point P0, Point P1, Vector V0, Vector V1, long nbU) {
  Point* curve = (Point*)malloc(nbU*sizeof(Point));
  for(long i=0;i<nbU;i++) {
    double u = (double)i/(nbU-1), u2 = pow(u,2), u3 = pow(u,3);
    double x = (2*u3-3*u2+1)*P0.getX() + (-2*u3+3*u2)*P1.getX() + (u3-2*u2+u)*V0.getX() + (u3-u2)*V1.getX();
    double y = (2*u3-3*u2+1)*P0.getY() + (-2*u3+3*u2)*P1.getY() + (u3-2*u2+u)*V0.getY() + (u3-u2)*V1.getY();
    double z = (2*u3-3*u2+1)*P0.getZ() + (-2*u3+3*u2)*P1.getZ() + (u3-2*u2+u)*V0.getZ() + (u3-u2)*V1.getZ();
    curve[i] = Point(x,y,z);
  }
  return curve;
}

Point* BezierCurveByBernstein(Point* TabControlPoint, long nbControlPoint, long nbU) {
  Point* curve = (Point*)malloc(nbU*sizeof(Point));
  for(long i=0;i<nbU;i++) {
    double u = (double)i/(nbU-1);
    double x,y,z;
    x = y = z = 0.0;
    for(long j=0;j<nbControlPoint;j++) {
      double B = Bernstein(j,nbControlPoint-1,u);
      x += B*(TabControlPoint[j].getX());
      y += B*(TabControlPoint[j].getY());
      z += B*(TabControlPoint[j].getZ());
    }
    curve[i] = Point(x,y,z);
  }
  return curve;
}

Point* BezierCurveByCasteljau(Point* TabControlPoint, long nbControlPoint, long nbU) {
  Point* curve = (Point*)malloc(nbU*sizeof(Point));
  Point** iterations = (Point**)malloc(sizeof(Point*)*(nbControlPoint-1));
  for(long k=0;k<nbControlPoint-1;k++) {
    iterations[k] = (Point*)malloc(sizeof(Point)*(nbControlPoint-1-k));
  }
  
  for(long i=0;i<nbU;i++) {
    double u = (double)i/(nbU-1);
    double x,y,z;
    
    int lim = nbControlPoint-1;
    //Quand k=0, on utilise TabControlPoint
    for(int j=0;j<lim;j++) {
      iterations[0][j] = Point((1-u)*TabControlPoint[j].getX() + u*TabControlPoint[j+1].getX(),
			       (1-u)*TabControlPoint[j].getY() + u*TabControlPoint[j+1].getY(),
			       (1-u)*TabControlPoint[j].getZ() + u*TabControlPoint[j+1].getZ());
    }
    lim--;
    
    //Caclul du reste des iterations
    for(int k=1;k<nbControlPoint-1;k++) {
      for(int j=0;j<lim;j++) {
	iterations[k][j] = Point((1-u)*iterations[k-1][j].getX() + u*iterations[k-1][j+1].getX(),
				 (1-u)*iterations[k-1][j].getY() + u*iterations[k-1][j+1].getY(),
				 (1-u)*iterations[k-1][j].getZ() + u*iterations[k-1][j+1].getZ());
      }
      lim--;
    }
    
    curve[i] = iterations[nbControlPoint-2][0];
    
    //====================
    if(true) {
      for(long k=0;k<nbControlPoint-1;k++) {
	glColor3f(0.0, u, u);
        DrawCurve(iterations[k], nbControlPoint-k-1, false);
      }
      glColor3f(0.8, 0.8, 0.8);
      DrawCurve(TabControlPoint, nbControlPoint, false);
    }
    //====================
  }
  
  for(long i=0;i<nbControlPoint-1;i++) free(iterations[i]);
  free(iterations);
  
  return curve;
}

