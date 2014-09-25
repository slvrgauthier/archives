#include "ImageBase.h"
#include <fstream>

using namespace std;

int main (int argc, char** argv){
	char cNomImgLue[250];
	int indice;

	if (argc != 4) {
		printf("Usage : ImageIn.pgm l/c Indice\n");
		return 1;
	}
	sscanf(argv[1],"%s",cNomImgLue);
	sscanf(argv[3],"%d",&indice);

	ImageBase imIn;
	imIn.load(cNomImgLue);

	ofstream profile("profile.dat");

	int max;
	if(argv[2][0] == 'c') {
		max = imIn.getHeight();
		printf("Ligne | Niveau\n");
		for(int i=0;i<max;i++) {
			//printf("%5d | %6d\n",i,imIn[indice][i]);
			profile<<(int)imIn[indice][i]<<endl;
		}
	}
	else if(argv[2][0] == 'l') {
		max = imIn.getWidth();
		printf("Colonne | Niveau\n");
		for(int i=0;i<max;i++) {
			//printf("%7d | %6d\n",i,imIn[i][indice]);
			profile<<(int)imIn[i][indice]<<endl;
		}
	}
	else {
		printf("Usage : l pour Ligne ou c pour Colonne en second argument\n");
		return 2;
	}

	profile.close();

	return 0;
}
