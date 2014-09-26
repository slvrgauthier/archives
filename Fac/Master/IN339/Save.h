#ifndef SAVE_H
#define SAVE_H

#include "Image.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

bool Image::save_ppm(string filename) const { 
	string name = filename.erase(filename.find_last_of("."), string::npos) + ".slvr.ppm";
	
	FILE *f_image;
	
	if( (f_image = fopen(name.c_str(), "wb")) == NULL)
	{
		cout << "Pas d'acces en ecriture sur l'image" << endl;
		return false;
	}
	else
	{
		fprintf(f_image,"P6\r");
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

bool Image::save_rgbc(string filename) const { 
	string name = filename.erase(filename.find_last_of("."), string::npos) + ".slvr.rgbc";
	
	FILE *f_image;
	
	if( (f_image = fopen(name.c_str(), "wb")) == NULL)
	{
		cout << "Pas d'acces en ecriture sur l'image" << endl;
		return false;
	}
	else
	{
		fprintf(f_image,"RGBC\r");
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

bool Image::save_yccc(string filename) const { 
	string name = filename.erase(filename.find_last_of("."), string::npos) + ".slvr.yccc";
	
	FILE *f_image;
	
	if( (f_image = fopen(name.c_str(), "wb")) == NULL)
	{
		cout << "Pas d'acces en ecriture sur l'image" << endl;
		return false;
	}
	else
	{
		fprintf(f_image,"YCCC\r");
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
