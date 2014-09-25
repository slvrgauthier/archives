#include <stdio.h>

int main (int argc, char*argv[], char*env[]){
float M=0,x,i=0;
printf("Rentrez vos nombres :");
scanf("%f",&x);
char c;
while (i==0)
{
	M+=x;
	scanf("%f",&x);
	printf("Voulez-vous continuer ? (y or n)");
	scanf("%c",&c);
	printf("%c",c);
}
printf("%f",(M/i));
return 0;
}


