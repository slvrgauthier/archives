#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

enum Format {
	BMP,
	GIF,
	JPG,
	PBM,
	PGM,
	PNG,
	PPM,
	TGA,
	TIF,
	
	RGBC,
	YCCC
};

enum Channel {
	BINARY,
	GREY,
	RED,
	GREEN,
	BLUE,
	LUMA,
	REDDIFF,
	BLUEDIFF
};

class Image {
	private:
		Format format;
		string name;
		unsigned int width;
		unsigned int height;
		bool colored;
		vector<Channel> channels;
		unsigned int length;
		unsigned char* data;

	public:
		Image(const string filename);
		Image(Format f, string n, unsigned int w, unsigned int h, bool c, vector<Channel> C);
		Image(const Image* image);
		~Image();

		Format getFormat() const;
		string getName() const;
		unsigned int getWidth() const;
		unsigned int getHeight() const;
		bool isColored() const;
		vector<Channel> getChannels() const;
		unsigned int getLength() const;
		unsigned char getData(int i) const;
		void setData(int i, unsigned char value);

		bool load(const string filename);
		bool save(const string filename, Format fileformat) const;
		
		void resizeData(unsigned int length);
		
	private:
		bool load_(string filename);
		bool save_(string filename) const;
		
		Image convertToPGM() const;
		Image convertToPPM() const;
		Image convertToRGBC() const;
		Image convertToYCCC() const;
};

#endif
