#include "ImageBase.h"
#include <fstream>

using namespace std;

int main (int argc, char** argv) {
	int histoR[256] = {0};
	int histoG[256] = {0};
	int histoB[256] = {0};

	if(argc < 2) {
		printf("Usage : ImageIn.ppm\n");
		return 1;
	}
	char* name = argv[1];
	ImageBase imIn;
	imIn.load(name);
	
	ImageBase planR = *(imIn.getPlan(imIn.PLAN_R));
	ImageBase planG = *(imIn.getPlan(imIn.PLAN_G));
	ImageBase planB = *(imIn.getPlan(imIn.PLAN_B));

	for(int x=0;x<imIn.getWidth();x+=3) {
		for(int y=0; y<imIn.getHeight();y++) {
			histoR[(int)planR[y][x]]++;
			histoG[(int)planG[y][x]]++;
			histoB[(int)planB[y][x]]++;
		}
	}

	ofstream his("histoRVB.dat");
	for(int i=0;i<256;i++)
		his<<i<<" "<<histoR[i]<<" "<<histoG[i]<<" "<<histoB[i]<<endl;
	his.close();

	return 0;
}
