#ifndef LOAD_H
#define LOAD_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void ignoreComments(FILE * f)
{
	unsigned char c;
	while((c=fgetc(f)) == '#')
		while((c=fgetc(f)) != '\n');
	fseek(f, -sizeof(unsigned char), SEEK_CUR);
}

bool Image::load_(string filename) { 
	FILE *f_image;
	int max_grey_val;
	
	if((f_image = fopen(filename.c_str(), "rb")) == NULL)
	{
		cout << "Pas d'accès en lecture sur l'image" << endl;
		return false;
	}
	else
	{
		if(format == PGM) {
			fscanf(f_image, "P5 ");
		}
		else if(format == PPM) {
			fscanf(f_image, "P6 ");
		}
		else if(format == RGBC) {
			fscanf(f_image, "RGBC ");
		}
		else if(format == YCCC) {
			fscanf(f_image, "YCCC ");
		}
		else if(format == SLVR) {
			fscanf(f_image, "SLVR ");
		}
		ignoreComments(f_image);
		fscanf(f_image, "%d %d %d%*c", &width, &height, &max_grey_val);
		
		if(format == PGM) {
			length = width * height;
			channels.push_back(GREY);
		}
		else if(format == PPM) {
			length = 3 * width * height;
			channels.push_back(RED);
			channels.push_back(GREEN);
			channels.push_back(BLUE);
		}
		else if(format == RGBC) {
			length = 3 * width * height / 2;
			channels.push_back(RED);
			channels.push_back(GREEN);
			channels.push_back(BLUE);
		}
		else if(format == YCCC) {
			length = 3 * width * height / 2;
			channels.push_back(LUMA);
			channels.push_back(REDDIFF);
			channels.push_back(BLUEDIFF);
		}
		else if(format == SLVR) {
			length = 3 * width * height / 2;
			channels.push_back(LUMA);
			channels.push_back(REDDIFF);
			channels.push_back(BLUEDIFF);
		}
		
		resizeData(length);
		if(fread((unsigned char*)data, sizeof(unsigned char), length, f_image) != (size_t)(length))
		{
			cout << "Erreur de lecture de l'image" << endl;
			return false;
		}
		fclose(f_image);
		return true;
	}
}

#endif
