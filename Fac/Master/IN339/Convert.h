#ifndef CONVERT_H
#define CONVERT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

Image Image::convertToPGM() const {
	if(format == PGM) {
		return Image(this);
	}
	else if(format == SLVR) {
		Image imageOut(PGM, name, width, height, false, channels);
		imageOut.resizeData(width * height);
		
		unsigned char Y[width*height];
		
		for(unsigned i=0 ; i < width ; i++) {
			for(unsigned j=0 ; j < height ; j++) {
				int xy = j * width + i;
				Y[xy] = this->getData(xy);
			}
		}
		
		unsigned char bloc_dim = 8;
		double A[2];
		double valY, val_cos;
		
		for(unsigned int y=0 ; y < height ; y+=bloc_dim) {
			for(unsigned int x=0 ; x < width ; x+=bloc_dim) {
				cout << "\rIDCT en cours... " << 100*(y*width+x)/(height*width) << "%" << flush;
				for(unsigned int u=0 ; u < bloc_dim && u+x < width ; u++) {
					for(unsigned int v=0 ; v < bloc_dim && v+y < height ; v++) {
						int xy = (v+y) * width + (u+x);
							
						// ============= Inverse Discret Cosine Transform =============
						valY = 0;
						for(unsigned int i=0 ; i < bloc_dim && i+x < width ; i++) {
							for(unsigned int j=0 ; j < bloc_dim && j+y < height ; j++) {
								int xy2 = (j+y) * width + (i+x);
								A[0] = (i == 0)? 1/sqrt(2) : 1;
								A[1] = (j == 0)? 1/sqrt(2) : 1;
								val_cos = cos((2*i+1)*u*M_PI/(2*bloc_dim)) * cos((2*j+1)*v*M_PI/(2*bloc_dim));
								valY += Y[xy2] * val_cos * A[0] * A[1];
							}
						}
						valY *= 2 / (double)bloc_dim;
						// ============================================================
						
						// ============= Second Quantification =============
						valY *= quant(u,v,LUMA);
						// =================================================
// valY=Y[xy];
// cout<<endl<<"valY = "<<valY<<endl;
						// ========== Convert to uncompressed Y ==========
						imageOut.setData(xy, (unsigned char)(max(0.0,min(255.0,valY))));
						// =================================================
					}
				}
			}
		}
		cout << "\rIDCT en cours... 100%" << endl;
		
		return imageOut;
	}
}

Image Image::convertToPPM() const {
	if(format == PPM) {
		return Image(this);
	}
	else if(format == RGBC) {
		Image imageOut(PPM, name, width, height, true, channels);
		imageOut.resizeData(width * height * 3);
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
		imageOut.resizeData(width * height * 3);
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
		imageOut.resizeData(width * height * 3);
		
		unsigned char Y[width*height];
		unsigned char Cr[width*height/4];
		unsigned char Cb[width*height/4];
		
		for(unsigned i=0 ; i < width ; i++) {
			for(unsigned j=0 ; j < height ; j++) {
				int xy = j * width + i;
				int xyc = j/2 * width/2 + i/2;
				Y[xy] = this->getData(xy);
				Cr[xyc] = this->getData(xyc + height*width);
				Cb[xyc] = this->getData(xyc + 5*height*width/4);
			}
		}
		
		unsigned char bloc_dim = 8;
		double A[2];
		double valY, valCr, valCb, val_cos;
		
		for(unsigned int y=0 ; y < height ; y+=bloc_dim) {
			for(unsigned int x=0 ; x < width ; x+=bloc_dim) {
				cout << "\rIDCT en cours... " << 100*(y*width+x)/(height*width) << "%" << flush;
				for(unsigned int u=0 ; u < bloc_dim && u+x < width ; u++) {
					for(unsigned int v=0 ; v < bloc_dim && v+y < height ; v++) {
						int xy = (v+y) * width + (u+x);
						int xyc = (v+y)/2 * width/2 + (u+x)/2;
							
						// ============= Inverse Discret Cosine Transform =============
						valY = valCr = valCb = 0;
						for(unsigned int i=0 ; i < bloc_dim && i+x < width ; i++) {
							for(unsigned int j=0 ; j < bloc_dim && j+y < height ; j++) {
								int xy2 = (j+y) * width + (i+x);
								int xyc2 = (j+y)/2 * width/2 + (i+x)/2;
								A[0] = (i == 0)? 1/sqrt(2) : 1;
								A[1] = (j == 0)? 1/sqrt(2) : 1;
								val_cos = cos((2*i+1)*u*M_PI/(2*bloc_dim)) * cos((2*j+1)*v*M_PI/(2*bloc_dim));
								valY += Y[xy2] * val_cos * A[0] * A[1];
								valCr += Cr[xyc2] * val_cos * A[0] * A[1];
								valCb += Cb[xyc2] * val_cos * A[0] * A[1];
							}
						}
						valY *= 2 / (double)bloc_dim;
						valCr *= 2 / (double)bloc_dim;
						valCb *= 2 / (double)bloc_dim;
						// ============================================================
						
						// ============= Second Quantification =============
/*						valY *= quant(u,v,LUMA);
						valCr *= quant(u,v,REDDIFF);
						valCb *= quant(u,v,BLUEDIFF);
*/						// =================================================
// valY=Y[xy];valCr=Cr[xyc];valCb=Cb[xyc];
cout<<endl;if(valY > 1 || valY < -1)cout<<"valY = "<<valY;if(valCr > 1 || valCr < -1)cout<<", valCr = "<<valCr;if(valCb > 1 || valCb < -1)cout<<", valCb = "<<valCb;
						// ========== Convert to uncompressed RGB ==========
						imageOut.setData(3*xy, (unsigned char)(max(0.0,min(255.0,( valY + 1.402 * valCr ))))); //R
						imageOut.setData(3*xy + 1, (unsigned char)(max(0.0,min(255.0,( valY - 0.34414 * valCb - 0.71414 * valCr ))))); //G
						imageOut.setData(3*xy + 2, (unsigned char)(max(0.0,min(255.0,( valY + 1.772 * valCb ))))); //B
						// =================================================
					}
				}
			}
		}
		cout << "\rIDCT en cours... 100%" << endl;
		
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
			unsigned char Y = imageOut.getData(xy);
			unsigned char Cr = imageOut.getData(xyc + width*height);
			unsigned char Cb = imageOut.getData(xyc + 5*width*height/4);
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
	else if(format == PPM) {
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
					int xyc = j/2 * width/2 + i/2;
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
					Cr[xyc] = (unsigned char)(val_cr / count);
					Cb[xyc] = (unsigned char)(val_cb / count);
				}
			}
		}
		// =================================================
		
		// ============= First Quantification =============
		unsigned char mask = 255;
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
							int xy = (v+y) * width + (u+x);
							int xyc = (v+y)/2 * width/2 + (u+x)/2;
							
							// ============= Discret Cosine Transform =============
							valY = valCr = valCb = 0;
							A[0] = (u == 0)? 1/sqrt(2) : 1;
							A[1] = (v == 0)? 1/sqrt(2) : 1;
							for(unsigned int i=0 ; i < bloc_dim && i+x < width ; i++) {
								for(unsigned int j=0 ; j < bloc_dim && j+y < height ; j++) {
									int xy2 = (j+y) * width + (i+x);
									int xyc2 = (j+y)/2 * width/2 + (i+x)/2;
									val_cos = cos((2*i+1)*u*M_PI/(2*bloc_dim)) * cos((2*j+1)*v*M_PI/(2*bloc_dim));
									valY += Y[xy2] * val_cos;
									valCr += Cr[xyc2] * val_cos;
									valCb += Cb[xyc2] * val_cos;
								}
							}
							valY *= 2*A[0]*A[1] / (double)bloc_dim;
							valCr *= 2*A[0]*A[1] / (double)bloc_dim;
							valCb *= 2*A[0]*A[1] / (double)bloc_dim;
							// ====================================================
							
							// ============= Second Quantification =============
/*							valY /= (double)quant(u,v,LUMA);
							valCr /= (double)quant(u,v,REDDIFF);
							valCb /= (double)quant(u,v,BLUEDIFF);
*/							// =================================================
// valY=Y[xy];valCr=Cr[xyc];valCb=Cb[xyc];
cout<<endl;if(valY > 1 || valY < -1)cout<<"valY = "<<valY;if(valCr > 1 || valCr < -1)cout<<", valCr = "<<valCr;if(valCb > 1 || valCb < -1)cout<<", valCb = "<<valCb;
							imageOut.setData(xy, (unsigned char)valY);
							imageOut.setData(xyc + height*width, (unsigned char)valCr);
							imageOut.setData(xyc + 5*height*width/4, (unsigned char)valCb);
						}
					}
				}
			}
			cout << "\rDCT en cours... 100%" << endl;
		}
			
		return imageOut;
	}
	else if(format == PGM) {
		Image imageref = new Image(this->convertToPGM());
		Image imageOut(SLVR, imageref.getName(), imageref.getWidth(), imageref.getHeight(), false, imageref.getChannels());
		imageOut.resizeData(imageref.getWidth() * imageref.getHeight());
		
		// ========== Convert to Y ==========
		unsigned char Y[width*height];
		for(unsigned int j=0 ; j < height ; j++) {
			for(unsigned int i=0 ; i < width ; i++) {
				int xy = j * width + i;
				Y[xy] = (unsigned char)imageref.getData(xy);
			}
		}
		// =================================================
		
		// ============= First Quantification =============
		unsigned char mask = 255;
		for(unsigned int i=0 ; i < width*height ; i++) {
			Y[i] = Y[i] & mask;
		}
		// ================================================
		
		{
			unsigned char bloc_dim = 8;
			double A[2];
			double valY, val_cos;
			
			for(unsigned int y=0 ; y < height ; y+=bloc_dim) {
				for(unsigned int x=0 ; x < width ; x+=bloc_dim) {
					cout << "\rDCT en cours... " << 100*(y*width+x)/(height*width) << "%" << flush;
					for(unsigned int u=0 ; u < bloc_dim && u+x < width ; u++) {
						for(unsigned int v=0 ; v < bloc_dim && v+y < height ; v++) {
							int xy = (v+y) * width + (u+x);
							
							// ============= Discret Cosine Transform =============
							valY = 0;
							A[0] = (u == 0)? 1/sqrt(2) : 1;
							A[1] = (v == 0)? 1/sqrt(2) : 1;
							for(unsigned int i=0 ; i < bloc_dim && i+x < width ; i++) {
								for(unsigned int j=0 ; j < bloc_dim && j+y < height ; j++) {
									int xy2 = (j+y) * width + (i+x);
									val_cos = cos((2*i+1)*u*M_PI/(2*bloc_dim)) * cos((2*j+1)*v*M_PI/(2*bloc_dim));
									valY += Y[xy2] * val_cos;
								}
							}
							valY *= 2*A[0]*A[1] / (double)bloc_dim;
							// ====================================================
							
							// ============= Second Quantification =============
							valY /= (double)quant(u,v,LUMA);
							// =================================================
// valY=Y[xy];
// cout<<endl<<"valY = "<<valY<<endl;
							imageOut.setData(xy, (unsigned char)valY);
						}
					}
				}
			}
			cout << "\rDCT en cours... 100%" << endl;
		}
			
		return imageOut;
	}
}

#endif
