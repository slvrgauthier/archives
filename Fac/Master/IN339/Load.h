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
		cout << "\nPas d'accès en lecture sur l'image" << endl;
		return false;
	}
	else
	{
		fscanf(f_image, "P6 ");
		ignoreComments(f_image);
		fscanf(f_image, "%d %d %d%*c", &width, &height, &max_grey_val);
		
		int length=3*width*height;
		cout<<"length = "<<length<<endl;
		if((data = (unsigned char*)calloc(length, sizeof(unsigned char))) == NULL)
		{
			cout <<"\n Allocation dynamique impossible"<<endl;
			return false;
		}
		if(fread((unsigned char*)data, sizeof(unsigned char), length, f_image) != (size_t)(length))
		{
			cout<<"\nErreur de lecture de l'image"<<endl;
			return false;
		}
		fclose(f_image);
		return true;
	}
}

#endif
