#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[], char*env[]){
  int n;
  char continuer[100]="y";
  int **pascal;
  while(continuer[0]=='y'){
    printf("Entrez la puissance : ");
    scanf("%d",&n);
    pascal=malloc(n*sizeof(int*));
    for(int i=0;i<n;i++)
      pascal[i]=malloc((i+1)*sizeof(int));
    pascal[0][0]=pascal[1][0]=pascal[1][1]=1;
    for(int i=1;i<n;i++){
      for(int j=1;j<i;j++)
        pascal[i][j]=pascal[i-1][j-1]+pascal[i-1][j];
      pascal[i][0]=pascal[i][i]=1;
    }
    printf("Voici le triangle de Pascal :\n");
    for(int i=0;i<n;i++){
      for(int j=0;j<=i;j++)
        printf("%2d ",pascal[i][j]);
      printf("\n");
    }
    printf("Recommencer ? (y/n) ");
    scanf("%s",&continuer);
  }
  exit(EXIT_SUCCESS);
}

