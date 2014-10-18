#include "Image.h"
#include "Function.h"
#include "Load.h"
#include "Save.h"
#include "Convert.h"
#include <iostream>
#include <string>

using namespace std;

void man() {
	cout << "Mode d'emploi :"<< endl;
	cout << "0 : Quitter" << endl;
	cout << "1 : Afficher le mode d'emploi" << endl;
	cout << "2 : Changer d'image" << endl;
	cout << "3 : Calculer le PSNR" << endl;
	cout << "4 : Compresser l'image en RGBc" << endl;
	cout << "5 : Compresser l'image en YCCc" << endl;
	cout << "6 : Convertir l'image en PGM" << endl;
	cout << "7 : Convertir l'image en PPM" << endl;
	cout << "8 : Faire une différence" << endl;
	cout << "9 : Compresser l'image en SLVR (projet)" << endl;
}

int main(int argc, char **argv) {
	string name, name2;
	cout << "Nom de l'image : ";
	cin >> name;
	name = "img/" + name;
	Image imIn(name);
	
	int w = imIn.getWidth(), h = imIn.getHeight();
	int action = -1;
	double psnr = 0;
	
	man();

	while(action != 0) {
		cout << endl << "===== " << name << " =====" << endl;
		cout << endl << "Action : ";
		cin >> action;
		switch(action) {
			case 0 : break;
			case 1 : man(); break;
			case 2 : 
				cout << "Nom de l'image : ";
				cin >> name;
				name = "img/" + name;
				imIn.load(name);
				break;
			case 3 : 
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
			case 4 : imIn.save(name, RGBC); break;
			case 5 : imIn.save(name, YCCC); break;
			case 6 : imIn.save(name, PGM); break;
			case 7 : imIn.save(name, PPM); break;
			case 8 : toDiff(&imIn).save(name, PGM); break;
			case 9 : imIn.save(name, SLVR); break;
			default : cout << "Action inconnue" << endl; break;
		}
	}
	
	return 0;
}
