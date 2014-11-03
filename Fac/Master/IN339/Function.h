#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>

using namespace std;

Image toDiff(Image* image) {
	Image imageOut(image);
	if(image->getFormat() == PGM) {
		int w = image->getWidth(), h = image->getHeight();
		for(unsigned int j=1 ; j < h ; j++) {
			int xy = j * w;
			imageOut.setData(xy, image->getData(xy) - image->getData(xy - w) + 128);
		}
		for(unsigned int i=1 ; i < w ; i++) {
			int xy = i;
			imageOut.setData(xy, image->getData(xy) - image->getData(xy - 1) + 128);
		}
		for(unsigned int j=1 ; j < h ; j++) {
			for(unsigned int i=1 ; i < w ; i++) {
				int xy = j * w + i;
				imageOut.setData(xy, image->getData(xy) - (image->getData(xy - 1) + image->getData(xy - w)) / 2 + 128);
			}
		}
	}
	else {
		cout << "Format incompatible avec la différence." << endl;
	}
	
	return imageOut;
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

Image spreadSpectrumIn(Image* image, string key, int alpha, string message) {
	Image imageOut(image);
	unsigned int length = image->getLength(), counter = 0;
	for(unsigned int i=0 ; i < length ; i++) {
		if(key[i%key.size()] == '1') {
			// wr = 1
			if(message[counter] == '1') {
				// wm = wr
				imageOut.setData(i, image->getData(i) + alpha);
			}
			else {
				// wm = -wr
				imageOut.setData(i, image->getData(i) - alpha);
			}
		}
// 		else {
			// wr = 0 et wm = 0
// 			imageOut.setData(i, image->getData(i));
// 		}
		if(i%8 == 0) {
			counter = (counter+1)%message.size();
		}
	}
	
	return imageOut;
}

bitset<8> spreadSpectrumOut(Image* image, bitset<8> key, int alpha) {
	Image imageOut(image);
	unsigned int length = image->getLength(), counter = 0;
	bitset<8> message;
	for(unsigned int i=0 ; i < length ; i++) {
		if(key[i%key.size()] == 1) {
			// wr = 1
			if(message[counter] == 1) {
				// wm = wr
				imageOut.setData(i, image->getData(i) + alpha * message[counter]);
			}
			else {
				// wm = -wr
				imageOut.setData(i, image->getData(i) - alpha * message[counter]);
			}
		}
		else {
			// wr = 0 et wm = 0
			imageOut.setData(i, image->getData(i));
		}
		if(i%8 == 0) {
			counter = (counter+1)%message.size();
		}
	}
	
	return message;
}

#endif
