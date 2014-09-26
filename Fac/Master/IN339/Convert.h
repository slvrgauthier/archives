#ifndef CONVERT_H
#define CONVERT_H

#include "Image.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

Image Image::convertToPPM() const {
	if(format == PPM) {
		return Image(this);
	}
	else if(format == RGBC) {
		Image imageOut(PPM, name, width, height, true, channels);
		imageOut.resizeData(width * height * channels.size());
		// RED and BLUE compressed, not GREEN
		for(unsigned int j=0 ; j < height ; j++) {
			for(unsigned int i=0 ; i < width ; i++) {
				int xy = j * width + i;
				imageOut.setData(3*xy, this->getData(xy/4));
				imageOut.setData(3*xy + 1, this->getData((xy + xy%4 + width*height)/4));
				imageOut.setData(3*xy + 2, this->getData((xy + 3*width*height)/4));
			}
		}
		return imageOut;
	}
	else if(format == YCCC) {
		Image imageOut(PPM, name, width, height, true, channels);
		imageOut.resizeData(width * height * channels.size());
		// REDDIFF and BLUEDIFF compressed, not LUMA
		for(unsigned int j=0 ; j < height ; j++) {
			for(unsigned int i=0 ; i < width ; i++) {
				int xy = j * width + i;
				unsigned char Y = this->getData((xy + xy%4)/4);
				unsigned char Cr = this->getData((xy + width*height)/4);
				unsigned char Cb = this->getData((xy + 3*width*height)/4);
				imageOut.setData(3*xy, (unsigned char)(Y + 1.402 * (Cr-128)));
				imageOut.setData(3*xy + 1, (unsigned char)(Y - 0.34414 * (Cb-128) - 0.71414 * (Cr-128)));
				imageOut.setData(3*xy + 2, (unsigned char)(Y + 1.772 * (Cb-128)));
			}
		}
		return imageOut;
	}
}

Image Image::convertToRGBC() const {
	if(format == RGBC) {
		return Image(this);
	}
	
	Image imageref = new Image(this->convertToPPM());
	Image imageOut(RGBC, imageref.getName(), imageref.getWidth(), imageref.getHeight(), true, imageref.getChannels());
	imageOut.resizeData(imageref.getWidth() * imageref.getHeight() * imageref.getChannels().size() / 2);
	// RED and BLUE compressed, not GREEN
	for(unsigned int j=0 ; j < height ; j++) {
		for(unsigned int i=0 ; i < width ; i++) {
			int xy = j * width + i;
			imageOut.setData(xy/4, imageref.getData(3*xy));
			imageOut.setData((xy + xy%4 + width*height)/4, imageref.getData(3*xy + 1));
			imageOut.setData((xy + 3*width*height)/4, imageref.getData(3*xy + 2));
		}
	}
	return imageOut;
}

Image Image::convertToYCCC() const {
	if(format == YCCC) {
		return Image(this);
	}
	
	Image imageref = new Image(this->convertToPPM());
	Image imageOut(YCCC, imageref.getName(), imageref.getWidth(), imageref.getHeight(), true, imageref.getChannels());
	imageOut.resizeData(imageref.getWidth() * imageref.getHeight() * imageref.getChannels().size() / 2);
	// REDDIFF and BLUEDIFF compressed, not LUMA
	for(unsigned int j=0 ; j < height ; j++) {
		for(unsigned int i=0 ; i < width ; i++) {
			int xy = j * width + i;
			unsigned char ppm_r = imageref.getData(3*xy);
			unsigned char ppm_g = imageref.getData(3*xy + 1);
			unsigned char ppm_b = imageref.getData(3*xy + 2);
			imageOut.setData((xy + xy%4)/4, (unsigned char)(0.299*ppm_r + 0.587*ppm_g + 0.114*ppm_b));
			imageOut.setData((xy + width*height)/4, (unsigned char)(-0.1687*ppm_r + -0.3313*ppm_g + 0.5*ppm_b +128));
			imageOut.setData((xy + 3*width*height)/4, (unsigned char)(0.5*ppm_r + -0.4187*ppm_g + -0.0813*ppm_b +128));
		}
	}
	return imageOut;
}

#endif
