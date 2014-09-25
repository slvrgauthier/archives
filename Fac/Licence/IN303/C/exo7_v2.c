#include <stdio.h>

int main (int argc, char*argv[], char*env[]){
float M=0,x,i=0;
printf("Rentrez vos nombres :\n");
int continuer = scanf("%f",&x);
while (continuer)
{
	M+=x;
	continuer = scanf("%f",&x);
	i++;
}
printf("La moyenne est de %f\n",(M/i));
return 0;
}


