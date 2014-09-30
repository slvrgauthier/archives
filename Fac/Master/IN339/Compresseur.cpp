#include "Image.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
	if(argc != 2) {
		cout << "Usage: Compresseur Image\n" << endl; 
		return 1;
	}

	string name(argv[1]);
	Image imIn(name);
	Image imOut(imIn);

	int w = imIn.getWidth(), h = imIn.getHeight();
	int action = -1;
	bool psnr = false, ratio = false;

	while(action != 0) {
		cout << "Mode d'emploi :"<< endl;
		cout << "0 : Quitter" << endl;
		cout << "1 : Activer / Désactiver le PSNR" << endl;
		cout << "2 : Activer / Désactiver le Taux de compression" << endl;
		cout << "3 : Compresser l'image en RGBc" << endl;
		cout << "4 : Compresser l'image en YCCc" << endl;
		cout << "5 : Convertir l'image en PPM" << endl;
		cout << "6 : Changer d'image" << endl;

		cout << endl << "Action : ";
		cin >> action;
		switch(action) {
			case 0 : break;
			case 1 : psnr = !psnr;
				if(psnr) 
					cout << "PSNR activé.";
				else
					cout << "PSNR désactivé.";
				cout << endl;
				break;
			case 2 : ratio = !ratio;
				if(ratio) 
					cout << "Taux de compression activé.";
				else
					cout << "Taux de compression désactivé.";
				cout << endl;
				break;
			case 3 : imIn.save(name, RGBC); break;
			case 4 : imIn.save(name, YCCC); break;
			case 5 : imIn.save(name, PPM); break;
			case 6 : cout << "Nom de l'image : ";
				cin >> name;
				name = "img/" + name;
				imIn.load(name);
				imOut.load(name);
				break;
			default : cout << "Action inconnue" << endl; break;
		}
		
		cout << endl << "--------------------------------------------------------------------" << endl;
	}
	
	return 0;
}
