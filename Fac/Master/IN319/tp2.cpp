#include <iostream>
#include <fstream>
#include "CImg.h"
using namespace std;
using namespace cimg_library;

void erosion(CImg<unsigned short>* img) {
	long w = (*img).width(), h = (*img).height(), d = (*img).depth();
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
						*((*img).data(x,y,z)) = 0;
					}
				}
			}
		}
	}
}
void dilatation(CImg<unsigned short>* img) {
	long w = (*img).width(), h = (*img).height(), d = (*img).depth();
	for(long x=0 ; x<w ; x++) {
		for(long y=0 ; y<h ; y++) {
			for(long z=0 ; z<d ; z++) {
				if((*img).atXYZ(x,y,z) == 0) {
					if((*img).atXYZ(x-1,y,z) != 0 && x > 0) {
						*((*img).data(x,y,z)) = (*img).atXYZ(x-1,y,z);
					}
					if((*img).atXYZ(x+1,y,z) != 0 && x < w) {
						*((*img).data(x,y,z)) = (*img).atXYZ(x+1,y,z);
					}
					if((*img).atXYZ(x,y-1,z) != 0 && y > 0) {
						*((*img).data(x,y,z)) = (*img).atXYZ(x,y-1,z);
					}
					if((*img).atXYZ(x,y+1,z) != 0 && y < h) {
						*((*img).data(x,y,z)) = (*img).atXYZ(x,y+1,z);
					}
					if((*img).atXYZ(x,y,z-1) != 0 && z > 0) {
						*((*img).data(x,y,z)) = (*img).atXYZ(x,y,z-1);
					}
					if((*img).atXYZ(x,y,z+1) != 0 && z < d) {
						*((*img).data(x,y,z)) = (*img).atXYZ(x,y,z+1);
					}
				}
			}
		}
	}

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
				else {
					//couleur ?
				}
			}
		}
	}

	erosion(&img);
	dilatation(&img);

// Visualisation
	img.display();
}




// g++ -otp1 tp1.cpp -O2 -L/usr/X11R6/lib -lm -lpthread -lX11

