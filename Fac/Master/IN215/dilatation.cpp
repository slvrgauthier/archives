#include <iostream>
#include "ImageBase.h"

using namespace std;

int main(int argc, char* argv[]) {
  
  if (argc != 4) {
    printf("Usage: ImageIn.pgm ImageOut.pgm Degre \n"); 
    return 1;
  }
   
  int degre = atoi(argv[3]);
  
  ImageBase imIn, imOut;
  imIn.load(argv[1]);
  imOut.load(argv[1]);

  int w = imIn.getWidth(), h = imIn.getHeight();
	
  for(int x=0;x<w;x++) {
    for(int y=0; y<h;y++) {
      if(!imIn.getColor()) {

        //Image en niveaux de gris
  
        bool change = true;

        for(int i=-degre;i<=degre;i++) {
          for(int j=-degre;j<=degre;j++) {
            if( y+j >= degre && y+j < h-degre && x+i >= degre && x+i < w-degre && imIn[y+j][x+i] < imIn[y][x] ) {
              imOut[y][x] = imIn[y+j][x+i];
              change = false;
            }
          }
        }

        if(change) {
          imOut[y][x] = imIn[y][x];
        }

      }

      else {

        //Image en couleur RGB

        bool changeR = true, changeG = true, changeB = true;

        for(int i=-degre;i<=degre;i++) {
          for(int j=-degre;j<=degre;j++) {
            if(y+j >= degre && y+j < h-degre && x+i >= degre && x+i < w-degre) {
              if(imIn[3*(y+j)][3*(x+i)] < imIn[3*y][3*x]) {
                imOut[3*y][3*x] = imIn[3*(y+j)][3*(x+i)];
                changeR = false;
              }
              if(imIn[3*(y+j)][3*(x+i)+1] < imIn[3*y][3*x+1]) {
                imOut[3*y][3*x+1] = imIn[3*(y+j)][3*(x+i)+1];
                changeG = false;
              }
              if(imIn[3*(y+j)][3*(x+i)+2] < imIn[3*y][3*x+2]) {
                imOut[3*y][3*x+2] = imIn[3*(y+j)][3*(x+i)+2];
                changeB = false;
              }
            }
          }
        }

        if(changeR) {
          imOut[3*y][3*x] = imIn[3*y][3*x];
        }
        if(changeG) {
          imOut[3*y][3*x+1] = imIn[3*y][3*x+1];
        }
        if(changeB) {
          imOut[3*y][3*x+2] = imIn[3*y][3*x+2];
        }

      }
    }
  }

  imOut.save(argv[2]);

  return 0;
}

