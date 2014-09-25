#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lecture.h"

int main()
{
    int x=lire_entier(),n=lire_entier(),i,p=1;
    for (i=1;i<=n;i++)
        p*=x;
    printf("La valeur de x puissance n est %d \n",p);
    return 0;
}
