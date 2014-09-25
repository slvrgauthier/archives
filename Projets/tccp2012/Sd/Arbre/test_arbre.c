#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"

int main(int argc,char* argv[])
{
	arbre* A=creerArbre(1337);
	arbre* B=A->ajouterFils(A,27328);
	arbre* C=A->ajouterFils(A,248902);
	arbre* D=A->ajouterFils(A,523413);
	arbre* E=B->ajouterFils(B,"abcd");
	arbre* F=B->ajouterFils(B,'d');
	printf("test d'accesseurs :\n");
	printf("%d\n",A->contenu);
	printf("TestChaine: %s \n", A->chaine(A));
	printf("%d\n",B->contenu);
	printf("%d\n",C->contenu);
	printf("%d\n",D->contenu);
	printf("test de char : ");
	printf("%c\n",F->contenu);
	printf("test de chaine : ");
	printf("%s\n",E->contenu);
	printf("test getfils :\n");
	printf("%d\n",A->getFilsNbx(A,1)->contenu);
	printf("%d\n",A->getFilsNbx(A,2)->contenu);
	printf("%d\n",A->getFilsNbx(A,3)->contenu);
	printf("test depassement : ");
	if(A->getFilsNbx(A,4)==NULL)
		printf("Succès.\n");
	printf("test nbelements : %d\n",A->nbElementsArbre(A));
	printf("test estfeuille (doit retourner false puis true) :\n");
	if(A->estFeuille(A))
		printf("true\n");
	else
		printf("false\n");
	if(F->estFeuille(F))
		printf("true\n");
	else
		printf("false\n");
	printf("Test clone :\n");
	//printf("\tArbre a cloner: A :: %s\n", A->chaine(A));
	printf("\tArbre a cloner: B :: %s\n", B->chaine(B));
	//arbre* G=A->cloneRacine(A);
	arbre* G=B->cloneRacine(B);
	printf("\tAprès clonage :\n");
	//printf("\t\tContenu de l'original : %s\n",A->chaine(A));
	printf("\t\tContenu de l'original : %s (%d)\n",B->chaine(B),B->contenu);
	printf("\t\tContenu du clone : %s (%d)\n",G->chaine(G),G->contenu);
	//printf("\t\tFils commun: B :: %s\n", B->chaine(B));
	printf("\tModification de l'original.\n");
	//A->contenu=7234;
	B->contenu=7234;
	//printf("\t\tContenu de l'original : %s\n",A->chaine(A));
	printf("\t\tContenu de l'original : %s (%d)\n",B->chaine(B),B->contenu);
	printf("\t\tContenu du clone : %s (%d)\n",G->chaine(G),G->contenu);
	//printf("\t\tFils commun: B :: %s\n", B->chaine(B));
	printf("Greffe d'un arbre à 3 elements.\n");
	arbre* H=creerArbre(16789);
	arbre* I=H->ajouterFils(H,2321);
	arbre* J=H->ajouterFils(H,1);
	C->grefferArbre(C,H);
	printf("nbelements du nouvel arbre : %d\n",A->nbElementsArbre(A));
	printf("Destruction des arbres : \n");
	if(A->detruireArbre(A)==0)
		printf("\tDestruction de l'arbre A.\n");
	if(G->detruireArbre(G)==0)
		printf("\tDestruction du clone G.\n");
	return 0;
}
