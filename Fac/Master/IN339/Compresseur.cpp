#include "Image.h"
#include <iostream>
#include <string>

using namespace std;

void RGBcompress(Image& imIn, Image& imOut, string name, bool psnr);
void YCCcompress(Image& imIn, Image& imOut, string name, bool psnr);

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
	cout<<"length = "<<w*h<<endl;
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
			case 3 : RGBcompress(imIn, imOut, name, psnr); break;
			case 4 : YCCcompress(imIn, imOut, name, psnr); break;
			case 5 : imIn.save(name.erase(name.find_last_of("."), string::npos), PPM); break;
			default : cout << "Action inconnue" << endl; break;
		}
		
		cout << endl << "--------------------------------------------------------------------" << endl;
	}
	
	return 0;
}

void RGBcompress(Image& imIn, Image& imOut, string name, bool psnr) {
	if(!imIn.isColored()) {
		cout << "Erreur: l'image ne prend pas en charge la couleur.\n" << endl;
	}
	else {
		string l_name = name.erase(name.find_last_of("."), string::npos);
		if(imOut.save(l_name, RGBC))
			cout << l_name << " enregistrée." << endl;
		else
			cout << "Erreur: " << l_name << " non enregistrée." << endl;
	}
}

void YCCcompress(Image& imIn, Image& imOut, string name, bool psnr) {
	if(!imIn.isColored()) {
		cout << "Erreur: l'image ne prend pas en charge la couleur.\n" << endl;
	}
	else {
		string l_name = name.erase(name.find_last_of("."), string::npos);
		if(imOut.save(l_name, YCCC))
			cout << l_name << " enregistrée." << endl;
		else
			cout << "Erreur: " << l_name << " non enregistrée." << endl;
	}
}

