#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lecture.h"

int main()
{
    int a,b,c,max,min;
    a=lire_entier();
    b=lire_entier();
    c=lire_entier();
    if (a<b)
    {
        if (a<c)
        {
            min=a;
            if (b<c)
                max=c;
            else
                max=b;
        }
        else
        {
            min=c;
            max=b;
        }
    }
    else
    {
        if (a<c)
        {
            min=b;
            max=c;
        }
        else if (b<c)
        {
            min=b;
            max=a;
        }
        else
        {
            min=c;
            max=a;
        }

    }
    printf("Le max est %d et le min est %d \n",max,min);
    return 0;
}
