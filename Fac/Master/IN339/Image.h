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
	JPEG,
	JPEG2000,
	PBM,
	PGM,
	PNG,
	PPM,
	TGA,
	TIFF,
	
	RGBC,
	YCCC
};

enum ChannelID {
	BINARY,
	GREY,
	RED,
	GREEN,
	BLUE,
	LUMA,
	BLUEDIFF,
	REDDIFF
};

typedef struct Channel {
	ChannelID id;
	bool compressed;
} Channel;

class Image {
	private:
		Format format;
		string name;
		unsigned int width;
		unsigned int height;
		bool colored;
		vector<Channel> channels;
		unsigned char* data;

	public:
		Image(const string filename);
		Image(const Image& image);
		~Image();

		Format getFormat() const;
		string getName() const;
		unsigned int getWidth() const;
		unsigned int getHeight() const;
		bool isColored();
		vector<ChannelID> getChannels() const;
		unsigned char getPixel(ChannelID channel, unsigned int x, unsigned int y) const;
		void setPixel(ChannelID channel, unsigned int x, unsigned int y, unsigned char value);

		bool load(const string filename);
		bool save(const string filename, Format fileformat);
		
	private:
		bool load_ppm(string filename);
		bool save_ppm(string filename);
		Image& convertToPPM();
};

//name.substr(name.find_last_of(".")+1, string::npos).compare("ppm") != 0
//string l_name = name.erase(name.find_last_of("."), string::npos)+".RGBc";

#endif
