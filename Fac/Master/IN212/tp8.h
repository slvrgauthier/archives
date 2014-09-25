class Voisins {
	public:
		int a;
		int b;
		int c;

		Voisins(int A, int B, int C) {
			a = A; b = B; c = C;
		}
};

bool TrianglesAdjacents(Triangle s, Triangle t){
  int sommet_commun=0;
  if((s.m_a.equals(t.m_a))||(s.m_a.equals(t.m_b))||(s.m_a.equals(t.m_c))){sommet_commun++;}
  if((s.m_b.equals(t.m_a))||(s.m_b.equals(t.m_b))||(s.m_b.equals(t.m_c))){sommet_commun++;}
  if((s.m_c.equals(t.m_a))||(s.m_c.equals(t.m_b))||(s.m_c.equals(t.m_c))){sommet_commun++;}
  if(sommet_commun==2){return true;}
  return false;
}

vector<Voisins> TrianglesVoisins(vector<Triangle> T){
  vector<Voisins> voisin;
  int t = T.size();
  for(int i=0;i<t;i++){
	  voisin.push_back(Voisins(-1,-1,-1));
  }
  for(int i=0;i<t;i++){
    for(int j=0;j<i;j++){
      if(TrianglesAdjacents(T[i],T[j])){
		int case_libre;
		if(voisin[i].a==-1){case_libre=0;}
		else{if(voisin[i].b==-1){case_libre=1;}
		else{case_libre=2;}}
		switch (case_libre) {
			case 0 : voisin[i].a=j; break;
			case 1 : voisin[i].b=j; break;
			case 2 : voisin[i].c=j; break;
		}
		if(voisin[j].a==-1){case_libre=0;}
		else{if(voisin[j].b==-1){case_libre=1;}
		else{case_libre=2;}}
		switch (case_libre) {
			case 0 : voisin[j].a=i; break;
			case 1 : voisin[j].b=i; break;
			case 2 : voisin[j].c=i; break;
		}
      }
    }
  }
  return voisin;
}

typedef struct TR {
	Triangle t;
	int r;
}TR;

void propagation(int r, int i, vector<Triangle>& maillage, vector<Voisins>& voisin, vector<bool>& vus, vector<TR>& regions) {
	int angle = 160;
    TR tr; tr.t = maillage[i]; tr.r = r;
	regions[i] = tr;
	if(voisin[i].a != -1 && angleDiedre(maillage[i], maillage[voisin[i].a]) > angle) {
		if(!vus[voisin[i].a]) {
			vus[voisin[i].a] = true;
			propagation(r, voisin[i].a, maillage, voisin, vus, regions);
		}
		else {
			tr.t = maillage[voisin[i].a];
			regions[voisin[i].a] = tr;
		}
	}
	if(voisin[i].b != -1 && angleDiedre(maillage[i], maillage[voisin[i].b]) > angle) {
		if(!vus[voisin[i].b]) {
			vus[voisin[i].b] = true;
			propagation(r, voisin[i].b, maillage, voisin, vus, regions);
		}
		else {
			tr.t = maillage[voisin[i].b];
			regions[voisin[i].b] = tr;
		}
	}
	if(voisin[i].c != -1 && angleDiedre(maillage[i], maillage[voisin[i].c]) > angle) {
		if(!vus[voisin[i].c]) {
			vus[voisin[i].c] = true;
			propagation(r, voisin[i].c, maillage, voisin, vus, regions);
		}
		else {
			tr.t = maillage[voisin[i].c];
			regions[voisin[i].c] = tr;
		}
	}
}

vector<TR> segmentationMaillage(vector<Triangle> maillage) {
	vector<TR> regions;
	regions.resize(maillage.size());
	vector<Voisins> voisin = TrianglesVoisins(maillage);
    vector<bool> vus;
	for(int i(0) ; i < maillage.size() ; ++i) {
		vus.push_back(false);
	}
	int currentR = 1;
	
	for(int i(0);i < maillage.size();++i) {
		if(!vus[i]) {
			vus[i] = true;
			propagation(currentR, i, maillage, voisin, vus, regions);
			currentR++;
		}
	}
	return regions;
}

void afficherTR(vector<TR> regions) {
	srand(time(NULL));
	vector<double> colors;
	int nbR = 0;
	for(int i(0) ; i<regions.size() ; i++) {
		if(regions[i].r > nbR) {
			nbR = regions[i].r;
		}
	}
	for(int i(0) ; i<3*nbR ; ++i) {
		colors.push_back(rand()%256);
	}
	for(int i(0) ; i<regions.size() ; i++) {
		glColor3f(colors[regions[i].r]/256, colors[regions[i].r+1]/256, colors[regions[i].r+2]/256);
		glBegin(GL_TRIANGLES);
		  regions[i].t.afficher();
		glEnd();
		glColor3f(0, 0, 0);
		glBegin(GL_LINE_LOOP);
		  regions[i].t.afficher();
		glEnd();
	}
}

