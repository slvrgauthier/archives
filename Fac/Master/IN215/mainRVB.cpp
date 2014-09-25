#include "ImageBase.h"
#include <stdio.h>

int main(int argc, char **argv) {
	char cNomImgLue[250], cNomImgEcrite[250];
	int S1, S2, S3;
  
	if (argc < 4) 
	{
		printf("Usage: ImageIn.ppm ImageOut.ppm Seuil1 [Seuil2] [Seuil3] \n"); 
		return 1;
	}
	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcrite);
	sscanf (argv[3],"%d",&S1);
	if(argc > 4) sscanf (argv[4],"%d",&S2);
	if(argc > 5) sscanf (argv[5],"%d",&S3);
	
	ImageBase imIn;
	imIn.load(cNomImgLue);

	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
	
	ImageBase planR = *(imIn.getPlan(imIn.PLAN_R));
	ImageBase planG = *(imIn.getPlan(imIn.PLAN_G));
	ImageBase planB = *(imIn.getPlan(imIn.PLAN_B));

	for(int x = 0; x < imIn.getHeight(); ++x)
		for(int y = 0; y < imIn.getWidth(); ++y)
		{
			if (planR[x][y] < S1) imOut[x*3][y*3] = 0;
			else if(argc == 5 && planR[x][y] < S2) imOut[x*3][y*3] = 128;
			else if(argc > 5 && planR[x][y] < S2) imOut[x*3][y*3] = 85;
			else if(argc > 5 && planR[x][y] < S3) imOut[x*3][y*3] = 170;
			else imOut[x*3][y*3] = 255;
			
			if (planG[x][y] < S1) imOut[x*3][y*3+1] = 0;
			else if(argc == 5 && planG[x][y] < S2) imOut[x*3][y*3+1] = 128;
			else if(argc > 5 && planG[x][y] < S2) imOut[x*3][y*3+1] = 85;
			else if(argc > 5 && planG[x][y] < S3) imOut[x*3][y*3+1] = 170;
			else imOut[x*3][y*3+1] = 255;
			
			if (planB[x][y] < S1) imOut[x*3][y*3+2] = 0;
			else if(argc == 5 && planB[x][y] < S2) imOut[x*3][y*3+2] = 128;
			else if(argc > 5 && planB[x][y] < S2) imOut[x*3][y*3+2] = 85;
			else if(argc > 5 && planB[x][y] < S3) imOut[x*3][y*3+2] = 170;
			else imOut[x*3][y*3+2] = 255;
		}
		
	imOut.save(cNomImgEcrite);
	
	return 0;
}
