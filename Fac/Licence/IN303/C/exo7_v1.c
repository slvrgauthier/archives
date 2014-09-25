#include <stdio.h>

int main (int argc, char*argv[], char*env[]){
float M=0,x,i;
for(i=0;i<5;i++)
{
	printf("Rentrez votre nombre :");
	scanf("%f",&x);
	M+=x;
}
printf("La moyenne est de %f",(M/i));
return 0;
}


