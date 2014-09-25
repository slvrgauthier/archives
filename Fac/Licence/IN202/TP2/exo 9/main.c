#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lecture.h"

int main()
{
    int n=lire_entier(),i;
    float x=0;
    printf("A l'endroit : ");
    for (i=1;i<=n;i++)
        x+=1.0/i;
    printf("x=%f \n",x);
    printf("A l'envers : ");
    x=0;
    for (i=n;i>0;i--)
        x+=1.0/i;
    printf("x=%f",x);
    return 0;
}
