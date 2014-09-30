#ifndef SAVE_H
#define SAVE_H

#include "Image.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

bool Image::save_(string filename) const { 
	string name = filename.erase(filename.find_last_of("."), string::npos);
	if(format == PGM) {
		name += ".pgm";
	}
	else if(format == PPM) {
		name += ".ppm";
	}
	else if(format == RGBC) {
		name += ".rgbc";
	}
	else if(format == YCCC) {
		name += ".yccc";
	}
	else {
		name += ".unknown";
	}
	
	FILE *f_image;
	
	if( (f_image = fopen(name.c_str(), "wb")) == NULL)
	{
		cout << "Pas d'acces en ecriture sur l'image" << endl;
		return false;
	}
	else
	{
		if(format == PGM) {
			fprintf(f_image,"P5\r");
		}
		else if(format == PPM) {
			fprintf(f_image,"P6\r");
		}
		else if(format == RGBC) {
			fprintf(f_image,"RGBC\r");
		}
		else if(format == YCCC) {
			fprintf(f_image,"YCCC\r");
		}
		else {
			fprintf(f_image,"UNKNOWN\r");
		}
		fprintf(f_image,"# Created by Slvr\n");
		fprintf(f_image,"%d %d\r255\r", width, height);
		
		if(fwrite((unsigned char*)data, sizeof(unsigned char), length, f_image) != (size_t)(length))
		{
			cout << "Erreur d'ecriture de l'image" << endl;
			return false;
		}
		fclose(f_image);
		return true;
	}
}

#endif
