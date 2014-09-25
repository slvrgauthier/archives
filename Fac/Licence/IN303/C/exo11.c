#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char*argv[], char*env[]){
char S[10];
int i,nb1,k,nb2;
for(k=1;k<argc;k++){
	i=0;nb1=atoi(argv[k]);nb2=0;
	while (nb1!=0){
		nb2=10*nb2+mod(nb1,10);
		nb1=(nb1-mod(nb1,10))/10;
	}
	while (nb2!=0){
		S[i]=mod(nb2, 10)*10^i;
		nb2=(nb2-mod(nb2, 10))/10;
		i++;
	}
printf("%s\n",S);
}
}



