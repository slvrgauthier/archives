#ifndef CONVERT_H
#define CONVERT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

Image Image::convertToPGM() const {}

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
				unsigned char Cr = this->getData(xyc + width*height);
				unsigned char Cb = this->getData(xyc + 5*width*height/4);
				imageOut.setData(3*xy, (unsigned char)(max(0.0,min(255.0,( Y + 1.402 * (Cr-128) ))))); //R
				imageOut.setData(3*xy + 1, (unsigned char)(max(0.0,min(255.0,( Y - 0.34414 * (Cb-128) - 0.71414 * (Cr-128) ))))); //G
				imageOut.setData(3*xy + 2, (unsigned char)(max(0.0,min(255.0,( Y + 1.772 * (Cb-128) ))))); //B
			}
		}
		return imageOut;
	}
	else if(format == SLVR) {
		Image imageOut(PPM, name, width, height, true, channels);
		imageOut.resizeData(width * height * channels.size());
		//TODO
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
	
	string auxname = imageref.getName();
	auxname = auxname.substr(0,auxname.find_last_of(".")) + ".AUXrgbc" + auxname.substr(auxname.find_last_of("."), string::npos);
	Image imageAux(PPM, auxname, 2*imageref.getWidth(), imageref.getHeight(), true, imageref.getChannels());
	for(unsigned int j=0 ; j < height ; j++) {
		for(unsigned int i=0 ; i < width ; i++) {
			int xy = j * width + i;
			int xyc = j/2 * width/2 + i/2;
			imageAux.setData(3 * ((j+height/2)/2 * 2*width + i/2), imageOut.getData(xyc));
			imageAux.setData(3 * (j * 2*width + i + width/2) + 1, imageOut.getData(xy + width*height/4));
			imageAux.setData(3 * ((j+height/2)/2 * 2*width + i/2 + 3*width/2) + 2, imageOut.getData(xyc + 5*width*height/4));
		}
	}
	imageAux.save(auxname, PPM);
	
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
			imageOut.setData(xy, (unsigned char)(max(0.0,min(255.0,( 0.299*ppm_r + 0.587*ppm_g + 0.114*ppm_b ))))); //Y
			imageOut.setData(xyc + width*height, (unsigned char)(max(0.0,min(255.0,( 0.5*ppm_r + -0.4187*ppm_g + -0.0813*ppm_b +128 ))))); //Cr
			imageOut.setData(xyc + 5*width*height/4, (unsigned char)(max(0.0,min(255.0,( -0.1687*ppm_r + -0.3313*ppm_g + 0.5*ppm_b +128 ))))); //Cb
		}
	}
	
	string auxname = imageref.getName();
	auxname = auxname.substr(0,auxname.find_last_of(".")) + ".AUXyccc" + auxname.substr(auxname.find_last_of("."), string::npos);
	Image imageAux(PGM, auxname, 2*imageref.getWidth(), imageref.getHeight(), true, imageref.getChannels());
	for(unsigned int j=0 ; j < height ; j++) {
		for(unsigned int i=0 ; i < width ; i++) {
			int xy = j * width + i;
			int xyc = j/2 * width/2 + i/2;
			unsigned char Y = this->getData(xy);
			unsigned char Cr = this->getData(xyc + width*height);
			unsigned char Cb = this->getData(xyc + 5*width*height/4);
			imageAux.setData(j * 2*width + i, Y);
			imageAux.setData((j+height/2)/2 * 2*width + i/2 + width, Cr + 128);
			imageAux.setData((j+height/2)/2 * 2*width + i/2 + 3*width/2, Cb + 128);
		}
	}
	imageAux.save(auxname, PGM);
	
	return imageOut;
}

Image Image::convertToSLVR() const {
	if(format == SLVR) {
		return Image(this);
	}
	
	Image imageref = new Image(this->convertToPPM());
	Image imageOut(SLVR, imageref.getName(), imageref.getWidth(), imageref.getHeight(), true, imageref.getChannels());
	imageOut.resizeData(imageref.getWidth() * imageref.getHeight() * imageref.getChannels().size() / 2);
	
	// ========== Convert to compressed YCrCb ==========
	unsigned char Y[width*height];
	unsigned char Cr[width*height/4];
	unsigned char Cb[width*height/4];
	{
		unsigned char tmp_Cr[width*height];
		unsigned char tmp_Cb[width*height];
		
		// Convert RGB to YCrCb
		for(unsigned int j=0 ; j < height ; j++) {
			for(unsigned int i=0 ; i < width ; i++) {
				int xy = j * width + i;
				unsigned char ppm_r = imageref.getData(3*xy);
				unsigned char ppm_g = imageref.getData(3*xy + 1);
				unsigned char ppm_b = imageref.getData(3*xy + 2);
				Y[xy] = (unsigned char)(max(0.0,min(255.0,( 0.299*ppm_r + 0.587*ppm_g + 0.114*ppm_b ))));
				tmp_Cr[xy] = (unsigned char)(max(0.0,min(255.0,( 0.5*ppm_r + -0.4187*ppm_g + -0.0813*ppm_b +128 ))));
				tmp_Cb[xy] = (unsigned char)(max(0.0,min(255.0,( -0.1687*ppm_r + -0.3313*ppm_g + 0.5*ppm_b +128 ))));
			}
		}
	
		// Compress Cr and Cb with mean
		for(unsigned int j=0 ; j < height ; j+=2) {
			for(unsigned int i=0 ; i < width ; i+=2) {
				int xy = j * width + i;
				int val_cr = tmp_Cr[xy];
				int val_cb = tmp_Cb[xy];
				int count = 1;
				if(i < width-1) {
					val_cr += tmp_Cr[xy+1];
					val_cb += tmp_Cb[xy+1];
					count++;
				}
				if(j < height-1) {
					val_cr += tmp_Cr[xy+width];
					val_cb += tmp_Cb[xy+width];
					count++;
				}
				if(j < height-1 && i < width-1) {
					val_cr += tmp_Cr[xy+width+1];
					val_cb += tmp_Cb[xy+width+1];
					count++;
				}
				Cr[xy] = (unsigned char)(val_cr / count);
				Cb[xy] = (unsigned char)(val_cb / count);
			}
		}
	}
	// =================================================
	
	// ============= First Quantification =============
	unsigned char mask = 252;
	for(unsigned int i=0 ; i < width*height ; i++) {
		Y[i] = Y[i] & mask;
		if(i%4 == 0) {
			Cr[i/4] = Cr[i/4] & mask;
			Cb[i/4] = Cb[i/4] & mask;
		}
	}
	// ================================================
	
	{
		unsigned char bloc_dim = 8;
		double A[2];
		double valY, valCr, valCb, val_cos;
		
		for(unsigned int y=0 ; y < height ; y+=bloc_dim) {
			for(unsigned int x=0 ; x < width ; x+=bloc_dim) {
				cout << "\rDCT en cours... " << 100*(y*width+x)/(height*width) << "%" << flush;
				for(unsigned int u=0 ; u < bloc_dim && u+x < width ; u++) {
					for(unsigned int v=0 ; v < bloc_dim && v+y < height ; v++) {
						
						// ============= Discret Cosine Transform =============
						valY = valCr = valCb = 0;
						A[0] = (u == 0)? 1/sqrt(2) : 1;
						A[1] = (v == 0)? 1/sqrt(2) : 1;
						for(unsigned int i=0 ; i < bloc_dim && i+x < width ; i++) {
							for(unsigned int j=0 ; j < bloc_dim && j+y < height ; j++) {
								val_cos = cos((2*i+1)*u*M_PI/(2*bloc_dim)) * cos((2*j+1)*v*M_PI/(2*bloc_dim));
								valY += Y[(j+y) * width + (i+x)] * val_cos;
								if(i+x < width/2 && j+y < height/2) {
									valCr += Cr[(j+y) * width + (i+x)] * val_cos;
									valCb += Cb[(j+y) * width + (i+x)] * val_cos;
								}
							}
						}
						valY *= 2*A[0]*A[1] / bloc_dim;
						valCr *= 2*A[0]*A[1] / bloc_dim;
						valCb *= 2*A[0]*A[1] / bloc_dim;
						// ====================================================
						
						// ============= Second Quantification =============
						valY /= quant(u,v,LUMA);
						valCr /= quant(u,v,REDDIFF);
						valCb /= quant(u,v,BLUEDIFF);
						// =================================================
						
						imageOut.setData((v+y) * width + (u+x), (unsigned char)valY);
						if(u+x < width/2 && v+y < height/2) {
							imageOut.setData((v+y+height) * width + (u+x), (unsigned char)valCr);
							imageOut.setData((v+y+5*height/4) * width + (u+x), (unsigned char)valCb);
						}
					}
				}
			}
		}
		cout << "\rDCT en cours... 100%" << endl;
	}
		
	return imageOut;
}

#endif
