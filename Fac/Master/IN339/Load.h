#ifndef LOAD_H
#define LOAD_H

#include "Image.h"
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

bool Image::load_ppm(string filename) { 
	FILE *f_image;
	int max_grey_val;
	
	if((f_image = fopen(filename.c_str(), "rb")) == NULL)
	{
		cout << "Pas d'accès en lecture sur l'image" << endl;
		return false;
	}
	else
	{
		fscanf(f_image, "P6 ");
		ignoreComments(f_image);
		fscanf(f_image, "%d %d %d%*c", &width, &height, &max_grey_val);
		channels.push_back(RED);
		channels.push_back(GREEN);
		channels.push_back(BLUE);
				
		length = 3 * width * height;
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

bool Image::load_rgbc(string filename) { 
	FILE *f_image;
	int max_grey_val;
	
	if((f_image = fopen(filename.c_str(), "rb")) == NULL)
	{
		cout << "Pas d'accès en lecture sur l'image" << endl;
		return false;
	}
	else
	{
		fscanf(f_image, "RGBC ");
		ignoreComments(f_image);
		fscanf(f_image, "%d %d %d%*c", &width, &height, &max_grey_val);
		channels.push_back(RED);
		channels.push_back(GREEN);
		channels.push_back(BLUE);
		
		length = 3 * width * height / 2;
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

bool Image::load_yccc(string filename) { 
	FILE *f_image;
	int max_grey_val;
	
	if((f_image = fopen(filename.c_str(), "rb")) == NULL)
	{
		cout << "Pas d'accès en lecture sur l'image" << endl;
		return false;
	}
	else
	{
		fscanf(f_image, "YCCC ");
		ignoreComments(f_image);
		fscanf(f_image, "%d %d %d%*c", &width, &height, &max_grey_val);
		channels.push_back(LUMA);
		channels.push_back(REDDIFF);
		channels.push_back(BLUEDIFF);
		
		length = 3 * width * height / 2;
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
