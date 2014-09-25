#include "ImageBase.h"
#include <stdio.h>
#include <algorithm>

using namespace std;

int main(int argc, char **argv) {
	char cNomImgLue[250], cNomImgEcrite[250];
  
	if (argc < 3) 
	{
		printf("Usage: ImageIn.pgm ImageOut.pgm\n"); 
		return 1;
	}
	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcrite);
	
	
	//ImageBase imIn, imOut;
	ImageBase imIn;
	imIn.load(cNomImgLue);

	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	unsigned char Vmin = 0, Vmax = 0, S;
	for(int x = 0; x < imIn.getHeight(); ++x)
		for(int y = 0; y < imIn.getWidth(); ++y)
		{
		  Vmin = min(Vmin,imIn[x][y]);
		  Vmax = max(Vmax,imIn[x][y]);
		}
	S = (Vmax + Vmin)/2;
	
	for(int x = 0; x < imIn.getHeight(); ++x)
		for(int y = 0; y < imIn.getWidth(); ++y)
		{
			if (imIn[x][y] < S) imOut[x][y] = 0;
			else imOut[x][y] = 255;
		}
		
	imOut.save(cNomImgEcrite);
	
	printf("Niveau maximum : %d\nNiveau minimum : %d\nSeuil : %d\n",Vmax,Vmin,S); 

	return 0;
}
