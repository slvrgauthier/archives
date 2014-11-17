// INCLUDES
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <math.h>
#include "huffman.h"

#define TEST false

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

double taux(string path1, string path2) {
	long size1, size2;
	{
		ifstream is(path1.c_str());
		if(!is) {
			return 0.0;
		}
		long pos = is.tellg(); 
		is.seekg( 0 , std::ios_base::end ); 
		size1 = is.tellg() ;
	}
	{
		ifstream is(path2.c_str());
		if(!is) {
			return 0.0;
		}
		long pos = is.tellg(); 
		is.seekg( 0 , std::ios_base::end ); 
		size2 = is.tellg() ;
	}
	
    return (double)size1/(double)size2;
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
		
		int Y[width][height];
		for(unsigned i=0 ; i < width ; i++) {
			for(unsigned j=0 ; j < height ; j++) {
				Y[i][j] = ((int)this->getData(j * width + i) - 128) * quant(i%8,j%8,LUMA);
			}
		}
		
		double COS[8][8], C[8], valY;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++)
				COS[i][j] = cos((2 * i + 1) * j * acos(-1) / 16.0);
			if (i) C[i] = 1;
			else C[i] = 1 / sqrt(2);
		}
		
		for(unsigned int r=0 ; r < width/8 ; r++) {
			for(unsigned int c=0 ; c < height/8 ; c++) {
				
				cout << "\rIDCT en cours... " << 100*(c*width+r)/(height*width) << "%" << flush;
				
				for(unsigned int x=0 ; x < 8 ; x++) {
					for(unsigned int y=0 ; y < 8 ; y++) {
						valY = 0;
						for(unsigned int i=0 ; i < 8 ; i++) {
							for(unsigned int j=0 ; j < 8 ; j++) {
								valY += Y[r*8+i][c*8+j] * COS[x][i] * COS[y][j] * C[i] * C[j];
							}
						}
						valY *= 0.25;
						imageOut.setData((c*8+y) * width + (r*8+x), (unsigned char)(max(0,min(255,(int)valY))));
					}
				}
			}
		}
		cout << "\rIDCT en cours... 100%" << endl;
		
		if(TEST) {
			for(unsigned int j=0;j<8;j++) {
				for(unsigned int i=0;i<8;i++) {
					cout<<setw(3)<<(int)Y[i][j]<<" ";
				}
				cout<<"   ";
				for(unsigned int i=0;i<8;i++) {
					cout<<setw(3)<<(int)imageOut.getData(j*width+i)<<" ";
				}
				cout<<endl;
			}
		}
		
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
		
		int Y[width][height], Cr[width][height], Cb[width][height];
		for(unsigned i=0 ; i < width ; i++) {
			for(unsigned j=0 ; j < height ; j++) {
				unsigned int xy = j * width + i;
				unsigned int xyc = j/2 * width/2 + i/2;
				Y[i][j] = ((int)this->getData(j * width + i) - 128) * quant(i%8,j%8,LUMA);
				Cr[i][j] = ((int)this->getData(xy + height*width) - 128) * quant(i%8,j%8,REDDIFF);
				Cb[i][j] = ((int)this->getData(xy + 8*height*width/4) - 128) * quant(i%8,j%8,BLUEDIFF);
			}
		}
		
		double COS[8][8], C[8], valY, valCr, valCb;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++)
				COS[i][j] = cos((2 * i + 1) * j * acos(-1) / 16.0);
			if (i) C[i] = 1;
			else C[i] = 1 / sqrt(2);
		}
		
		for(unsigned int r=0 ; r < height/8 ; r++) {
			for(unsigned int c=0 ; c < width/8 ; c++) {
				
				cout << "\rIDCT en cours... " << 100*(r*width*8+c)/(height*width) << "%" << flush;
				
				for(unsigned int x=0 ; x < 8 ; x++) {
					for(unsigned int y=0 ; y < 8 ; y++) {
						valY = valCr = valCb = 0;
						for(unsigned int i=0 ; i < 8 ; i++) {
							for(unsigned int j=0 ; j < 8 ; j++) {
								valY += Y[r*8+i][c*8+j] * COS[x][i] * COS[y][j] * C[i] * C[j];
								valCr += Cr[r*8+i][c*8+j] * COS[x][i] * COS[y][j] * C[i] * C[j];
								valCb += Cb[r*8+i][c*8+j] * COS[x][i] * COS[y][j] * C[i] * C[j];
							}
						}
						valY *= 0.25;
						valCr *= 0.25;
						valCb *= 0.25;
						unsigned int xy = (r*8+y) * width + (c*8+x);
						imageOut.setData(3*xy, (unsigned char)(max(0.0,min(255.0,( valY + 1.402 * (valCr-128) ))))); //R
						imageOut.setData(3*xy + 1, (unsigned char)(max(0.0,min(255.0,( valY - 0.34414 * (valCb-128) - 0.71414 * (valCr-128) ))))); //G
						imageOut.setData(3*xy + 2, (unsigned char)(max(0.0,min(255.0,( valY + 1.772 * (valCb-128) ))))); //B
					}
				}
			}
		}
		cout << "\rIDCT en cours... 100%" << endl;
		
		if(TEST) {
			for(unsigned int j=0;j<8;j++) {
				for(unsigned int i=0;i<8;i++) {
					cout<<setw(3)<<(int)Y[i][j]<<" ";
				}
				cout<<"   ";
				for(unsigned int i=0;i<8;i++) {
					cout<<setw(3)<<(int)imageOut.getData(j*width+i)<<" ";
				}
				cout<<endl;
			}
		}
		
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
		
		unsigned char Y[width][height], Cr[width][height], Cb[width][height];
		{
			unsigned char tmp_Cr[width][height];
			unsigned char tmp_Cb[width][height];
			
			// Convert RGB to YCrCb
			for(unsigned int j=0 ; j < height ; j++) {
				for(unsigned int i=0 ; i < width ; i++) {
					int xy = j * width + i;
					unsigned char ppm_r = imageref.getData(3*xy);
					unsigned char ppm_g = imageref.getData(3*xy + 1);
					unsigned char ppm_b = imageref.getData(3*xy + 2);
					Y[i][j] = (unsigned char)(max(0.0,min(255.0,( 0.299*ppm_r + 0.587*ppm_g + 0.114*ppm_b ))));
					tmp_Cr[i][j] = (unsigned char)(max(0.0,min(255.0,( 0.5*ppm_r + -0.4187*ppm_g + -0.0813*ppm_b +128 ))));
					tmp_Cb[i][j] = (unsigned char)(max(0.0,min(255.0,( -0.1687*ppm_r + -0.3313*ppm_g + 0.5*ppm_b +128 ))));
				}
			}

			// Compress Cr and Cb with mean
			for(unsigned int j=0 ; j < height ; j+=2) {
				for(unsigned int i=0 ; i < width ; i+=2) {
					int val_cr = tmp_Cr[i][j];
					int val_cb = tmp_Cb[i][j];
					int count = 1;
					if(i < width-1) {
						val_cr += tmp_Cr[i+1][j];
						val_cb += tmp_Cb[i+1][j];
						count++;
					}
					if(j < height-1) {
						val_cr += tmp_Cr[i][j+1];
						val_cb += tmp_Cb[i][j+1];
						count++;
					}
					if(j < height-1 && i < width-1) {
						val_cr += tmp_Cr[i+1][j+1];
						val_cb += tmp_Cb[i+1][j+1];
						count++;
					}
					Cr[i][j] = (unsigned char)(val_cr / count);
					Cr[i+1][j] = (unsigned char)(val_cr / count);
					Cr[i][j+1] = (unsigned char)(val_cr / count);
					Cr[i+1][j+1] = (unsigned char)(val_cr / count);
					Cb[i][j] = (unsigned char)(val_cb / count);
					Cb[i+1][j] = (unsigned char)(val_cb / count);
					Cb[i][j+1] = (unsigned char)(val_cb / count);
					Cb[i+1][j+1] = (unsigned char)(val_cb / count);
				}
			}
		}
		// =================================================
		
		// ============= First Quantification =============
/*		unsigned char mask = 255;
		for(unsigned int i=0 ; i < width ; i++) {
			for(unsigned int j=0 ; j < height ; j++) {
				Y[i][j] = Y[i][j] & mask;
				Cr[i][j] = Cr[i][j] & mask;
				Cb[i][j] = Cb[i][j] & mask;
			}
		}*/
		// ================================================

		
		double COS[8][8], C[8], valY, valCr, valCb;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++)
				COS[i][j] = cos((2 * i + 1) * j * acos(-1) / 16.0);
			if (i) C[i] = 1;
			else C[i] = 1 / sqrt(2);
		}
		
		for(unsigned int r=0 ; r < height/8 ; r++) {
			for(unsigned int c=0 ; c < width/8 ; c++) {
				
				cout << "\rDCT en cours... " << 100*(r*width*8+c)/(height*width) << "%" << flush;
				
				for(unsigned int i=0 ; i < 8 ; i++) {
					for(unsigned int j=0 ; j < 8 ; j++) {
						valY = valCr = valCb = 0;
						for(unsigned int x=0 ; x < 8 ; x++) {
							for(unsigned int y=0 ; y < 8 ; y++) {
								valY += (Y[r*8+x][c*8+y]) * COS[x][i] * COS[y][j];
								valCr += (Cr[r*8+x][c*8+y]) * COS[x][i] * COS[y][j];
								valCb += (Cb[r*8+x][c*8+y]) * COS[x][i] * COS[y][j];
							}
						}
						valY *= C[i]*C[j]*0.25/(double)quant(i,j,LUMA);
						valCr *= C[i]*C[j]*0.25/(double)quant(i,j,REDDIFF);
						valCb *= C[i]*C[j]*0.25/(double)quant(i,j,BLUEDIFF);
						unsigned int xy = (r*8+j) * width + (c*8+i); 
						unsigned int xyc = (r*8+j)/2 * width/2 + (c*8+i)/2; 
						imageOut.setData(xy, (unsigned char)(max(0,min(255,(int)valY+128))));
						imageOut.setData(xy + height*width, (unsigned char)(max(0,min(255,(int)valCr+128))));
						imageOut.setData(xy + 8*height*width/4, (unsigned char)(max(0,min(255,(int)valCb+128))));
					}
				}
			}
		}
		cout << "\rDCT en cours... 100%" << endl;
		
		if(TEST) {
			for(unsigned int j=0;j<8;j++) {
				for(unsigned int i=0;i<8;i++) {
					cout<<setw(3)<<(int)Y[i][j]<<" ";
				}
				cout<<"   ";
				for(unsigned int i=0;i<8;i++) {
					cout<<setw(3)<<(int)imageOut.getData(j*width+i)-128<<" ";
				}
				cout<<endl;
			}
		}
		
		return imageOut;
	}
	else if(format == PGM) {
		Image imageref = new Image(this->convertToPGM());
		Image imageOut(SLVRG, imageref.getName(), imageref.getWidth(), imageref.getHeight());
		imageOut.resizeData(imageref.getWidth() * imageref.getHeight());
		
		unsigned char Y[width][height];
		for(unsigned int j=0 ; j < height ; j++) {
			for(unsigned int i=0 ; i < width ; i++) {
				Y[i][j] = imageref.getData(j * width + i);
			}
		}
		
		double COS[8][8], C[8], valY;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++)
				COS[i][j] = cos((2 * i + 1) * j * acos(-1) / 16.0);
			if (i) C[i] = 1;
			else C[i] = 1 / sqrt(2);
		}
		
		for(unsigned int r=0 ; r < width/8 ; r++) {
			for(unsigned int c=0 ; c < height/8 ; c++) {
				
				cout << "\rDCT en cours... " << 100*(c*width+r)/(height*width) << "%" << flush;
				
				for(unsigned int i=0 ; i < 8 ; i++) {
					for(unsigned int j=0 ; j < 8 ; j++) {
						valY = 0;
						for(unsigned int x=0 ; x < 8 ; x++) {
							for(unsigned int y=0 ; y < 8 ; y++) {
								valY += (Y[r*8+x][c*8+y]) * COS[x][i] * COS[y][j];
							}
						}
						valY *= C[i]*C[j]*0.25/(double)quant(i,j,LUMA);
						imageOut.setData((c*8+j) * width + (r*8+i), (unsigned char)(max(0,min(255,(int)valY+128))));
					}
				}
			}
		}
		cout << "\rDCT en cours... 100%" << endl;
		
		if(TEST) {
			for(unsigned int j=0;j<8;j++) {
				for(unsigned int i=0;i<8;i++) {
					cout<<setw(3)<<(int)Y[i][j]<<" ";
				}
				cout<<"   ";
				for(unsigned int i=0;i<8;i++) {
					cout<<setw(3)<<(int)imageOut.getData(j*width+i)-128<<" ";
				}
				cout<<endl;
			}
		}
		
		return imageOut;
	}
}

//  =============================== =============================== ===============================
//           =============================== COMPRESSEUR ===============================
//  =============================== =============================== ===============================
int main(int argc, char **argv) {
	bool loaded = false;
	string name, name2;
	Image imIn("");
	
	while(!loaded) {
		cout << "Nom de l'image : ";
		cin >> name;
		name = "img/" + name;
		loaded = imIn.load(name);
		if(!loaded) cout<<"Erreur de chargement de l'image."<<endl;
	}
	
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
				loaded = false;
				while(!loaded) {
					cout << "Nom de l'image : ";
					cin >> name;
					name = "img/" + name;
					loaded = imIn.load(name);
					if(!loaded) cout<<"Erreur de chargement de l'image."<<endl;
				}
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
				cout << "Le taux de compression entre "<< name << " et " << name2 << " est de " << taux(name,name2) << endl;
				break;
			case 6 : imIn.save(name, PGM); break;
			case 7 : imIn.save(name, PPM); break;
			case 8 : imIn.save(name, SLVR); break;
			case 9 : 
				format = imIn.getFormat();
				if(format != PGM && format != PPM) {
					cout<<"Ce projet ne prend pas en charge le format de l'image"<<endl;
				}
				else {
					imIn.save(name, SLVR);
					imIn.load(name+".slvr");
					imIn.save(name+".slvr", format);
					imIn.load(name);
					if(format == PGM) {
						name2 = name+".slvr.pgm";
					}
					else {
						name2 = name+".slvr.ppm";
					}
					psnr = imIn.psnr(Image(name2));
					if(psnr == -1) {
						cout << "Erreur : les deux images sont de tailles ou formats différent(e)s" << endl;
					}
					else {
						cout << "Le PSNR entre "<< name << " et " << name2 << " est de " << psnr << endl;
					}
					name2 = name+".slvr.huff";
					const char* args[4] = {"huffman_main","c",(name+".slvr").c_str(),name2.c_str()};
					huffman_main(4,args);
					cout << "Le taux de compression entre "<< name << " et " << name2 << " est de " << taux(name,name2) << endl;
				}
				break;
			default : cout << "Action inconnue" << endl; break;
		}
	}
	
	return 0;
}
