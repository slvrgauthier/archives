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
					if(((*img).atXYZ(x-1,y,z) == 0 && x > 0)
					||((*img).atXYZ(x+1,y,z) == 0 && x < w)
					||((*img).atXYZ(x,y-1,z) == 0 && y > 0)
					||((*img).atXYZ(x,y+1,z) == 0 && y < h)
					||((*img).atXYZ(x,y,z-1) == 0 && z > 0)
					||((*img).atXYZ(x,y,z+1) == 0) && z < d) {
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
					if((*img).atXYZ(x-1,y,z) != 0 && x > 0) {
						*(l_img.data(x,y,z)) = (*img).atXYZ(x-1,y,z);
					}
					else if((*img).atXYZ(x+1,y,z) != 0 && x < w) {
						*(l_img.data(x,y,z)) = (*img).atXYZ(x+1,y,z);
					}
					else if((*img).atXYZ(x,y-1,z) != 0 && y > 0) {
						*(l_img.data(x,y,z)) = (*img).atXYZ(x,y-1,z);
					}
					else if((*img).atXYZ(x,y+1,z) != 0 && y < h) {
						*(l_img.data(x,y,z)) = (*img).atXYZ(x,y+1,z);
					}
					else if((*img).atXYZ(x,y,z-1) != 0 && z > 0) {
						*(l_img.data(x,y,z)) = (*img).atXYZ(x,y,z-1);
					}
					else if((*img).atXYZ(x,y,z+1) != 0 && z < d) {
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
	for(long x=0 ; x<w ; x++) {
		for(long y=0 ; y<h ; y++) {
			for(long z=0 ; z<d ; z++) {
				*(l_img.data(x,y,z)) = 0;
			}
		}
	}
	return l_img;
}

int main(int argc, char* argv[]) {

	unsigned short seuil1, seuil2;
	cout << "Seuil 1 : ";
	cin >> seuil1;
	cout << "Seuil 2 : ";
	cin >> seuil2;

// Lecture et stockage
	CImg<unsigned short> img;
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

	img = erosion(&img);
	//img = composante(&img);
	img = dilatation(&img);

// Visualisation
	img.display();
}




// g++ -otp2 tp2.cpp -O2 -L/usr/X11R6/lib -lm -lpthread -lX11

