#include <fstream>

using namespace std;

double XMIN = 1000, XMAX = -1000, YMIN = 1000, YMAX = -1000, ZMIN = 1000, ZMAX = -1000;

void lireOff(const string path, vector<Point>& sommets, vector<int>& faces) {
	XMIN = YMIN = ZMIN = 1000;
	XMAX = YMAX = ZMAX = -1000;
	sommets.clear();
	faces.clear();
	
	ifstream is(path.c_str());
	string title;
	is >> title;
	if(title.compare("OFF") == 0) {
		int nbSommets, nbFaces, nbAretes;
		is >> nbSommets >> nbFaces >> nbAretes;
		
		double tmp1, tmp2, tmp3;
		for(int i(0) ; i < nbSommets ; ++i) {
			is >> tmp1 >> tmp2 >> tmp3;
			if(tmp1 > XMAX) XMAX = tmp1;
			if(tmp1 < XMIN) XMIN = tmp1;
			if(tmp2 > YMAX) YMAX = tmp2;
			if(tmp2 < YMIN) YMIN = tmp2;
			if(tmp3 > ZMAX) ZMAX = tmp3;
			if(tmp3 < ZMIN) ZMIN = tmp3;
			sommets.push_back(Point(tmp1,tmp2,tmp3));
		}
		int tmp;
		for(int i(0) ; i < nbFaces ; ++i) {
			int faceSize;
			is >> faceSize;
			for(int j(0) ; j < faceSize ; ++j) {
				is >> tmp;
				faces.push_back(tmp);
			}
		}
	}
	else {
		cout << "Une erreur est survenue lors de la lecture du fichier " << path << endl;
	}
}

void afficherOff(vector<Point> sommets, vector<int> faces) {
	if(filled) {
		glColor3f(1,1,1);
		glBegin(GL_TRIANGLES);
		for(int i(0) ; i < faces.size() ; i++) {
			sommets[faces[i]].placer();
		}
		glEnd();
	}
	if(wireframe) {
		glColor3f(0,0,0);
		for(int i(0) ; i < faces.size() ; i+=3) {
			glBegin(GL_LINE_LOOP);
				sommets[faces[i]].placer();
				sommets[faces[i+1]].placer();
				sommets[faces[i+2]].placer();
			glEnd();
		}
	}
}
