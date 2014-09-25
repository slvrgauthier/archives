#include <iostream>
#include "ImageBase.h"
#include <vector>

using namespace std;

typedef struct Region {
  int xmin;
  int ymin;
  int w;
  int h;
} Region;

int* cut4(int w, int h, int xmin, int ymin);
void cut4Rec(int w, int h, int xmin, int ymin, int s);
void fusion(int seuil);
void colorier(Region r, int c);

ImageBase imIn, imOut;
vector<Region> vR = vector<Region>();

void affR() {
  vector<Region>::iterator i = vR.begin();
  while(i != vR.end()) {
    cout<<"Region : x="<<(*i).xmin<<", y="<<(*i).ymin<<", w="<<(*i).w<<", h="<<(*i).h<<", c="<<(int)imOut[(*i).ymin][(*i).xmin]<<endl;
    i++;
  }
}

int main(int argc, char* argv[]) {
  
  if (argc != 2) {
    printf("Usage: ImageIn.pgm\n"); 
    return 1;
  }

  imIn.load(argv[1]);
  imOut.load(argv[1]);
  string name(argv[1]);

  int w = imIn.getWidth(), h = imIn.getHeight();

  //Image entière coupée en 4
//  cut4(w,h,0,0);
//  imOut.save((char*)(name+".r4.pgm").c_str());

  //Image coupée récursivement
//  cut4Rec(w,h,0,0,2000);
//  imOut.save((char*)(name+".r4Rec_2000.pgm").c_str());
//  fusion(5);
//  imOut.save((char*)(name+".r4Rec_2000_f5.pgm").c_str());
  cut4Rec(w,h,0,0,500);
  imOut.save((char*)(name+".r4Rec_500.pgm").c_str());
  fusion(10);
  imOut.save((char*)(name+".r4Rec_500_f10.pgm").c_str());
//  cut4Rec(w,h,0,0,200);
//  imOut.save((char*)(name+".r4Rec_200.pgm").c_str());
//  fusion(2);
//  imOut.save((char*)(name+".r4Rec_200_f2.pgm").c_str());
//  cut4Rec(w,h,0,0,100);
//  imOut.save((char*)(name+".r4Rec_100.pgm").c_str());


  return 0;
}

int* cut4(int w, int h, int xmin, int ymin) {
  int wR = w/2, hR = h/2, var[4] = {0};
  
  vector<Region>::iterator it = vR.begin();
  while(it != vR.end()) {
    if((*it).xmin == xmin && (*it).ymin == ymin) {
      vR.erase(it);
      it = vR.end();
      --it;
    }
    ++it;
  }
  Region r1, r2, r3, r4;
  r1.xmin = xmin; r2.xmin = xmin; r3.xmin = xmin+wR; r4.xmin = xmin+wR;
  r1.ymin = ymin; r2.ymin = ymin+hR; r3.ymin = ymin; r4.ymin = ymin+hR;
  r1.w = r2.w = r3.w = r4.w = wR;
  r1.h = r2.h = r3.h = r4.h = hR;
  vR.push_back(r1); vR.push_back(r2); vR.push_back(r3); vR.push_back(r4);
  
  for(int i=0;i<2;i++) {
    for(int j=0;j<2;j++) {
      long tmp = 0;
      for(int x=i*wR+xmin;x<(i+1)*wR+xmin;x++) {
        for(int y=j*hR+ymin;y<(j+1)*hR+ymin;y++) {
          tmp += imIn[y][x];
        }
      }
      tmp /= (wR*hR);
      for(int x=i*wR+xmin;x<(i+1)*wR+xmin;x++) {
        for(int y=j*hR+ymin;y<(j+1)*hR+ymin;y++) {
          var[2*i+j] += ((imIn[y][x]-tmp)*(imIn[y][x]-tmp));
          imOut[y][x] = tmp;
        }
      }
      var[2*i+j] /= (wR*hR);
      //cout << "w="<<w<<",h="<<h<<",xmin="<<xmin<<",ymin="<<ymin<<" ; "<<"v(x) ["<<i<<","<<j<<"] = "<<var[2*i+j]<<endl;
    }
  }
  
  return var;
}

void cut4Rec(int w, int h, int xmin, int ymin, int s) {
  int* var = cut4(w,h,xmin,ymin); 
  int v0=var[0], v1=var[1], v2=var[2], v3=var[3];
  if(s < v0) { cut4Rec(w/2,h/2,xmin,ymin,s); }
  if(s < v1) { cut4Rec(w/2,h/2,xmin,ymin+h/2,s); }
  if(s < v2) { cut4Rec(w/2,h/2,xmin+w/2,ymin,s); }
  if(s < v3) { cut4Rec(w/2,h/2,xmin+w/2,ymin+h/2,s); }
}

void fusion(int seuil) {
  int size = vR.size();
  
  // Affichage
  int cpt = 0;
  
  // Ensemble des sommets
  Region* X = (Region*)malloc(sizeof(Region)*size);
  vector<Region>::iterator it = vR.begin();
  int i=0, j=0;
  while(it != vR.end()) {
    X[i] = (*it);
    ++it;
    ++i;
  }
  vR.clear();
  
  // Matrice d'adjacence
  bool* RAG = (bool*)malloc(sizeof(bool)*size*size);
  for(i=0;i<size*size;++i) {
    RAG[i] = false;
  }

  // Remplissage de la matrice
  for(i=0;i<size;++i) {
    for(j=0;j<size;++j) {
      bool colorize = false;
      if(i!=j && (X[i].xmin == X[j].xmin+X[j].w || X[i].xmin+X[i].w == X[j].xmin)) {
	if(X[j].ymin < X[i].ymin+X[i].h && X[i].ymin < X[j].ymin+X[j].h) {
	  colorize = true;
	}
      }
      else if(i!=j && (X[i].ymin == X[j].ymin+X[j].h || X[i].ymin+X[i].h == X[j].ymin)) {
  	if(X[j].xmin < X[i].xmin+X[i].w && X[i].xmin < X[j].xmin+X[j].w) {
	  colorize = true;
	}
      }
      if(colorize) {
	RAG[2*i+j] = true;
      }
    }
  }
  
  // Boucle de traitement
  bool stop;
  do {
    stop = true;
    for(i=0;i<size;++i) {
      cout<<"\rItération : "<<cpt<<", "<<(cpt+1)*size<<" Régions traitées   "<<flush;
      for(j=0;j<size;++j) {
	int tmpi = imOut[X[i].ymin][X[i].xmin];
	int tmpj = imOut[X[j].ymin][X[j].xmin];
    int couleur = tmpi;
	if(RAG[2*i+j] && tmpi != tmpj && abs(tmpi - tmpj) < seuil) {
  	  colorier(X[i], couleur);
      colorier(X[j], couleur);
	  // Prendre en compte les régions composées
	  for(int k=0;k<size;k++) {
	    int tmpk = imOut[X[k].ymin][X[k].xmin];
	    if(abs(tmpk-tmpi) < seuil && (RAG[2*i+k] || RAG[2*j+k] || RAG[2*k+i] || RAG[2*k+j]) ) {
	      colorier(X[k], couleur);
	    }
	  }
	  stop = false;
	}
      }
    }
    ++cpt;
  } while(!stop);
  cout<<endl;
}

void colorier(Region r, int c) {
  for(int x=r.xmin;x<r.xmin+r.w;x++) {
    for(int y=r.ymin;y<r.ymin+r.h;y++) {
      imOut[y][x] = (char)c;
    }
  }
}
