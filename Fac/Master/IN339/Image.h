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
	PGM,
	PNG,
	PPM,
	TGA,
	TIFF
};

enum ChannelID {
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
	vector<unsigned char> data;
} Channel;

class Image {
	private:
		Format format;
		string name;
		unsigned int width = 0;
		unsigned int height = 0;
		bool colored;
		vector<Channel> channels;

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
		bool load(const Image& image);
		bool save(const string filename);
};

//name.substr(name.find_last_of(".")+1, string::npos).compare("ppm") != 0
//string l_name = name.erase(name.find_last_of("."), string::npos)+".RGBc";

