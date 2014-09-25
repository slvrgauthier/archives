#include <iostream>
#include "ImageBase.h"

using namespace std;

ImageBase imOut;

void meanReconstruct(char* outname);
void dilateReconstuct(char* outname);
void textureReconstuct(char* outname);
void supprimerObjet(char* outname);

int main(int argc, char* argv[]) {
  
  if (argc != 3) {
    printf("Usage: ImageIn.pgm ImageOut.pgm\n"); 
    return 1;
  }
  
  string name(argv[2]);

  imOut.load(argv[1]);
  meanReconstruct((char*)(name+".meanReconstruct.pgm").c_str());
  imOut.load(argv[1]);
  dilateReconstuct((char*)(name+".dilateReconstuct.pgm").c_str());
  imOut.load(argv[1]);
  textureReconstuct((char*)(name+".textureReconstuct.pgm").c_str());
  imOut.load("in/fruit1.pgm");
  supprimerObjet("out/fruit1.supprimerObjet.pgm");

  return 0;

}

void meanReconstruct(char* outname) {
	int w = imOut.getWidth(), h = imOut.getHeight();
	for(int x=0;x<w;x++) {
		for(int y=0; y<h;y++) {
			if(imOut[y][x] < 10) {
				int tmp = 0, cpt = 0;
				for(int i(-1) ; i <= 1 ; ++i) {
					for(int j(-1) ; j <= 1 ; ++j) {
						if(x+i >= 0 && x+i < w && y+j >= 0 && y+j < h) {
							if(imOut[y+j][x+i] > 50) {
								tmp += imOut[y+j][x+i];
								cpt++;
							}
						}
					}
				}
				if(cpt != 0) {
					//plus joli avec le for
					for(int i(-1) ; i <= 1 ; ++i) {
						for(int j(-1) ; j <= 1 ; ++j) {
							if(x+i >= 0 && x+i < w && y+j >= 0 && y+j < h) {
								imOut[y+j][x+i] = (char)(tmp/cpt);
							}
						}
					}
				}
			}
		}
	}
	
	if(outname != NULL) imOut.save(outname);
}

void dilateReconstuct(char* outname) {
	int w = imOut.getWidth(), h = imOut.getHeight();
	for(int x=0;x<w;x++) {
		for(int y=0; y<h;y++) {
			if(imOut[y][x] < 10) {
				for(int i=-1;i<=1;i++) {
					for(int j=-1;j<=1;j++) {
						if( y+j >= 0 && y+j < h && x+i >= 0 && x+i < w && imOut[y+j][x+i] > imOut[y][x] ) {
							imOut[y][x] = imOut[y+j][x+i];
						}
					}
				}
			}
		}
	}
	
	if(outname != NULL) imOut.save(outname);
}

void textureReconstuct(char* outname) {
	char motif[5][5]; bool b_motif = true;
	
	int w = imOut.getWidth(), h = imOut.getHeight();
	for(int x=0;x<w;x++) {
		for(int y=0; y<h;y++) {
			if(imOut[y][x] < 10) {
				if(b_motif && x > 10 && y > 10) {
					for(int i=-5;i<0;i++) {
						for(int j=-5;j<0;j++) {
							motif[j+5][i+5] = imOut[y+j][x+i];
						}
					}
					b_motif = false;
				}
				for(int i=-1;i<=1;i++) {
					for(int j=-1;j<=1;j++) {
						if( y+j >= 0 && y+j < h && x+i >= 0 && x+i < w ) {
								imOut[y+j][x+i] = motif[(y+j)%5][(x+i)%5];
						}
					}
				}
			}
			else {
				b_motif = true;
			}
		}
	}
	
	if(outname != NULL) imOut.save(outname);
}

void supprimerObjet(char* outname) {
	int w = imOut.getWidth(), h = imOut.getHeight();
	int x=0,y=0;
	for(int y=0; y<h-10;y++) {
		for(int x=0;x<w-10;x++) {
			if(imOut[y][x] > 100) {
				imOut[y][x] = 0;/*
				int i=0,j=0;
				while(x+i < w && y+j<h) {
					int k=1;
					while(y+j-k >= 0 && imOut[y+j-k][x+i] > 100) {
							imOut[y+j-k][x+i] = 0;
							++k;
					}
					k=1;
					while(y+j+k < h && imOut[y+j+k][x+i] > 100) {
							imOut[y+j+k][x+i] = 0;
							++k;
					}
					k=1;
					while(x+i-k >= 0 && imOut[y+j][x+i-k] > 100) {
							imOut[y+j-k][x+i] = 0;
							++k;
					}
					k=1;
					while(x+i+k < w && imOut[y+j][x+i+k] > 100) {
							imOut[y+j-k][x+i] = 0;
							++k;
					}
					++j;
					++i;
				}
				x = w;
				y = h;*/
			}
		}
	}
	
	if(outname != NULL) imOut.save(outname);
	textureReconstuct(outname);
}