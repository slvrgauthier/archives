void CarreauParametrique(Point* P, long imax, long jmax, long nbU) {
  Point** iterations = (Point**)malloc(sizeof(Point*)*imax*jmax);
  for(long k=0;k<imax;k++) {
    iterations[k] = (Point*)malloc(sizeof(Point)*(imax-k)*(jmax-k));
  }
  
  for(long S=0;S<nbU;S++) {
    double s = (double)S/(nbU-1);
    for(long T=0;T<nbU;T++) {
      double t = (double)S/(nbU-1);
    
      long limI = imax;
      long limJ = jmax;
      //Quand k=0, on utilise P
      for(long i=0;i<limI;i++) {
	for(long j=0;j<limJ;j++) {
          iterations[0][i*limJ+j] = Point((1-s)*((1-t)*P[i*imax+j].getX() + t*P[i*imax+j+1].getX()) + s*((1-t)*P[(i+1)*imax+j].getX() + t*P[(i+1)*imax+j+1].getX()),
	  		                  (1-s)*((1-t)*P[i*imax+j].getY() + t*P[i*imax+j+1].getY()) + s*((1-t)*P[(i+1)*imax+j].getY() + t*P[(i+1)*imax+j+1].getY()),
			                  (1-s)*((1-t)*P[i*imax+j].getZ() + t*P[i*imax+j+1].getZ()) + s*((1-t)*P[(i+1)*imax+j].getZ() + t*P[(i+1)*imax+j+1].getZ()));
	}
	limJ--;
      }
      limI--;
    
      //Caclul du reste des iterations
      for(long k=1;k<imax;k++) {
        for(long i=0;i<limI;i++) {
	  for(long j=0;j<limJ;j++) {
	    iterations[k][i*limJ+j] = Point((1-s)*((1-t)*iterations[k-1][i*limJ+j].getX() + t*iterations[k-1][i*limJ+j+1].getX()) + s*((1-t)*iterations[k-1][(i+1)*limJ+j].getX() + t*iterations[k-1][(i+1)*limJ+j+1].getX()),
	  		                    (1-s)*((1-t)*iterations[k-1][i*limJ+j].getY() + t*iterations[k-1][i*limJ+j+1].getY()) + s*((1-t)*iterations[k-1][(i+1)*limJ+j].getY() + t*iterations[k-1][(i+1)*limJ+j+1].getY()),
			                    (1-s)*((1-t)*iterations[k-1][i*limJ+j].getZ() + t*iterations[k-1][i*limJ+j+1].getZ()) + s*((1-t)*iterations[k-1][(i+1)*limJ+j].getZ() + t*iterations[k-1][(i+1)*limJ+j+1].getZ()));
          }
          limJ--;
	}
        limI--;
      }
      iterations[imax-1][0].afficher();
    }
  }
  
  for(long i=0;i<imax;i++) free(iterations[i]);
  free(iterations);
}

void SurfaceReglee(Point* Pc, Point* Qc, long nbC, long nbU, long nbV) {
  Point S[nbU][nbV];
  Point * P = BezierCurveByBernstein(Pc, nbC, nbU);
  Point * Q = BezierCurveByBernstein(Qc, nbC, nbU);
  DrawCurve(P,nbU,false);
  DrawCurve(Q,nbU,false);
  for(long u=0;u<nbU;u++) {
    for(long v=0;v<nbV;v++) {
      double coef = (double)v/(nbV-1);
      S[u][v] = Point((1-coef)*P[u].getX()+coef*Q[u].getX(),(1-coef)*P[u].getY()+coef*Q[u].getY(),(1-coef)*P[u].getZ()+coef*Q[u].getZ());
    }
  }
  for(long i=0;i<nbU-1;i++){
    for(long j=0;j<nbV-1;j++) {
      glBegin(GL_LINE_LOOP);
      glVertex3f(S[i][j].getX(),S[i][j].getY(),S[i][j].getZ());
      glVertex3f(S[i+1][j].getX(),S[i+1][j].getY(),S[i+1][j].getZ());
      glVertex3f(S[i+1][j+1].getX(),S[i+1][j+1].getY(),S[i+1][j+1].getZ());
      glEnd();
      glBegin(GL_LINE_LOOP);
      glVertex3f(S[i+1][j+1].getX(),S[i+1][j+1].getY(),S[i+1][j+1].getZ());
      glVertex3f(S[i][j+1].getX(),S[i][j+1].getY(),S[i][j+1].getZ());
      glVertex3f(S[i][j].getX(),S[i][j].getY(),S[i][j].getZ());
      glEnd();
    }
  }
}
