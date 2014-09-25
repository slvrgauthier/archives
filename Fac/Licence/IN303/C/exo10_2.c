#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[], char*env[]){
char* S;
int i,nb,k;
for(k=1;k<argc;k++){
	i=0;nb=0;S=argv[k];
	while (S[i]!='\0'){
		if ((S[i]>'9')||(S[i]<'0'))
			break;
		else
			while((S[i]>'0')&&(S[i]<'9')){
				nb=10*nb+(S[i]-'0');
				i++;
			}
	}
	printf("%i\n",(nb));
}
}

