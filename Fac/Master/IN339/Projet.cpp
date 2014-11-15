// INCLUDES
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <math.h>

using namespace std;

//  =============================== =============================== ===============================
//            =============================== FUNCTIONS ===============================
//  =============================== =============================== ===============================
enum Format {
	PGM,
	PPM,
	SLVR,
	SLVRG,
	SLVRP
};

enum Channel {
	LUMA,
	REDDIFF,
	BLUEDIFF
};

void man() {
	cout << "Mode d'emploi :"<< endl;
	cout << "0 : Quitter" << endl;
	cout << "1 : Afficher le mode d'emploi" << endl;
	cout << "2 : Recharger l'image" << endl;
	cout << "3 : Changer d'image" << endl;
	cout << "4 : Calculer le PSNR" << endl;
	cout << "5 : Calculer le taux de compression" << endl;
	cout << "6 : Convertir l'image en PGM" << endl;
	cout << "7 : Convertir l'image en PPM" << endl;
	cout << "8 : Compresser l'image en SLVR" << endl;
	cout << "9 : Compresser et décompresser en SLVR (projet)" << endl;
}

unsigned char quant_luma[64] = {16,11,10,16,24,40,51,61,
								12,12,14,19,26,58,60,55,
								14,13,16,24,40,57,69,56,
								14,17,22,29,51,87,80,62,
								18,22,37,56,68,109,103,77,
								24,35,55,64,81,104,113,92,
								49,64,78,87,103,121,120,101,
								72,92,95,98,112,100,103,99};
								
unsigned char quant_crcb[64] = {17,18,24,47,99,99,99,99,
								18,21,26,66,99,99,99,99,
								24,26,56,99,99,99,99,99,
								47,66,99,99,99,99,99,99,
								99,99,99,99,99,99,99,99,
								99,99,99,99,99,99,99,99,
								99,99,99,99,99,99,99,99,
								99,99,99,99,99,99,99,99};
								
int quant(int u, int v, Channel c) {
	if(c == LUMA) {
		return quant_luma[v * 8 + u];
	}
	else if(c == BLUEDIFF || c == REDDIFF) {
		return quant_crcb[v * 8 + u];
	}
	else {
		return 1;
	}
}

//  =============================== =============================== ===============================
//              =============================== IMAGE ===============================
//  =============================== =============================== ===============================
class Image {
	private:
		Format format;
		string name;
		unsigned int width;
		unsigned int height;
		unsigned int length;
		unsigned char* data;

	public:
		Image(const string filename);
		Image(Format f, string n, unsigned int w, unsigned int h);
		Image(const Image* image);
		~Image();

		Format getFormat() const;
		string getName() const;
		unsigned int getWidth() const;
		unsigned int getHeight() const;
		unsigned int getLength() const;
		unsigned char getData(int i) const;
		void setData(int i, char value);

		bool load(const string filename);
		bool save(const string filename, Format fileformat) const;
		double psnr(const Image image) const;
		
		void resizeData(unsigned int length);
		
	private:
		bool load_(string filename);
		bool save_(string filename) const;
		
		Image convertToPGM() const;
		Image convertToPPM() const;
		Image convertToSLVR() const;
};

#define MAX_INT 65536  // 2^16

Image::Image(const string filename) { load(filename); }
Image::Image(Format f, string n, unsigned int w, unsigned int h) {
	format = f;
	name = n;
	width = w;
	height = h;
	length = width * height;
	if(f == PPM || f == SLVR) {
		length *= 3;
	}
	resizeData(length);
}
Image::Image(const Image* image) {
	format = image->getFormat();
	name = image->getName();
	width = image->getWidth();
	height = image->getHeight();
	length = width * height;
	if(format == PPM || format == SLVR) {
		length *= 3;
	}
	resizeData(length);
	for(unsigned int i=0 ; i < length ; i++) {
		data[i] = image->getData(i);
	}
}
Image::~Image() {/*TODO*/}

Format Image::getFormat() const { return format; }
string Image::getName() const { return name; }
unsigned int Image::getWidth() const { return width; }
unsigned int Image::getHeight() const { return height; }
unsigned int Image::getLength() const { return length; }
unsigned char Image::getData(int i) const { return data[i]; }
void Image::setData(int i, char value) { data[i] = value; }

bool Image::load(const string filename) {
	ifstream is(filename.c_str());
	if(!is) {
		return false;
	}
	
	string keyWord;
	is >> keyWord;
	is.close();
	
	if(keyWord.compare("P5") == 0) {
		format = PGM;
		name = filename;
		return load_(filename);
	}
	else if(keyWord.compare("P6") == 0) {
		format = PPM;
		name = filename;
		return load_(filename);
	}
	else if(keyWord.compare("SLVRG") == 0) {
		format = SLVRG;
		name = filename;
		return load_(filename);
	}
	else if(keyWord.compare("SLVRP") == 0) {
		format = SLVRP;
		name = filename;
		return load_(filename);
	}
	else {
		return false;
	}
}

bool Image::save(const string filename, Format fileformat) const {
	if(fileformat == format) {
		return save_(filename);
	}
	else {
		if(fileformat == PGM) {
			return convertToPGM().save_(filename + ".");
		}
		else if(fileformat == PPM) {
			return convertToPPM().save_(filename + ".");
		}
		else if(fileformat == SLVR || fileformat == SLVRG || fileformat == SLVRP) {
			return convertToSLVR().save_(filename + ".");
		}
		else {
			return false;
		}
	}
}

double Image::psnr(const Image image) const {
	double result = 0;
	if(length != image.getLength()) {
		result = -1;
	}
	else {
		for(unsigned int i=0 ; i < length ; i++) {
			result += pow(getData(i) - image.getData(i), 2);
		}
		result /= width * height;
		result = 10 * log(255*255/result);
	}
	return result;
}

void Image::resizeData(unsigned int length) {
	this->length = length;
	if((data = (unsigned char*)calloc(length, sizeof(unsigned char))) == NULL) {
		cout << "Allocation dynamique impossible" << endl;
		exit(EXIT_FAILURE);
	}
}

//  =============================== =============================== ===============================
//              =============================== LOAD ===============================
//  =============================== =============================== ===============================
void ignoreComments(FILE * f){
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
		else if(format == SLVRG) {
			fscanf(f_image, "SLVRG ");
		}
		else if(format == SLVRP) {
			fscanf(f_image, "SLVRP ");
		}
		ignoreComments(f_image);
		fscanf(f_image, "%d %d %d%*c", &width, &height, &max_grey_val);
		
		if(format == PGM) {
			length = width * height;
		}
		else if(format == PPM) {
			length = 3 * width * height;
		}
		else if(format == SLVRG) {
			length = width * height;
		}
		else if(format == SLVRP) {
			length = 3 * width * height;
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

//  =============================== =============================== ===============================
//              =============================== SAVE ===============================
//  =============================== =============================== ===============================
bool Image::save_(string filename) const { 
	string name = filename.erase(filename.find_last_of("."), string::npos);
	if(format == PGM) {
		name += ".pgm";
	}
	else if(format == PPM) {
		name += ".ppm";
	}
	else if(format == SLVRG || format == SLVRP) {
		name += ".slvr";
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
		else if(format == SLVRG) {
			fprintf(f_image,"SLVRG\r");
		}
		else if(format == SLVRP) {
			fprintf(f_image,"SLVRP\r");
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

//  =============================== =============================== ===============================
//            =============================== CONVERTER ===============================
//  =============================== =============================== ===============================
Image Image::convertToPGM() const {
	if(format == PGM) {
		return Image(this);
	}
	else if(format == SLVRG) {
		Image imageOut(PGM, name, width, height);
		imageOut.resizeData(width * height);
		
		int Y[width*height];
		
		for(unsigned i=0 ; i < width ; i++) {
			for(unsigned j=0 ; j < height ; j++) {
				int xy = j * width + i;
				Y[xy] = (int)(this->getData(xy) - 128);
			}
		}
		
		unsigned int bloc_dim = 8;
		double A[2];
		double valY, val_cos;
		
		for(unsigned int y=0 ; y < height ; y+=bloc_dim) {
			for(unsigned int x=0 ; x < width ; x+=bloc_dim) {
				
// 				cout << "\rIDCT en cours... " << 100*(y*width+x)/(height*width) << "%" << flush;
				
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
								val_cos = cos((2*i+1)*u*M_PI/(2.0*bloc_dim)) * cos((2*j+1)*v*M_PI/(2.0*bloc_dim));
								
								// ============= Second Quantification =============
								valY += (double)Y[xy2] * val_cos * A[0] * A[1] * (double)quant(i,j,LUMA);
								// =================================================
							}
						}
						valY *= 2 / (double)bloc_dim;
						// ============================================================
if(xy<8)cout<<"valY = "<<(int)Y[xy]<<" -> "<<(int)valY<<endl;

						// ========== Convert to uncompressed RGB ==========
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
	else if(format == SLVRP) {
		Image imageOut(PPM, name, width, height);
		imageOut.resizeData(width * height * 3);
		
		int Y[width*height];
		int Cr[width*height];
		int Cb[width*height];
		
		for(unsigned i=0 ; i < width ; i++) {
			for(unsigned j=0 ; j < height ; j++) {
				int xy = j * width + i;
				Y[xy] = (int)this->getData(xy) - 128;
				Cr[xy] = (int)this->getData(xy + height*width) - 128;
				Cb[xy] = (int)this->getData(xy + 2*height*width) - 128;
			}
		}
		
		unsigned int bloc_dim = 8;
		double A[2];
		double valY, valCr, valCb, val_cos;
		
		for(unsigned int y=0 ; y < height ; y+=bloc_dim) {
			for(unsigned int x=0 ; x < width ; x+=bloc_dim) {
				
// 				cout << "\rIDCT en cours... " << 100*(y*width+x)/(height*width) << "%" << flush;
				
				for(unsigned int u=0 ; u < bloc_dim && u+x < width ; u++) {
					for(unsigned int v=0 ; v < bloc_dim && v+y < height ; v++) {
						
						int xy = (v+y) * width + (u+x);
							
						// ============= Inverse Discret Cosine Transform =============
						valY = valCr = valCb = 0;
						
						for(unsigned int i=0 ; i < bloc_dim && i+x < width ; i++) {
							for(unsigned int j=0 ; j < bloc_dim && j+y < height ; j++) {
								
								int xy2 = (j+y) * width + (i+x);
								A[0] = (i == 0)? 1/sqrt(2) : 1;
								A[1] = (j == 0)? 1/sqrt(2) : 1;
								val_cos = cos((2*i+1)*u*M_PI/(2*bloc_dim)) * cos((2*j+1)*v*M_PI/(2*bloc_dim));
								
								// ============= Second Quantification =============
								valY += (double)Y[xy2] * val_cos * A[0] * A[1] * (double)quant(i,j,LUMA);
								valCr += (double)Cr[xy2] * val_cos * A[0] * A[1] * (double)quant(i,j,REDDIFF);
								valCb += (double)Cb[xy2] * val_cos * A[0] * A[1] * (double)quant(i,j,BLUEDIFF);
								// =================================================
							}
						}
						valY *= 2 / (double)bloc_dim;
						valCr *= 2 / (double)bloc_dim;
						valCb *= 2 / (double)bloc_dim;
						
						valCr = valCb = 128;
						// ============================================================
if(xy<8)cout<<"valY = "<</*(int)Y[xy]<<" -> "<<*/(int)valY<<", valCr = "<</*(int)Cr[xy]<<" -> "<<*/(int)valCr<<", valCb = "<</*(int)Cb[xy]<<" -> "<<*/(int)valCb<<endl;

						// ========== Convert to uncompressed RGB ==========
						imageOut.setData(3*xy, (unsigned char)(max(0.0,min(255.0,( valY + 1.402 * (valCr - 128)))))); //R
						imageOut.setData(3*xy + 1, (unsigned char)(max(0.0,min(255.0,( valY - 0.34414 * (valCb - 128) - 0.71414 * (valCr - 128)))))); //G
						imageOut.setData(3*xy + 2, (unsigned char)(max(0.0,min(255.0,( valY + 1.772 * (valCb - 128)))))); //B
						// =================================================
					}
				}
			}
		}
		cout << "\rIDCT en cours... 100%" << endl;
		
		return imageOut;
	}
}

Image Image::convertToSLVR() const {
	if(format == SLVRG || format == SLVRP) {
		return Image(this);
	}
	else if(format == PPM) {
		Image imageref = new Image(this->convertToPPM());
		Image imageOut(SLVRP, imageref.getName(), imageref.getWidth(), imageref.getHeight());
		imageOut.resizeData(imageref.getWidth() * imageref.getHeight() * 3);
		
		// ========== Convert to compressed YCrCb ==========
		unsigned char Y[width*height];
		unsigned char Cr[width*height];
		unsigned char Cb[width*height];
// 		{
// 			char tmp_Cr[width*height];
// 			char tmp_Cb[width*height];
			
			// Convert RGB to YCrCb
			for(unsigned int j=0 ; j < height ; j++) {
				for(unsigned int i=0 ; i < width ; i++) {
					int xy = j * width + i;
					unsigned char ppm_r = imageref.getData(3*xy);
					unsigned char ppm_g = imageref.getData(3*xy + 1);
					unsigned char ppm_b = imageref.getData(3*xy + 2);
					Y[xy] = (unsigned char)(max(0.0,min(255.0,( 0.299*ppm_r + 0.587*ppm_g + 0.114*ppm_b ))));
					Cr[xy] = (unsigned char)(max(0.0,min(255.0,( 0.5*ppm_r + -0.4187*ppm_g + -0.0813*ppm_b +128 ))));
					Cb[xy] = (unsigned char)(max(0.0,min(255.0,( -0.1687*ppm_r + -0.3313*ppm_g + 0.5*ppm_b +128 ))));
				}
			}
/*
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
*/
		unsigned int bloc_dim = 8;
		double A[2];
		double valY, valCr, valCb, val_cos;
		
		for(unsigned int y=0 ; y < height ; y+=bloc_dim) {
			for(unsigned int x=0 ; x < width ; x+=bloc_dim) {
				
// 				cout << "\rDCT en cours... " << 100*(y*width+x)/(height*width) << "%" << flush;
				
				for(unsigned int u=0 ; u < bloc_dim && u+x < width ; u++) {
					for(unsigned int v=0 ; v < bloc_dim && v+y < height ; v++) {
						
						int xy = (v+y) * width + (u+x);
						
						// ============= Discret Cosine Transform =============
						valY = valCr = valCb = 0;
						A[0] = (u == 0)? 1/sqrt(2) : 1;
						A[1] = (v == 0)? 1/sqrt(2) : 1;
						
						for(unsigned int i=0 ; i < bloc_dim && i+x < width ; i++) {
							for(unsigned int j=0 ; j < bloc_dim && j+y < height ; j++) {
								
								int xy2 = (j+y) * width + (i+x);
								val_cos = cos((2*i+1)*u*M_PI/(2*bloc_dim)) * cos((2*j+1)*v*M_PI/(2*bloc_dim));
								
								valY += (double)Y[xy2] * val_cos;
								valCr += (double)Cr[xy2] * val_cos;
								valCb += (double)Cb[xy2] * val_cos;
							}
						}
						
						valY *= 2*A[0]*A[1] / (double)bloc_dim;
						valCr *= 2*A[0]*A[1] / (double)bloc_dim;
						valCb *= 2*A[0]*A[1] / (double)bloc_dim;
						// ====================================================
						
						// ============= Second Quantification =============
						valY /= (double)quant(u,v,LUMA);
						valCr /= (double)quant(u,v,REDDIFF);
						valCb /= (double)quant(u,v,BLUEDIFF);
						// =================================================
						
if(xy<8)cout<<"valY = "<<(int)Y[xy]<</*" -> "<<(int)valY<<*/", valCr = "<<(int)Cr[xy]<</*" -> "<<(int)valCr<<*/", valCb = "<<(int)Cb[xy]<</*" -> "<<(int)valCb<<*/endl;
						
						imageOut.setData(xy, (unsigned char)((int)valY + 128));
						imageOut.setData(xy + height*width, (unsigned char)((int)valCr + 128));
						imageOut.setData(xy + 2*height*width, (unsigned char)((int)valCb + 128));
					}
				}
			}
		}
		cout << "\rDCT en cours... 100%" << endl;
		
		return imageOut;
	}
	else if(format == PGM) {
		Image imageref = new Image(this->convertToPGM());
		Image imageOut(SLVRG, imageref.getName(), imageref.getWidth(), imageref.getHeight());
		imageOut.resizeData(imageref.getWidth() * imageref.getHeight());
		
		// ========== Convert to compressed YCrCb ==========
		unsigned char Y[width*height];
		
		for(unsigned int j=0 ; j < height ; j++) {
			for(unsigned int i=0 ; i < width ; i++) {
				int xy = j * width + i;
				Y[xy] = imageref.getData(xy);
			}
		}
		
		unsigned int bloc_dim = 8;
		double A[2];
		double valY, val_cos;
		
		for(unsigned int y=0 ; y < height ; y+=bloc_dim) {
			for(unsigned int x=0 ; x < width ; x+=bloc_dim) {
				
// 				cout << "\rDCT en cours... " << 100*(y*width+x)/(height*width) << "%" << flush;
				
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
								val_cos = cos((2*i+1)*u*M_PI/(2.0*bloc_dim)) * cos((2*j+1)*v*M_PI/(2.0*bloc_dim));
								
								valY += (double)Y[xy2] * val_cos;
							}
						}
						
						valY *= 2*A[0]*A[1] / (double)bloc_dim;
						// ====================================================
						
						// ============= Second Quantification =============
						valY /= (double)quant(u,v,LUMA);
						// =================================================
						
if(xy<8)cout<<"valY = "<<(int)Y[xy]<<" -> "<<(int)valY<<endl;
						
						imageOut.setData(xy, (unsigned char)((int)valY + 128));
					}
				}
			}
		}
		cout << "\rDCT en cours... 100%" << endl;
		
		return imageOut;
	}
}

//  =============================== =============================== ===============================
//           =============================== COMPRESSEUR ===============================
//  =============================== =============================== ===============================
int main(int argc, char **argv) {
	string name, name2;
	cout << "Nom de l'image : ";
	cin >> name;
	name = "img/" + name;
	Image imIn(name);
	
	int w = imIn.getWidth(), h = imIn.getHeight();
	int action = -1;
	double psnr = 0;
	Format format;
	
	man();

	while(action != 0) {
		cout << endl << "===== " << name << " =====" << endl;
		cout << endl << "Action : ";
		cin >> action;
		switch(action) {
			case 0 : break;
			case 1 : man(); break;
			case 2 : imIn.load(name); break;
			case 3 : 
				cout << "Nom de l'image : ";
				cin >> name;
				name = "img/" + name;
				imIn.load(name);
				break;
			case 4 : 
				cout << "Nom de l'image à comparer : ";
				cin >> name2;
				name2 = "img/" + name2;
				psnr = imIn.psnr(Image(name2));
				if(psnr == -1) {
					cout << "Erreur : les deux images sont de tailles ou formats différent(e)s" << endl;
				}
				else {
					cout << "Le PSNR entre "<< name << " et " << name2 << " est de " << psnr << endl;
				}
				break;
			case 5 : 
				cout << "Nom de l'image à comparer : ";
				cin >> name2;
				name2 = "img/" + name2;
				psnr = imIn.psnr(Image(name2));
				if(psnr == -1) {
					cout << "Erreur : les deux images sont de tailles ou formats différent(e)s" << endl;
				}
				else {
					cout << "Le PSNR entre "<< name << " et " << name2 << " est de " << psnr << endl;
				}
				break;
			case 6 : imIn.save(name, PGM); break;
			case 7 : imIn.save(name, PPM); break;
			case 8 : imIn.save(name, SLVR); break;
			case 9 : 
				format = imIn.getFormat();
				imIn.save(name, SLVR);
				imIn.load(name+".slvr");
				imIn.save(name+".slvr", format);
				imIn.load(name);
				break;
			default : cout << "Action inconnue" << endl; break;
		}
	}
	
	return 0;
}
