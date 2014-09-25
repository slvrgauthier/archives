#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//variables globales :
char* code[511];
int T[511],fg[511],fd[511],parent[511]; // T probabilités, fg et fd fils gauche et droit

void HuffmanCode(int ind);
char setBit(char c, int index, int bit);

int main(int argc, char*argv[], char*env[]){
//Construction de la distribution probabiliste des caractères
FILE* f=fopen(argv[1],"r+");
if(f!=NULL){
	char c=fgetc(f);
	int cpt=0;
	for(int i=0;i<511;i++){
		T[i]=0;
		fg[i]=fd[i]=parent[i]=-1;
	}
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
		tot+=T[i];
	}
	printf("\nNombre total de caractères : %i\nFréquence totale : %f\nNombre de caractères différents : %i\n",cpt,(float)tot/cpt,nbchar);
//Construction probabiliste de l'arbre
	printf("\nArbre :\n");
	int min1, min2, imin1, imin2, j=256; //minimums et indices des minimums, j indice du prochain nouveau noeud
	int nbnewnoeud=nbchar-1;
	do{
		min1=cpt;
		min2=cpt;
		for(int i=0;i<j;i++){
			if((T[i]!=0)&&(parent [i]==-1)){ //noeuds non traités
				if(min1<min2){
					if(T[i]<min2){
						min2=T[i];
						imin2=i;
					}
				}
				else {
					if(T[i]<min1){
						min1=T[i];
						imin1=i;
					}
				}
			}
		}
		T[j]=min1+min2;
		fg[j]=imin1; fd[j]=imin2; parent[imin1]=parent[imin2]=j;
		j++; nbnewnoeud--;
	}while(nbnewnoeud!=0);
	for(int i=0;i<j;i++)
		if (T[i]!=0)
			printf("%3d : %f ; %3d ; %3d ; %3d\n",i,(float)T[i]/cpt,fg[i],fd[i],parent[i]);
//Calcul du code de Huffman
	j--; //j indice du dernier noeud créé = racine de l'arbre
	for(int i=0;i<511;i++)
		code[i]=NULL;
	HuffmanCode(j);
	int codmin=64,codmax=0,codmoy=0; //tailles min,max et moy du codage
	printf("\nCode :\n");
	for(int i=0;i<256;i++)
		if(code[i]!=NULL){
			if(i==9) printf("TAB : %s\n",code[i]);
			else if(i==10) printf(" CR : %s\n",code[i]);
			else printf("%3c : %s\n",i,code[i]);
			codmin=((codmin < strlen(code[i]))? codmin : strlen(code[i]));
			codmax=((codmax > strlen(code[i]))? codmax : strlen(code[i]));
			codmoy+=strlen(code[i]);
		}
	codmoy/=nbchar;
	for(int i=256;i<511;i++)
		if(code[i]!=NULL)
			printf("%3i : %s\n",i,code[i]);
	printf("\nTaille minimale du code : %d\nTaille maximale du code : %d\nTaille moyenne du code : %d\n",codmin,codmax,codmoy);
}
fclose(f);
return 0;
}

void HuffmanCode(int ind){
if(parent[ind]!=-1){
	code[ind]=malloc(strlen(code[parent[ind]])+2);
	strcat(strcpy(code[ind],code[parent[ind]]),(ind==fg [parent[ind]]?"0":"1"));
}
else
	code[ind]="";
if(fg[ind]!=-1){
	HuffmanCode(fg[ind]);
	HuffmanCode(fd[ind]);
}
}

char setBit(char c, int index, int bit){
	char masque=1;
	for(int i=1;i<index;i++)
		masque*=2;
	if(((masque & c) == masque)&&(bit==0))
		return (c-masque);
	else if (((masque & c) != masque)&&(bit==1))
		return (c+masque);
	else return c;
}



