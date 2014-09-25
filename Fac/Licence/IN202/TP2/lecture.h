#include <stdio.h>
#include <stdlib.h>

int lire_entier();
float lire_reel();

int lire_entier()
{
    int n;
    printf("Entrez  un  entier:");
    scanf("%d",&n);
    return  n;
    }

float lire_reel()
{
    float f;
    printf("Entrez  un reel:");
    scanf("%f",&f);
    return  f;
    }
