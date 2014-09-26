#include "Image.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

Image::Image(const string filename) {}
Image::Image(const Image& image) {}
Image::~Image() {}

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
			return channels[i].data[ y * width + x];
		}
		i++;
	}
	return 0; // channel don't exist
}
void Image::setPixel(ChannelID channel, unsigned int x, unsigned int y, unsigned char value) {
	unsigned int i=0;
	while(i < channels.size()) {
		if(channels[i].id == channel) {
			channels[i].data[ y * width + x] = value;
			i = channels.size();
		}
		i++;
	}
}

bool Image::load(const string filename) {}
bool Image::load(const Image& image) {}
bool Image::save(const string filename) {}

