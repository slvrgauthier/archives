#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[], char*env[]){
FILE* f=fopen(argv[1],"r+");
if(f!=NULL){
	char c=fgetc(f);
	int T[256];
	int cpt=0;
	for(int i=0;i<256;i++)
		T[i]=0;
	while (c != EOF){
	T[c]++;
	cpt++;
	c=fgetc(f);
	}
	int tot=0;
	int nbchar=0;
	for(int i=0;i<256;i++){
		if (T[i]!=0)
			nbchar++;
		printf("%e ",(float)T[i]/cpt);
		tot+=T[i];
	}
	printf("\nNombre de caractères : %i\nFréquence totale : %f\nNombre de caractères différents : %i\n",cpt,(float)tot/cpt,nbchar);
}
fclose(f);
}


