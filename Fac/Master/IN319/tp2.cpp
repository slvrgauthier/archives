#include <iostream>
#include <fstream>
#include "CImg.h"
using namespace std;
using namespace cimg_library;

CImg<unsigned short> erosion(CImg<unsigned short>* img) {
	long w = (*img).width(), h = (*img).height(), d = (*img).depth();
	CImg<unsigned short> l_img(w, h, d, 1);
	for(long x=0 ; x<w ; x++) {
		for(long y=0 ; y<h ; y++) {
			for(long z=0 ; z<d ; z++) {
				if((*img).atXYZ(x,y,z) != 0) {
					if((*img).atXYZ(x-1,y,z) == 0
					||(*img).atXYZ(x+1,y,z) == 0
					||(*img).atXYZ(x,y-1,z) == 0
					||(*img).atXYZ(x,y+1,z) == 0
					||(*img).atXYZ(x,y,z-1) == 0
					||(*img).atXYZ(x,y,z+1) == 0) {
						*(l_img.data(x,y,z)) = 0;
					}
					else {
						*(l_img.data(x,y,z)) = *((*img).data(x,y,z));
					}
				}
			}
		}
	}
	return l_img;
}

CImg<unsigned short> dilatation(CImg<unsigned short>* img) {
	long w = (*img).width(), h = (*img).height(), d = (*img).depth();
	CImg<unsigned short> l_img(w, h, d, 1);
	for(long x=0 ; x<w ; x++) {
		for(long y=0 ; y<h ; y++) {
			for(long z=0 ; z<d ; z++) {
				if((*img).atXYZ(x,y,z) == 0) {
					if((*img).atXYZ(x-1,y,z) != 0) {
						*(l_img.data(x,y,z)) = (*img).atXYZ(x-1,y,z);
					}
					else if((*img).atXYZ(x+1,y,z) != 0) {
						*(l_img.data(x,y,z)) = (*img).atXYZ(x+1,y,z);
					}
					else if((*img).atXYZ(x,y-1,z) != 0) {
						*(l_img.data(x,y,z)) = (*img).atXYZ(x,y-1,z);
					}
					else if((*img).atXYZ(x,y+1,z) != 0) {
						*(l_img.data(x,y,z)) = (*img).atXYZ(x,y+1,z);
					}
					else if((*img).atXYZ(x,y,z-1) != 0) {
						*(l_img.data(x,y,z)) = (*img).atXYZ(x,y,z-1);
					}
					else if((*img).atXYZ(x,y,z+1) != 0) {
						*(l_img.data(x,y,z)) = (*img).atXYZ(x,y,z+1);
					}
				}
				else {
					*(l_img.data(x,y,z)) = *((*img).data(x,y,z));
				}
			}
		}
	}
	return l_img;
}

CImg<unsigned short> composante(CImg<unsigned short>* img) {
	long w = (*img).width(), h = (*img).height(), d = (*img).depth();
	CImg<unsigned short> l_img(w, h, d, 1);
	CImg<long> comp(w, h, d, 1);
	long current = 1;
	
	cout<<"Initialisation des composantes (toutes différentes)"<<endl;
	for(long x=0 ; x<w ; x++) {
		for(long y=0 ; y<h ; y++) {
			for(long z=0 ; z<d ; z++) {
				if((*img).atXYZ(x,y,z) != 0) {
					*(comp.data(x,y,z)) = current;
					current++;
				}
			}
		}
	}
	
	cout<<"Fusion des composantes connexes entre elles"<<endl;
	bool stop;
	do {
		stop = true;
		for(long x=0 ; x<w ; x++) {
			for(long y=0 ; y<h ; y++) {
				for(long z=0 ; z<d ; z++) {
					if(comp.atXYZ(x,y,z) != 0) {
						if(comp.atXYZ(x-1,y,z) != 0 && comp.atXYZ(x-1,y,z) != comp.atXYZ(x,y,z)) {
							*(comp.data(x,y,z)) = comp.atXYZ(x-1,y,z);
							stop = false;
						}
						else if(comp.atXYZ(x+1,y,z) != 0 && comp.atXYZ(x+1,y,z) != comp.atXYZ(x,y,z)) {
							*(comp.data(x,y,z)) = comp.atXYZ(x+1,y,z);
							stop = false;
						}
						else if(comp.atXYZ(x,y-1,z) != 0 && comp.atXYZ(x,y-1,z) != comp.atXYZ(x,y,z)) {
							*(comp.data(x,y,z)) = comp.atXYZ(x,y-1,z);
							stop = false;
						}
						else if(comp.atXYZ(x,y+1,z) != 0 && comp.atXYZ(x,y+1,z) != comp.atXYZ(x,y,z)) {
							*(comp.data(x,y,z)) = comp.atXYZ(x,y+1,z);
							stop = false;
						}
						else if(comp.atXYZ(x,y,z-1) != 0 && comp.atXYZ(x,y,z-1) != comp.atXYZ(x,y,z)) {
							*(comp.data(x,y,z)) = comp.atXYZ(x,y,z-1);
							stop = false;
						}
						else if(comp.atXYZ(x,y,z+1) != 0 && comp.atXYZ(x,y,z+1) != comp.atXYZ(x,y,z)) {
							*(comp.data(x,y,z)) = comp.atXYZ(x,y,z+1);
							stop = false;
						}
					}
				}
			}
		}
	}while(!stop);
	
	cout<<"Comptage des composantes"<<endl;
	long nbComp = 0;
	for(long x=0 ; x<w ; x++) {
		for(long y=0 ; y<h ; y++) {
			for(long z=0 ; z<d ; z++) {
				nbComp = max(nbComp, *(comp.data(x,y,z)));
			}
		}
	}
	
	cout<<"Selection de la plus grande composante"<<endl;
	long biggestComp = 0;
	long compSize = 0;
	long maxSize = 0;
	for(long n=1 ; n<10 ; n++) {
		compSize = 0;
		for(long x=0 ; x<w ; x++) {
			for(long y=0 ; y<h ; y++) {
				for(long z=0 ; z<d ; z++) {
					if(comp.atXYZ(x,y,z) == n) {
						compSize++;
					}
				}
			}
		}
		if(compSize > maxSize) {
			biggestComp = n;
			maxSize = compSize;
		}
	}
	
	cout<<"Effacement des autres composantes"<<endl;
	for(long x=0 ; x<w ; x++) {
		for(long y=0 ; y<h ; y++) {
			for(long z=0 ; z<d ; z++) {
				if(comp.atXYZ(x,y,z) != biggestComp) {
					*(l_img.data(x,y,z)) = 0;
				}
			}
		}
	}
	return l_img;
}

//==========================================================================================
int main(int argc, char* argv[]) {

	unsigned short seuil1, seuil2;
	cout << "Seuil 1 : ";
	cin >> seuil1;
	cout << "Seuil 2 : ";
	cin >> seuil2;

// Lecture et stockage
	CImg<unsigned short> img, mask;
	float voxelsize[3];
	img.load_analyze("MR-head.Coronal.hdr", voxelsize);
	for(long x=0 ; x<img.width() ; x++) {
		for(long y=0 ; y<img.height() ; y++) {
			for(long z=0 ; z<img.depth() ; z++) {
				if(img.atXYZ(x,y,z) <= seuil1 || img.atXYZ(x,y,z) >= seuil2) {
					*(img.data(x,y,z)) = 0;
				}
			}
		}
	}

	cout<<"Erosion..."<<endl;
	img = erosion(&img);
	cout<<"Composante..."<<endl;
	img = composante(&img);
	cout<<"Dilatation..."<<endl;
	img = dilatation(&img);

// Visualisation
	img.display();
}




// g++ -otp2 tp2.cpp -O2 -L/usr/X11R6/lib -lm -lpthread -lX11

