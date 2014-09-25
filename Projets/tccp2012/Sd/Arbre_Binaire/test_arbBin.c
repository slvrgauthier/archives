#include <stdio.h>
#include <stdlib.h>

#include "arbBin.h"

int main(int argc, char *argv[])
{
	ArbBin racine = creerArbre(1);
	afficheArbre(racine);
	printf("\n");
	ArbBin node1 = racine->ajoutNoeud(racine, 2);
	afficheArbre(racine);
	printf("\n");
	ArbBin node2 = racine->ajoutNoeud(racine, 3);
	afficheArbre(racine);
	printf("\n");
	ArbBin node3 = racine->ajoutNoeud(racine, 4);
	afficheArbre(racine);

	printf("\nDestruction de l'arbre entier.\n");

	supprRecur(racine);
	//racine = NULL;
	afficheArbre(racine);

	return 0;
}
