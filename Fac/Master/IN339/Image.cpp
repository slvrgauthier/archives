#include "Image.h"
#include "Load.h"
#include "Save.h"
#include "Convert.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define MAX_INT 65536  // 2^16

using namespace std;

Image::Image(const string filename) { load(filename); }
Image::Image(const Image& image) {/* TODO */}
Image::~Image() {/* TODO */}

Format Image::getFormat() const { return format; }
string Image::getName() const { return name; }
unsigned int Image::getWidth() const { return width; }
unsigned int Image::getHeight() const { return height; }
bool Image::isColored() { return colored; }
vector<ChannelID> Image::getChannels() const {
	vector<ChannelID> ids;
	for(unsigned int i=0 ; i < channels.size() ; i++) {
		ids.push_back(channels[i].id);
	}
	return ids;
}
unsigned char Image::getPixel(ChannelID channel, unsigned int x, unsigned int y) const {
	unsigned int i=0;
	while(i < channels.size()) {
		if(channels[i].id == channel) {
			//return channels[i].data[ y * width + x];
		}
		i++;
	}
	return 0; // channel don't exist
}
void Image::setPixel(ChannelID channel, unsigned int x, unsigned int y, unsigned char value) {
	unsigned int i=0;
	while(i < channels.size()) {
		if(channels[i].id == channel) {
			//channels[i].data[ y * width + x] = value;
			i = channels.size();
		}
		i++;
	}
}

bool Image::load(const string filename) {
	ifstream is(filename.c_str());
	if(!is) {
		return false;
	}
	
	string keyWord;
	is >> keyWord;
	is.close();
	
	if(keyWord.compare("P6") == 0) {
		format = PPM;
		return load_ppm(filename);
	}
	else {
		return false;
	}
}

bool Image::save(const string filename, Format fileformat) {
	if(fileformat == PPM) {
		if(format == PPM) {
			return save_ppm(filename);
		}
		else {
			return convertToPPM().save_ppm(filename);
		}
	}
	else {
		return false;
	}
}
