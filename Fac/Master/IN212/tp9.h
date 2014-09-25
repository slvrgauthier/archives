void simplifierMaillage(vector<Triangle>& maillage, int level, double coordMin, double coordMax) {
	double size = (coordMax-coordMin)/level;
	for(int i(0) ; i<maillage.size() ; ++i) {
		for(int p(0) ; p<3 ; ++p) {
			Point current;
			if(p==0) {current = maillage[i].m_a;}
			if(p==1) {current = maillage[i].m_b;}
			if(p==2) {current = maillage[i].m_c;}
			double x = 0, y = 0, z = 0;
			for(int c(0) ; c<level ; ++c) {
				if(current.x >= coordMin+c*size && current.x <= coordMin+(c+1)*size) x = coordMin+c*size;
				if(current.y >= coordMin+c*size && current.y <= coordMin+(c+1)*size) y = coordMin+c*size;
				if(current.z >= coordMin+c*size && current.z <= coordMin+(c+1)*size) z = coordMin+c*size;
			}
			for(int j(i) ; j<maillage.size() ; ++j) {
				if(maillage[j].m_a.x >= x && maillage[j].m_a.x <= x+size &&
					maillage[j].m_a.y >= y && maillage[j].m_a.y <= y+size &&
					maillage[j].m_a.z >= z && maillage[j].m_a.z <= z+size
				) {
					maillage[j].m_a = current;
				}
				if(maillage[j].m_b.x >= x && maillage[j].m_b.x <= x+size &&
					maillage[j].m_b.y >= y && maillage[j].m_b.y <= y+size &&
					maillage[j].m_b.z >= z && maillage[j].m_b.z <= z+size
				) {
					maillage[j].m_b = current;
				}
				if(maillage[j].m_c.x >= x && maillage[j].m_c.x <= x+size &&
					maillage[j].m_c.y >= y && maillage[j].m_c.y <= y+size &&
					maillage[j].m_c.z >= z && maillage[j].m_c.z <= z+size
				) {
					maillage[j].m_c = current;
				}	
			}
		}
	}
}

void afficherGrille(int level, double coordMin, double coordMax) {
	double size = (coordMax-coordMin)/level;
	for(int x(0) ; x<level ; ++x) {
		for(int y(0) ; y<level ; ++y) {
			for(int z(0) ; z<level ; ++z) {
				glColor3f(0.25,0.25,0.25);
				glBegin(GL_LINE_LOOP);
					glVertex3f(coordMin+(x+1)*size,coordMin+(y+1)*size,coordMin+(z+1)*size);
					glVertex3f(coordMin+x*size,coordMin+(y+1)*size,coordMin+(z+1)*size);
					glVertex3f(coordMin+x*size,coordMin+y*size,coordMin+(z+1)*size);
					glVertex3f(coordMin+(x+1)*size,coordMin+y*size,coordMin+(z+1)*size);
				glEnd();
	
				glBegin(GL_LINE_LOOP);
					glVertex3f(coordMin+(x+1)*size,coordMin+(y+1)*size,coordMin+(z+1)*size);
					glVertex3f(coordMin+x*size,coordMin+(y+1)*size,coordMin+(z+1)*size);
					glVertex3f(coordMin+x*size,coordMin+(y+1)*size,coordMin+z*size);
					glVertex3f(coordMin+(x+1)*size,coordMin+(y+1)*size,coordMin+z*size);
				glEnd();

				glBegin(GL_LINE_LOOP);
					glVertex3f(coordMin+(x+1)*size,coordMin+(y+1)*size,coordMin+(z+1)*size);
					glVertex3f(coordMin+(x+1)*size,coordMin+y*size,coordMin+(z+1)*size);
					glVertex3f(coordMin+(x+1)*size,coordMin+y*size,coordMin+z*size);
					glVertex3f(coordMin+(x+1)*size,coordMin+(y+1)*size,coordMin+z*size);
				glEnd();

				glBegin(GL_LINE_LOOP);
					glVertex3f(coordMin+x*size,coordMin+y*size,coordMin+z*size);
					glVertex3f(coordMin+(x+1)*size,coordMin+y*size,coordMin+z*size);
					glVertex3f(coordMin+(x+1)*size,coordMin+(y+1)*size,coordMin+z*size);
					glVertex3f(coordMin+x*size,coordMin+(y+1)*size,coordMin+z*size);
				glEnd();

				glBegin(GL_LINE_LOOP);
					glVertex3f(coordMin+x*size,coordMin+y*size,coordMin+z*size);
					glVertex3f(coordMin+(x+1)*size,coordMin+y*size,coordMin+z*size);
					glVertex3f(coordMin+(x+1)*size,coordMin+y*size,coordMin+(z+1)*size);
					glVertex3f(coordMin+x*size,coordMin+y*size,coordMin+(z+1)*size);
				glEnd();

				glBegin(GL_LINE_LOOP);
					glVertex3f(coordMin+x*size,coordMin+y*size,coordMin+z*size);
					glVertex3f(coordMin+x*size,coordMin+(y+1)*size,coordMin+z*size);
					glVertex3f(coordMin+x*size,coordMin+(y+1)*size,coordMin+(z+1)*size);
					glVertex3f(coordMin+x*size,coordMin+y*size,coordMin+(z+1)*size);
				glEnd();
			}
		}
	}
}

