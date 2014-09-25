#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lecture.h"

int main()
{
    double a,x,y;
    int n;
    printf("Entrez a : ");
    scanf("%lf",&a);
    printf("Precision : ");
    scanf("%d",&n);
    x=a;
    y=0;
    while (fabs(x-y)>=1./n)
    {
        y=x;
        x=0.5*(x+a/x);
    }
    printf("La racine de %f est %f (au lieu de %f) \n",a,x,sqrt(a));
    return 0;
}
