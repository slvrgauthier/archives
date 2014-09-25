#include <iostream>
#include "ImageBase.h"

using namespace std;

ImageBase imIn, imOut1, imOut2;

void dilatation(int degre, char* outname);
void erosion(int degre, char* outname);

int main(int argc, char* argv[]) {
  
  if (argc != 4) {
    printf("Usage: ImageIn.pgm ImageOut.pgm Degre \n"); 
    return 1;
  }
   
  int degre = atoi(argv[3]);
  
  imIn.load(argv[1]);
  imOut1.load(argv[1]);
  imOut2.load(argv[1]);

  erosion(degre,NULL);
  dilatation(degre,argv[2]);

  return 0;

}

void erosion(int degre, char* outname) {

  int w = imIn.getWidth(), h = imIn.getHeight();
	
  for(int x=0;x<w;x++) {
    for(int y=0; y<h;y++) {
      if(!imIn.getColor()) {

        //Image en niveaux de gris
  
        bool change = true;

        for(int i=-degre;i<=degre;i++) {
          for(int j=-degre;j<=degre;j++) {
            if( y+j >= degre && y+j < h-degre && x+i >= degre && x+i < w-degre && imIn[y+j][x+i] > imIn[y][x] ) {
              imOut1[y][x] = imIn[y+j][x+i];
              change = false;
            }
          }
        }

        if(change) {
          imOut1[y][x] = imIn[y][x];
        }

      }

      else {

        //Image en couleur RGB

        bool changeR = true, changeG = true, changeB = true;

        for(int i=-degre;i<=degre;i++) {
          for(int j=-degre;j<=degre;j++) {
            if(y+j >= degre && y+j < h-degre && x+i >= degre && x+i < w-degre) {
              if(imIn[3*(y+j)][3*(x+i)] > imIn[3*y][3*x]) {
                imOut1[3*y][3*x] = imIn[3*(y+j)][3*(x+i)];
                changeR = false;
              }
              if(imIn[3*(y+j)][3*(x+i)+1] > imIn[3*y][3*x+1]) {
                imOut1[3*y][3*x+1] = imIn[3*(y+j)][3*(x+i)+1];
                changeG = false;
              }
              if(imIn[3*(y+j)][3*(x+i)+2] > imIn[3*y][3*x+2]) {
                imOut1[3*y][3*x+2] = imIn[3*(y+j)][3*(x+i)+2];
                changeB = false;
              }
            }
          }
        }

        if(changeR) {
          imOut1[3*y][3*x] = imIn[3*y][3*x];
        }
        if(changeG) {
          imOut1[3*y][3*x+1] = imIn[3*y][3*x+1];
        }
        if(changeB) {
          imOut1[3*y][3*x+2] = imIn[3*y][3*x+2];
        }
      }
    }
  }

  if(outname != NULL) imOut1.save(outname);
}

void dilatation(int degre, char* outname) {

  int w = imIn.getWidth(), h = imIn.getHeight();
	
  for(int x=0;x<w;x++) {
    for(int y=0; y<h;y++) {
      if(!imIn.getColor()) {

        //Image en niveaux de gris
  
        bool change = true;

        for(int i=-degre;i<=degre;i++) {
          for(int j=-degre;j<=degre;j++) {
            if( y+j >= degre && y+j < h-degre && x+i >= degre && x+i < w-degre && imOut1[y+j][x+i] < imOut1[y][x] ) {
              imOut2[y][x] = imOut1[y+j][x+i];
              change = false;
            }
          }
        }

        if(change) {
          imOut2[y][x] = imOut1[y][x];
        }

      }

      else {

        //Image en couleur RGB

        bool changeR = true, changeG = true, changeB = true;

        for(int i=-degre;i<=degre;i++) {
          for(int j=-degre;j<=degre;j++) {
            if(y+j >= degre && y+j < h-degre && x+i >= degre && x+i < w-degre) {
              if(imOut1[3*(y+j)][3*(x+i)] < imOut1[3*y][3*x]) {
                imOut2[3*y][3*x] = imOut1[3*(y+j)][3*(x+i)];
                changeR = false;
              }
              if(imOut1[3*(y+j)][3*(x+i)+1] < imOut1[3*y][3*x+1]) {
                imOut2[3*y][3*x+1] = imOut1[3*(y+j)][3*(x+i)+1];
                changeG = false;
              }
              if(imOut1[3*(y+j)][3*(x+i)+2] < imOut1[3*y][3*x+2]) {
                imOut2[3*y][3*x+2] = imOut1[3*(y+j)][3*(x+i)+2];
                changeB = false;
              }
            }
          }
        }

        if(changeR) {
          imOut2[3*y][3*x] = imOut1[3*y][3*x];
        }
        if(changeG) {
          imOut2[3*y][3*x+1] = imOut1[3*y][3*x+1];
        }
        if(changeB) {
          imOut2[3*y][3*x+2] = imOut1[3*y][3*x+2];
        }
      }
    }
  }

  if(outname != NULL) imOut2.save(outname);
}
