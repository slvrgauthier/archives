#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//              Using the software : Compression [path in] [path out]

// ==============================    Global Var :   ==============================
int proba[511],fg[511],fd[511],parent[511];
char* code[511];


// ==============================    Prototypes :   ==============================
void initTabint(int T[], int val);
void initTabstr(char* T[], char* val);
void disPro(FILE* f, int* cpt);
int treePro(int nbChar, int nbCharDif);
void HuffmanCode(int ind);
char setBit(char c, int index, int bit);
void treeWr(FILE* g, short int* nbNoeud);
void textWr(FILE* f, FILE* g, int nbChar);


// ==============================       Main :      ==============================
int main(int argc, char*argv[], char*env[]){
  if (argc < 3){
    printf("Need two file paths to compress.\n");
    exit(1);
  }
  FILE* f = fopen(argv[1],"r+");
  FILE* g = fopen(argv[2], "r+");
  if (f == NULL){
    printf("Cannot open file (IN).\n");
    exit(2);
  }
  if (g == NULL){
    printf("Cannot open file (OUT).\n");
    exit(3);
  }
  
// Initialization :
  initTabint(proba, 0);
  initTabint(fg, -1);
  initTabint(fd, -1);
  initTabint(parent, -1);
  initTabstr(code, NULL);
  
// Construction of probability distribution of characters:
  int nbChar = 0, nbCharDif = 0;
  disPro(f, &nbChar);
  for(int i=0;i<256;i++){
    if (proba[i]!=0)
      nbCharDif++;
  }
  printf("\nTotal number of characters : %i\n",nbChar);
  printf("Number of different characters : %i\n",nbCharDif);
  
// Probabilistic construction of the tree :
  int indRacine = treePro(nbChar, nbCharDif);
  short int nbNoeud = 0;
  for(int i=0 ; i<511 ; i++)
    if(proba[i] != 0)
      nbNoeud++;
  
// Calculation of Huffman code :
  HuffmanCode(indRacine);
  int codmin = 64, codmax = 0, codmoy = 0;
  for(int i=0 ; i<256 ; i++){
    if(code[i] != NULL){
      codmin = ((codmin < strlen(code[i]))? codmin : strlen(code[i]));
      codmax = ((codmax > strlen(code[i]))? codmax : strlen(code[i]));
      codmoy += strlen(code[i]);
    }
  }
  codmoy /= nbCharDif;
  printf("\nCode's minimum size : %d\nCode's maximum size : %d\nCode's average size : %d\n",codmin,codmax,codmoy);
  printf("Compression's average rate : %i%\n",100-(codmoy*nbChar + 2*(nbNoeud + 1))*100/(nbChar*8));
  printf("\nDo you want to continue ? (y/n) ");
  char follow;
  scanf("%c",&follow);
  if(follow == 'n'){
    printf("Aborted by the user.\n");
    exit(4);
  }
  
// Writing in binary file :
  treeWr(g, &nbNoeud);
  textWr(f, g, nbChar);
  
// Closing :
  fclose(f);
  fclose(g);
  return 0;
}


// ==============================    Functions :    ==============================
void initTabint(int T[], int val){
  for(int i=0 ; i < 511 ; i++)
    T[i] = val;
}

void initTabstr(char* T[], char* val){
  for(int i=0 ; i < 511 ; i++)
    T[i] = val;
}

void disPro(FILE* f, int* cpt){
  char c = fgetc(f);
  while (c != EOF){
    proba[c]++;
    *cpt = *cpt + 1;
    c = fgetc(f);
  }
}

int treePro(int nbChar, int nbCharDif){
  int min1, min2, imin1, imin2, j = 256; //minimums et indices des minimums, j indice du prochain nouveau noeud
  int nbnewnoeud = nbCharDif-1; //nombre de nouveaux noeuds à créer
  do{
    min1 = min2 = nbChar;
    for(int i=0 ; i<j ; i++){
      if((proba[i] != 0) && (parent[i] == -1)){ //noeuds non traités
        if(min1 < min2){
          if(proba[i] < min2){
            min2 = proba[i];
            imin2 = i;
          }
        }
        else {
          if(proba[i] < min1){
            min1 = proba[i];
            imin1 = i;
          }
        }
      }
    }
    proba[j] = min1+min2;
    fg[j] = imin1; fd[j] = imin2; parent[imin1] = parent[imin2] = j;
    j++; 
    nbnewnoeud--;
  }while(nbnewnoeud != 0);
  return (j-1);
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
  if(bit == 1)
    return (c | (1 << (index-1)));
  else
    return (c & (~(1 << (index-1))));
}

void treeWr(FILE* g, short int* nbNoeud){
  fwrite(nbNoeud, sizeof(short int), 1, g);
  for(short int i=0 ; i<511 ; i++){
    if(proba[i] != 0){
      fwrite(&i, sizeof(short int), 1, g);
      fwrite(&fg[i], sizeof(short int), 1, g);
      fwrite(&fd[i], sizeof(short int), 1, g);
      fwrite(&parent[i], sizeof(short int), 1, g);
    }
  }
}

void textWr(FILE* f, FILE* g, int nbChar){
  fwrite(&nbChar, sizeof(int), 1, g);
  fseek(f, 0, SEEK_SET);
  char* S = code[fgetc(f)];
  char c;
  int i = 0, masque, tot = nbChar, percent1 = 0, percent2 = 0;
  while(nbChar != 0){
    c = 0;
    masque = 8;
    while((masque != 0) && (nbChar != 0)){
      c = setBit(c, masque, (S[i]-'0'));
      masque--;
      i++;
      if(S[i] == '\0'){
	S = code[fgetc(f)];
	i = 0;
	nbChar--;
	percent2 = 100-nbChar*100/tot;
	if((percent2 != percent1) && (percent2 % 10 == 0)){
	  printf("0 [");
	  for(int j=0 ; j<percent2/10 ; j++)
	    printf("-");
	  printf("] %i%\n",percent2);
	  percent1 = percent2;
	}
      }
    }
    fwrite(&c, sizeof(char), 1, g);
  }
}

