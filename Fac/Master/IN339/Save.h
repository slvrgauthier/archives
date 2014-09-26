#ifndef SAVE_H
#define SAVE_H

#include "Image.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

bool Image::save_ppm(string filename) { 
	string name = filename + ".slvr.ppm";
	
	FILE *f_image;
	int length = 3*width*height;
	cout<<"length = "<<length<<endl;
	
	if( (f_image = fopen(name.c_str(), "wb")) == NULL)
	{
		cout<<"\nPas d'acces en ecriture sur l'image"<<endl;
		return false;
	}
	else
	{
		fprintf(f_image,"P6\r");
		fprintf(f_image,"# Created by Slvr\n");
		fprintf(f_image,"%d %d\r255\r", width, height);
		
		if(fwrite((unsigned char*)data, sizeof(unsigned char), length, f_image) != (size_t)(length))
		{
			cout<<"\nErreur d'ecriture de l'image"<<endl;
			return false;
		}
		fclose(f_image);
		return true;
	}
}

#endif
