#include "Image.h"
#include <iostream>
#include <string>

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

int main(int argc, char **argv) {
	string name, name2;
	cout << "Nom de l'image : ";
	cin >> name;
	name = "img/" + name;
	Image imIn(name);
	//Image imOut(imIn);
	
	int w = imIn.getWidth(), h = imIn.getHeight();
	int action = -1;
	double psnr = -1;

	while(action != 0) {
		cout << endl << "===== " << name << " =====" << endl;
		cout << "Mode d'emploi :"<< endl;
		cout << "0 : Quitter" << endl;
		cout << "1 : Changer d'image" << endl;
		cout << "2 : Calculer le PSNR" << endl;
		cout << "3 : Compresser l'image en RGBc" << endl;
		cout << "4 : Compresser l'image en YCCc" << endl;
		cout << "5 : Convertir l'image en PGM" << endl;
		cout << "6 : Convertir l'image en PPM" << endl;
		cout << "7 : Faire une différence" << endl;
		cout << "===== " << name << " =====" << endl;

		cout << endl << "Action : ";
		cin >> action;
		switch(action) {
			case 0 : break;
			case 1 : 
				cout << "Nom de l'image : ";
				cin >> name;
				name = "img/" + name;
				imIn.load(name);
				//imOut.load(name);
				break;
			case 2 : 
				cout << "Nom de l'image à comparer : ";
				cin >> name2;
				name2 = "img/" + name2;
				psnr = imIn.psnr(Image(name2));
				if(psnr == -1) {
					cout << "Erreur : les deux images sont de tailles ou formats différent(e)s" << endl;
				}
				else {
					cout << "Le PSNR entre "<< name << " et " << name2 << " est de " << psnr << endl;
				}
				break;
			case 3 : imIn.save(name, RGBC); break;
			case 4 : imIn.save(name, YCCC); break;
			case 5 : imIn.save(name, PGM); break;
			case 6 : imIn.save(name, PPM); break;
			case 7 : toDiff(&imIn).save(name, PGM); break;
			default : cout << "Action inconnue" << endl; break;
		}
	}
	
	return 0;
}
