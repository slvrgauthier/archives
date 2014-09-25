#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lecture.h"

int main()
{
    int a=0,n=0,s=0;
    double m;
    while (a>=0)
    {
        a=lire_entier();
        if (a>=0)
        {
            n++;
            s+=a;
        }
    }
    m=(float)s/n;
    printf("%d nombres positifs ont été tapspé à la suite! \n",n);
    printf("La moyenne de cette suite est %.2f \n",m);
    return 0;
}
