#include "ImageBase.h"
#include <fstream>

using namespace std;

int main (int argc, char** argv) {
	int histo[256] = {0};

	if(argc < 3) {
		printf("Usage : ImageIn.pgm HistoOut.dat\n");
		return 1;
	}
	char* name = argv[1];
	ImageBase imIn;
	imIn.load(name);

	for(int x=0;x<imIn.getWidth();x++)
		for(int y=0; y<imIn.getHeight();y++)
			histo[(int)imIn[y][x]]++;

	ofstream his(argv[2]);
	for(int i=0;i<256;i++)
		his<<histo[i]<<endl;
	his.close();

	return 0;
}
