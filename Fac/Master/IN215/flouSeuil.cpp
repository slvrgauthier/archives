#include <iostream>
#include "ImageBase.h"

using namespace std;

int main(int argc, char* argv[]) {
  
  if (argc != 5) {
    printf("Usage: ImageIn.ppm ImageSeuil.pgm ImageOut.ppm Degre\n"); 
    return 1;
  }

  ImageBase imIn, imSe, imOut;
  imIn.load(argv[1]);
  imSe.load(argv[2]);
  imOut.load(argv[1]);

  int w = imIn.getWidth(), h = imIn.getHeight();
  for(int x=0;x<w;x++) {
    for(int y=0; y<h;y++) {
      if(imSe[y][x] == 255) {
        int tmpR = imIn[3*y][3*x], tmpG = imIn[3*y][3*x+1], tmpB = imIn[3*y][3*x+2], cpt = 1;
        for(int degre=1;degre<=atoi(argv[4]);degre++) {
          if(x > degre-1 && y > degre-1) { 
            tmpR += imIn[3*(y-degre)][3*(x-degre)];
            tmpG += imIn[3*(y-degre)][3*(x-degre)+1];
            tmpB += imIn[3*(y-degre)][3*(x-degre)+2];
            cpt++;
          }
          if(y > degre-1) {
            tmpR += imIn[3*(y-degre)][3*x];
            tmpG += imIn[3*(y-degre)][3*x+1];
            tmpB += imIn[3*(y-degre)][3*x+2];
            cpt++;
          }
          if(x < w-degre && y > degre-1) {
            tmpR += imIn[3*(y-degre)][3*(x+degre)];
            tmpG += imIn[3*(y-degre)][3*(x+degre)+1];
            tmpB += imIn[3*(y-degre)][3*(x+degre)+2];
            cpt++;
          }
          if(x > degre-1) {
            tmpR += imIn[3*y][3*(x-degre)];
            tmpG += imIn[3*y][3*(x-degre)+1];
            tmpB += imIn[3*y][3*(x-degre)+2];
            cpt++;
          }
          if(x < w-degre) {
            tmpR += imIn[3*y][3*(x+degre)];
            tmpG += imIn[3*y][3*(x+degre)+1];
            tmpB += imIn[3*y][3*(x+degre)+2];
            cpt++;
          }
          if(x > degre-1 && y < h-degre) {
            tmpR += imIn[3*(y+degre)][3*(x-degre)];
            tmpG += imIn[3*(y+degre)][3*(x-degre)+1];
            tmpB += imIn[3*(y+degre)][3*(x-degre)+2];
            cpt++;
          }
          if(y < h-degre) {
            tmpR += imIn[3*(y+degre)][3*x];
            tmpG += imIn[3*(y+degre)][3*x+1];
            tmpB += imIn[3*(y+degre)][3*x+2];
            cpt++;
          }
          if(x < w-degre && y < h-degre) {
            tmpR += imIn[3*(y+degre)][3*(x+degre)];
            tmpG += imIn[3*(y+degre)][3*(x+degre)+1];
            tmpB += imIn[3*(y+degre)][3*(x+degre)+2];
            cpt++;
          }
        }
            
        imOut[3*y][3*x] = (char)(tmpR/cpt);
        imOut[3*y][3*x+1] = (char)(tmpG/cpt);
        imOut[3*y][3*x+2] = (char)(tmpB/cpt);
      }
    }
  }
  
  imOut.save(argv[3]);

  return 0;
}

