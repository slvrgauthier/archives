#include <iostream>
#include "ImageBase.h"

using namespace std;

int main(int argc, char* argv[]) {
  
  if (argc != 3) {
    printf("Usage: ImageIn.ppm ImageOut.pgm\n"); 
    return 1;
  }

  ImageBase imIn;
  imIn.load(argv[1]);

  int w = imIn.getWidth(), h = imIn.getHeight();
  ImageBase imOut(w,h,false);
  for(int x=0;x<w;x++) {
    for(int y=0; y<h;y++) {
      imOut[y][x] = (char)(0.299*imIn[3*y][3*x]+0.587*imIn[3*y][3*x+1]+0.114*imIn[3*y][3*x+2]);
    }
  }
  
  imOut.save(argv[2]);

  return 0;
}

