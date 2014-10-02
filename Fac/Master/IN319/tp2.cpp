#include <iostream>
#include <fstream>
#include "CImg.h"
using namespace std;
using namespace cimg_library;

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

// Visualisation
	img.display();
}




// g++ -otp1 tp1.cpp -O2 -L/usr/X11R6/lib -lm -lpthread -lX11

