#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>

// Valeurs minimum et maximum d'un short
#define VAL_MIN 0
#define VAL_MAX 65535

// Drapeaux utilisés pour le Volume Rendering
#define MIP 0 // Utilisation du maximum
#define AIP 1 // Utilisation de la moyenne
#define MinIP 2 // Utilisation du minimum

using namespace std;

typedef struct Vertex {
	double x;
	double y;
	double z;
}Vertex;

typedef struct Triangle {
	Vertex v1;
	Vertex v2;
	Vertex v3;
}Triangle;

bool readImage(const char* filename, unsigned short* image, int dimX, int dimY, int dimZ);
unsigned short getValue(unsigned short* image, int i, int j, int k, int dimX, int dimY);
unsigned short* extremValue(unsigned short* image, int dimX, int dimY, int dimZ);
bool volumeRendering(unsigned short* image, int dimX, int dimY, int dimZ, unsigned short* result, int flag);
bool writeImage(const char* filename, unsigned short* image, int dimX, int dimY, int dimZ);
bool tresholding(unsigned short* image, unsigned short treshold, int dimX, int dimY, int dimZ);
vector<Triangle> marchingCube(unsigned short* image, unsigned short treshold, int dimX, int dimY, int dimZ, double sizeX, double sizeY, double sizeZ);
bool writeSTL(const char* filename, vector<Triangle> mesh);

int main(int argc, char* argv[]) {
	
	// Conteneur de l'image (taille maximum des images pour n'en faire qu'une)
	unsigned short* image = new unsigned short[512*512*256];
	unsigned short* result = new unsigned short[512*512];
	
/*
	// BEAUFIX
	if(readImage("./medical/beaufix.448x576x72.0.6250x0.6250x1.4.img", image, 448, 576, 72)) {
		unsigned short* minmax = extremValue(image, 448, 576, 72);
		cout << "Beaufix : min="<<minmax[0]<<", max="<<minmax[1]<<endl;
		
		volumeRendering(image, 448, 576, 72, result, MIP);
		writeImage("./medical/beaufix.MIP.0.raw", result, 448, 576, 1);
		
		volumeRendering(image, 448, 576, 72, result, AIP);
		writeImage("./medical/beaufix.AIP.0.raw", result, 448, 576, 1);
		
		volumeRendering(image, 448, 576, 72, result, MinIP);
		writeImage("./medical/beaufix.MinIP.0.raw", result, 448, 576, 1);
	} 
	else { cout<<"Erreur de lecture de Beaufix"<<endl; }
	
	
	// BRAINIX
	if(readImage("medical/brainix.256x256x100.0.9375x0.9375x1.5.img", image, 256, 256, 100)) {
		unsigned short* minmax = extremValue(image, 256, 256, 100);
		cout << "Brainix : min="<<minmax[0]<<", max="<<minmax[1]<<endl;
		
		volumeRendering(image, 256, 256, 100, result, MIP);
		writeImage("./medical/brainix.MIP.0.raw", result, 256, 256, 1);
		
		volumeRendering(image, 256, 256, 100, result, AIP);
		writeImage("./medical/brainix.AIP.0.raw", result, 256, 256, 1);
		
		volumeRendering(image, 256, 256, 100, result, MinIP);
		writeImage("./medical/brainix.MinIP.0.raw", result, 256, 256, 1);
	}
	else { cout<<"Erreur de lecture de Brainix"<<endl; }
	
	
	// ENGINE
	if(readImage("medical/engine.256x256x128.1x1x1.img", image, 256, 256, 128)) {
		unsigned short* minmax = extremValue(image, 256, 256, 128);
		cout << "Engine : min="<<minmax[0]<<", max="<<minmax[1]<<endl;
		
		volumeRendering(image, 256, 256, 128, result, MIP);
		writeImage("./medical/engine.MIP.0.raw", result, 256, 256, 1);
		
		volumeRendering(image, 256, 256, 128, result, AIP);
		writeImage("./medical/engine.AIP.0.raw", result, 256, 256, 1);
		
		volumeRendering(image, 256, 256, 128, result, MinIP);
		writeImage("./medical/engine.MinIP.0.raw", result, 256, 256, 1);
	}
	else { cout<<"Erreur de lecture de Engine"<<endl; }
	
	
	// FOOT
	if(readImage("medical/foot.256x256x256.1.1.1.img", image, 256, 256, 256)) {
		unsigned short* minmax = extremValue(image, 256, 256, 256);
		cout << "Foot : min="<<minmax[0]<<", max="<<minmax[1]<<endl;
		
		volumeRendering(image, 256, 256, 256, result, MIP);
		writeImage("./medical/foot.MIP.0.raw", result, 256, 256, 1);
		
		volumeRendering(image, 256, 256, 256, result, AIP);
		writeImage("./medical/foot.AIP.0.raw", result, 256, 256, 1);
		
		volumeRendering(image, 256, 256, 256, result, MinIP);
		writeImage("./medical/foot.MinIP.0.raw", result, 256, 256, 1);
	}
	else { cout<<"Erreur de lecture de Foot"<<endl; }
	
	
	// MANIX
	if(readImage("medical/manixSansIV.512x512x48.0.4570x0.4570x3.0.img", image, 512, 512, 48)) {
		unsigned short* minmax = extremValue(image, 512, 512, 48);
		cout << "Manix : min="<<minmax[0]<<", max="<<minmax[1]<<endl;
		
		volumeRendering(image, 512, 512, 48, result, MIP);
		writeImage("./medical/manix.MIP.0.raw", result, 512, 512, 1);
		
		volumeRendering(image, 512, 512, 48, result, AIP);
		writeImage("./medical/manix.AIP.0.raw", result, 512, 512, 1);
		
		volumeRendering(image, 512, 512, 48, result, MinIP);
		writeImage("./medical/manix.MinIP.0.raw", result, 512, 512, 1);
	}
	else { cout<<"Erreur de lecture de Manix"<<endl; }
	
	
	// WHATISIT
	if(readImage("medical/whatisit.301x324x56.1.1.1.4.img", image, 301, 324, 56)) {
		unsigned short* minmax = extremValue(image, 301, 324, 56);
		cout << "Whatisit : min="<<minmax[0]<<", max="<<minmax[1]<<endl;
		
		volumeRendering(image, 301, 324, 56, result, MIP);
		writeImage("./medical/whatisit.MIP.0.raw", result, 301, 324, 1);
		
		volumeRendering(image, 301, 324, 56, result, AIP);
		writeImage("./medical/whatisit.AIP.0.raw", result, 301, 324, 1);
		
		volumeRendering(image, 301, 324, 56, result, MinIP);
		writeImage("./medical/whatisit.MinIP.0.raw", result, 301, 324, 1);
	}
	else { cout<<"Erreur de lecture de Whatisit"<<endl; }
*/

	// BEAUFIX
	if(readImage("./medical/beaufix.448x576x72.0.6250x0.6250x1.4.img", image, 448, 576, 72)) {
		cout << "Beaufix" << endl;
		if(tresholding(image,120, 448, 576, 72)) {
			writeImage("./medical/beaufix.treshold120.0.raw", image, 448, 576, 72);
			writeSTL("./medical/beaufix.treshold120.stl", marchingCube(image, 120, 448, 576, 72, 0.625, 0.625, 1.4));
		}
	} 
	else { cout<<"Erreur de lecture de Beaufix"<<endl; }

	
	// ENGINE
	if(readImage("medical/engine.256x256x128.1x1x1.img", image, 256, 256, 128)) {
		cout << "Engine" << endl;
		if(tresholding(image,100, 256, 256, 128)) {
			writeImage("./medical/engine.treshold100.0.raw", image, 256, 256, 128);
			writeSTL("./medical/engine.treshold100.stl", marchingCube(image, 100, 256, 256, 128, 1.0, 1.0, 1.0));
		}
		if(tresholding(image,200, 256, 256, 128)) {
			writeImage("./medical/engine.treshold200.0.raw", image, 256, 256, 128);
			writeSTL("./medical/engine.treshold200.stl", marchingCube(image, 200, 256, 256, 128, 1.0, 1.0, 1.0));
		}
	}
	else { cout<<"Erreur de lecture de Engine"<<endl; }
	

	// MANIX
	if(readImage("medical/manixSansIV.512x512x48.0.4570x0.4570x3.0.img", image, 512, 512, 48)) {
		cout << "Manix" << endl;
		if(tresholding(image,1250, 512, 512, 48)) {
			writeImage("./medical/manix.treshold1250.0.raw", image, 512, 512, 48);
			writeSTL("./medical/manix.treshold1250.stl", marchingCube(image, 1250, 512, 512, 48, 0.4570, 0.4570, 3.0));
		}
	}
	else { cout<<"Erreur de lecture de Manix"<<endl; }
	
	
	// WHATISIT
	if(readImage("medical/whatisit.301x324x56.1.1.1.4.img", image, 301, 324, 56)) {
		cout << "Whatisit" << endl;
		if(tresholding(image,50, 301, 324, 56)) {
			writeImage("./medical/whatisit.treshold50.0.raw", image, 301, 324, 56);
			writeSTL("./medical/whatisit.treshold50.stl", marchingCube(image, 50, 301, 324, 56, 1.0, 1.0, 1.4));
		}
	}
	else { cout<<"Erreur de lecture de Whatisit"<<endl; }

	return 0;
}


/* 
 * Lit une image à partir d'un fichier .img codé en brut avec des shorts.
 * 
 * Entrée : chemin du fichier (filename), conteneur de l'image (image), dimensions de l'image (dimX, dimY et dimZ).
 * Sortie : un booléen attestant de la réussite de la lecture.
 */
bool readImage(const char* filename, unsigned short* image, int dimX, int dimY, int dimZ) {
	
	// Ouverture du fichier
	FILE* fichier = fopen(filename, "rb");
	if(fichier == NULL) {
		cout<<"Erreur : impossible d'ouvrir le fichier "<<filename<<endl;
		return false;
	}
	
	// Lecture du fichier et stockage de l'image
	
	for(int z(0) ; z < dimZ ; ++z) {
		for(int y(0) ; y < dimY ; ++y) {
			for(int x(0) ; x < dimX ; ++x) {
				// Lecture du short
				if( fread(&image[z*dimX*dimY+y*dimX+x], sizeof(unsigned short), 1, fichier) == 0) {
					// Error ou EndOfFile
					return false;
				}
			}
		}
	}
	
	return true;
}

/* 
 * Renvoie une valeur de voxel selon une position.
 * 
 * Entrée : conteneur de l'image (image), indices de position (i, j et k), dimensions de l'image (dimX, dimY).
 * Sortie : la valeur du voxel de l'image à la position (i,j,k).
 */
unsigned short getValue(unsigned short* image, int i, int j, int k, int dimX, int dimY) {
	return (image[k*dimX*dimY+j*dimX+i]%256)*256+image[k*dimX*dimY+j*dimX+i]/256;
}

/* 
 * Détermine les valeurs minimum et maximum des voxels de l'image.
 * 
 * Entrée : conteneur de l'image (image), dimensions de l'image (dimX, dimY et dimZ).
 * Sortie : un tableau de deux shorts [min, max].
 */
unsigned short* extremValue(unsigned short* image, int dimX, int dimY, int dimZ) {
	// Minimum : minmax[0]
	// Maximum : minmax[1]
	unsigned short minmax[2] = {VAL_MAX, VAL_MIN};
	
	for(int z(0) ; z < dimZ ; ++z) {
		for(int y(0) ; y < dimY ; ++y) {
			for(int x(0) ; x < dimX ; ++x) {
				// Valeur du voxel courant
				unsigned short currentValue = getValue(image, x, y, z, dimX, dimY);
				
				// Maximum
				if(currentValue > minmax[1]) {
					minmax[1] = currentValue;
				}
				//Minimum
				if(currentValue < minmax[0]) {
					minmax[0] = currentValue;
				}
			}
		}
	}
	
	return minmax;
}

/* 
 * Crée une image au format brut suivant l'axe z.
 * 
 * Entrée : conteneur de l'image (image), dimensions de l'image (dimX, dimY et dimZ), conteneur de l'image de sortie (result), drapeau (flag).
 * Sortie : le conteneur result rempli, un booléen attestant de la réussite de la fonction.
 */
bool volumeRendering(unsigned short* image, int dimX, int dimY, int dimZ, unsigned short* result, int flag) {
	
	// Utilisation du maximum
	if(flag == MIP) {
		for(int y(0) ; y < dimY ; ++y) {
			for(int x(0) ; x < dimX ; ++x) {
				// Initialisation
				result[y*dimX+x] = image[y*dimX+x]; // en z=0
				for(int z(1) ; z < dimZ ; ++z) {
					// Recherche du maximum
					if(image[z*dimX*dimY+y*dimX+x] > result[y*dimX+x]) {
						result[y*dimX+x] = image[z*dimX*dimY+y*dimX+x];
					}
				}
			}
		}
	}
	// Utilisation de la moyenne
	else if(flag == AIP) {
		
		for(int y(0) ; y < dimY ; ++y) {
			for(int x(0) ; x < dimX ; ++x) {
				// Initialisation
				int sum = image[y*dimX+x];
				for(int z(1) ; z < dimZ ; ++z) {
					// Ajout de toutes les valeurs en Z
					sum += image[z*dimX*dimY+y*dimX+x];
				}
				// Moyenne
				sum /= dimZ;
				result[y*dimX+x] = (unsigned short)sum;
			}
		}
	}
	// Utilisation du minimum
	else if(flag == MinIP) {
		for(int y(0) ; y < dimY ; ++y) {
			for(int x(0) ; x < dimX ; ++x) {
				// Initialisation
				result[y*dimX+x] = image[y*dimX+x]; // en z=0
				for(int z(1) ; z < dimZ ; ++z) {
					// Recherche du maximum
					if(image[z*dimX*dimY+y*dimX+x] < result[y*dimX+x]) {
						result[y*dimX+x] = image[z*dimX*dimY+y*dimX+x];
					}
				}
			}
		}
	}
	// Drapeau inconnu
	else {
		cout<<"Drapeau inconnu"<<endl;
		return false;
	}
	
	return true;
}

/* 
 * Sauvegarde une image dans un fichier .img codé en brut avec des shorts.
 * 
 * Entrée : chemin du fichier (filename), conteneur de l'image (image), dimensions de l'image (dimX, dimY et dimZ).
 * Sortie : un booléen attestant de la réussite de l'écriture.
 */
bool writeImage(const char* filename, unsigned short* image, int dimX, int dimY, int dimZ) {
	
	// Ouverture du fichier
	FILE* fichier = fopen(filename, "wb");
	if(fichier == NULL) {
		cout<<"Erreur : impossible d'ouvrir le fichier "<<filename<<endl;
		return false;
	}
	
	// Ecriture du fichier
	for(int z(0) ; z < dimZ ; ++z) {
		for(int y(0) ; y < dimY ; ++y) {
			for(int x(0) ; x < dimX ; ++x) {
				// Ecriture des voxels dans le fichier
				if( fwrite(&image[z*dimY*dimX+y*dimX+x], sizeof(unsigned short), 1, fichier) == 0) {
					// Error
					return false;
				}
			}
		}
	}
	
	return true;
}

/* 
 * Seuille l'image selon la valeur passée en paramètre.
 * 
 * Entrée : conteneur de l'image (image), valeur du seuil (treshold).
 * Sortie : un booléen attestant de la réussite du seuillage.
 */
bool tresholding(unsigned short* image, unsigned short treshold, int dimX, int dimY, int dimZ) {

	for(int z(0) ; z < dimZ ; ++z) {
		for(int y(0) ; y < dimY ; ++y) {
			for(int x(0) ; x < dimX ; ++x) {
				image[z*dimX*dimY+y*dimX+x] = (getValue(image,x,y,z,dimX,dimY) < treshold)?0:VAL_MAX;
			}
		}
	}
	
	return true;
}

/* 
 * Transforme une image en maillage surfacique selon un seuil.
 * 
 * Entrée : conteneur de l'image (image), valeur du seuil (treshold).
 * Sortie : une liste de triangles définissant le maillage 3D de l'image.
 */
vector<Triangle> marchingCube(unsigned short* image, unsigned short treshold, int dimX, int dimY, int dimZ, double sizeX, double sizeY, double sizeZ) {
	vector<Triangle> mesh;
	Vertex v1, v2, v3, v4;
	Triangle t1, t2;

	for(int z(1) ; z < dimZ-1 ; ++z) {
		for(int y(1) ; y < dimY-1 ; ++y) {
			for(int x(1) ; x < dimX-1 ; ++x) {
				if(getValue(image,x,y,z,dimX,dimY) > treshold) {
					if(getValue(image,x-1,y,z,dimX,dimY) < treshold) {
						v1.x = (x-0.5)*sizeX; v1.y = (y-0.5)*sizeY; v1.z = (z-0.5)*sizeZ;
						v2.x = (x-0.5)*sizeX; v2.y = (y+0.5)*sizeY; v2.z = (z-0.5)*sizeZ;
						v3.x = (x-0.5)*sizeX; v3.y = (y+0.5)*sizeY; v3.z = (z+0.5)*sizeZ;
						v4.x = (x-0.5)*sizeX; v4.y = (y-0.5)*sizeY; v4.z = (z+0.5)*sizeZ;

						t1.v1 = v1; t1.v2 = v4; t1.v3 = v3;
						t2.v1 = v3; t2.v2 = v2; t2.v3 = v1;

						mesh.push_back(t1);
						mesh.push_back(t2);
					}
					if(getValue(image,x+1,y,z,dimX,dimY) < treshold) {
						v1.x = (x+0.5)*sizeX; v1.y = (y-0.5)*sizeY; v1.z = (z-0.5)*sizeZ;
						v2.x = (x+0.5)*sizeX; v2.y = (y+0.5)*sizeY; v2.z = (z-0.5)*sizeZ;
						v3.x = (x+0.5)*sizeX; v3.y = (y+0.5)*sizeY; v3.z = (z+0.5)*sizeZ;
						v4.x = (x+0.5)*sizeX; v4.y = (y-0.5)*sizeY; v4.z = (z+0.5)*sizeZ;

						t1.v1 = v1; t1.v2 = v2; t1.v3 = v3;
						t2.v1 = v3; t2.v2 = v4; t2.v3 = v1;

						mesh.push_back(t1);
						mesh.push_back(t2);
					}
					if(getValue(image,x,y-1,z,dimX,dimY) < treshold) {
						v1.x = (x-0.5)*sizeX; v1.y = (y-0.5)*sizeY; v1.z = (z-0.5)*sizeZ;
						v2.x = (x+0.5)*sizeX; v2.y = (y-0.5)*sizeY; v2.z = (z-0.5)*sizeZ;
						v3.x = (x+0.5)*sizeX; v3.y = (y-0.5)*sizeY; v3.z = (z+0.5)*sizeZ;
						v4.x = (x-0.5)*sizeX; v4.y = (y-0.5)*sizeY; v4.z = (z+0.5)*sizeZ;

						t1.v1 = v1; t1.v2 = v2; t1.v3 = v3;
						t2.v1 = v3; t2.v2 = v4; t2.v3 = v1;

						mesh.push_back(t1);
						mesh.push_back(t2);
					}
					if(getValue(image,x,y+1,z,dimX,dimY) < treshold) {
						v1.x = (x-0.5)*sizeX; v1.y = (y+0.5)*sizeY; v1.z = (z-0.5)*sizeZ;
						v2.x = (x+0.5)*sizeX; v2.y = (y+0.5)*sizeY; v2.z = (z-0.5)*sizeZ;
						v3.x = (x+0.5)*sizeX; v3.y = (y+0.5)*sizeY; v3.z = (z+0.5)*sizeZ;
						v4.x = (x-0.5)*sizeX; v4.y = (y+0.5)*sizeY; v4.z = (z+0.5)*sizeZ;

						t1.v1 = v1; t1.v2 = v4; t1.v3 = v3;
						t2.v1 = v3; t2.v2 = v2; t2.v3 = v1;

						mesh.push_back(t1);
						mesh.push_back(t2);
					}
					if(getValue(image,x,y,z-1,dimX,dimY) < treshold) {
						v1.x = (x-0.5)*sizeX; v1.y = (y-0.5)*sizeY; v1.z = (z-0.5)*sizeZ;
						v2.x = (x-0.5)*sizeX; v2.y = (y+0.5)*sizeY; v2.z = (z-0.5)*sizeZ;
						v3.x = (x+0.5)*sizeX; v3.y = (y+0.5)*sizeY; v3.z = (z-0.5)*sizeZ;
						v4.x = (x+0.5)*sizeX; v4.y = (y-0.5)*sizeY; v4.z = (z-0.5)*sizeZ;

						t1.v1 = v1; t1.v2 = v2; t1.v3 = v3;
						t2.v1 = v3; t2.v2 = v4; t2.v3 = v1;

						mesh.push_back(t1);
						mesh.push_back(t2);
					}
					if(getValue(image,x,y,z+1,dimX,dimY) < treshold) {
						v1.x = (x-0.5)*sizeX; v1.y = (y-0.5)*sizeY; v1.z = (z+0.5)*sizeZ;
						v2.x = (x-0.5)*sizeX; v2.y = (y+0.5)*sizeY; v2.z = (z+0.5)*sizeZ;
						v3.x = (x+0.5)*sizeX; v3.y = (y+0.5)*sizeY; v3.z = (z+0.5)*sizeZ;
						v4.x = (x+0.5)*sizeX; v4.y = (y-0.5)*sizeY; v4.z = (z+0.5)*sizeZ;

						t1.v1 = v1; t1.v2 = v4; t1.v3 = v3;
						t2.v1 = v3; t2.v2 = v2; t2.v3 = v1;

						mesh.push_back(t1);
						mesh.push_back(t2);
					}
				}
			}
		}
	}
	
	return mesh;
}

/* 
 * Sauvegarde un mesh dans un fichier .stl.
 * 
 * Entrée : chemin du fichier (filename), conteneur du mesh (mesh).
 * Sortie : un booléen attestant de la réussite de l'écriture.
 */
bool writeSTL(const char* filename, vector<Triangle> mesh) {
	
	// Ouverture du fichier
	ofstream fichier(filename);
	if(fichier == NULL) {
		cout<<"Erreur : impossible d'ouvrir le fichier "<<filename<<endl;
		return false;
	}
	
	// Ecriture de l'en-tête
	fichier << "solid " << filename << endl;

	// Ecriture du mesh
	for(int i(0) ; i < mesh.size() ; ++i) {
		// Ecriture des voxels dans le fichier
		fichier << "facet normal " << endl;
		fichier << "outer loop" << endl;
		fichier << "vertex " << mesh[i].v1.x << " " << mesh[i].v1.y << " " << mesh[i].v1.z << endl;
		fichier << "vertex " << mesh[i].v2.x << " " << mesh[i].v2.y << " " << mesh[i].v2.z << endl;
		fichier << "vertex " << mesh[i].v3.x << " " << mesh[i].v3.y << " " << mesh[i].v3.z << endl;
		fichier << "endloop" << endl << "endfacet" << endl;
	}

	// Conclusion
	fichier << "endsolid " << filename;

	fichier.close();
	
	return true;
}

