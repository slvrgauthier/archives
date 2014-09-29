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
				int xyc = j/2 * width/2 + i/2;
				imageOut.setData(3*xy, this->getData(xyc));
				imageOut.setData(3*xy + 1, this->getData(xy + width*height/4));
				imageOut.setData(3*xy + 2, this->getData(xyc + 5*width*height/4));
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
				int xyc = j/2 * width/2 + i/2;
				unsigned char Y = this->getData(xy);
				unsigned char Cb = this->getData(xyc + width*height);
				unsigned char Cr = this->getData(xyc + 5*width*height/4);
				imageOut.setData(3*xy, (unsigned char)(max(0.0,min(255.0,(Y - 0.34414 * (Cb-128) - 0.71414 * (Cr-128))))));
				imageOut.setData(3*xy + 1, (unsigned char)(max(0.0,min(255.0,(Y + 1.402 * (Cr-128))))));
				imageOut.setData(3*xy + 2, (unsigned char)(max(0.0,min(255.0,(Y + 1.772 * (Cb-128))))));
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
			int xyc = j/2 * width/2 + i/2;
			imageOut.setData(xyc, imageref.getData(3*xy));
			imageOut.setData(xy + width*height/4, imageref.getData(3*xy + 1));
			imageOut.setData(xyc + 5*width*height/4, imageref.getData(3*xy + 2));
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
			int xyc = j/2 * width/2 + i/2;
			unsigned char ppm_r = imageref.getData(3*xy);
			unsigned char ppm_g = imageref.getData(3*xy + 1);
			unsigned char ppm_b = imageref.getData(3*xy + 2);
			imageOut.setData(xy, (unsigned char)(max(0.0,min(255.0,(0.299*ppm_r + 0.587*ppm_g + 0.114*ppm_b)))));
			imageOut.setData(xyc + width*height, (unsigned char)(max(0.0,min(255.0,(-0.1687*ppm_r + -0.3313*ppm_g + 0.5*ppm_b +128)))));
			imageOut.setData(xyc + 5*width*height/4, (unsigned char)(max(0.0,min(255.0,(0.5*ppm_r + -0.4187*ppm_g + -0.0813*ppm_b +128)))));
		}
	}
	return imageOut;
}

#endif
