#include <iostream>
#include "ImageBase.h"

using namespace std;

int main(int argc, char* argv[]) {
  
  if (argc != 4) {
    printf("Usage: ImageIn1.pgm ImageIn2.pgm ImageOut.pgm\n"); 
    return 1;
  }

  ImageBase imIn1, imIn2, imOut;
  imIn1.load(argv[1]);
  imIn2.load(argv[2]);
  imOut.load(argv[1]);

  if(imIn1.getWidth() != imIn2.getWidth() || imIn1.getHeight() != imIn2.getHeight()) {
    printf("Usage : ImageIn1.pgm et ImageIn2.pgm doivent etre de taille identique\n");
    return 2;
  }

  int w = imIn1.getWidth(), h = imIn1.getHeight();
  for(int x=0;x<w;x++) {
    for(int y=0; y<h;y++) {
      if(imIn1[y][x] == 255 && imIn2[y][x] == 0) imOut[y][x] = 0;
      else imOut[y][x] = 255;
    }
  }

  imOut.save(argv[3]);

  return 0;
}

