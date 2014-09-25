#include <iostream>
#include <fstream>
#include "CImg.h"
using namespace std;
using namespace cimg_library;

int main(int argc, char* argv[]) {

// Lecture et stockage
	CImg<unsigned short> img;
	float voxelsize[3];
	img.load_analyze("knix.hdr", voxelsize);
	cout << "dimensions : " << img.width() << "x" << img.height() << "x" << img.depth() << endl;
	cout << "voxelsize : " << voxelsize[0] << ", " << voxelsize[1] << ", " << voxelsize[2] << endl;
	cout << "min = " << img.min() << " ; max = " << img.max() << endl;
	if(img.width() > 256 && img.height() > 256 && img.depth() > 12) {
		cout << "voxel(256x256x12) = " << img.atXYZ(256, 256, 12) <<endl;
	}

// Visualisation
	CImg<unsigned short> img2;
	img2.load_analyze("test.hdr", voxelsize);
	img2.display();

// Filtrage
	

}




// g++ -otp1 tp1.cpp -O2 -L/usr/X11R6/lib -lm -lpthread -lX11

