#include <stdio.h>
#include <stdlib.h>
#define TAILLE = 10

int PremierePosition (int T[TAILLE], int x);
int DernierePosition (int T[TAILLE], int x);
int estAvantTableau (int T[TAILLE], int a, int b);
int AvantMoi (int T[TAILLE], int b);

int main()
{
    int T[TAILLE]={5,1,3,2,5,4,3,5,1,2}, i=0;
    int T1=AvantMoi(T,3), T2=AvantMoi(T,4);
    printf("Les nombres se trouvant avant 3 dont :\n");
    for (i=1; i<TAILLE+1; i++)
    {
        if (T1[i]!=0)
            printf("%d   ",T1[i]);
    }
    printf("Les nombres se trouvant avant 4 dont :\n");
    for (i=1; i<TAILLE+1; i++)
    {
        if (T2[i]!=0)
            printf("%d   ",T2[i]);
    }
    return 0;
}

int PremierePosition (int T[TAILLE], int x)
{
    int i=0;
    for (i=1; i<TAILLE+1; i++)
    {
        if (T[i]==x)
            return i;
    }
    return -1;
}

int DernierePosition (int T[TAILLE], int x)
{
    int i=0;
    for (i=TAILLE; i>0; i--)
    {
        if (T[i]==x)
            return i;
    }
    return -1;
}

int estAvantTableau (int T[TAILLE], int a, int b)
{
    int i=0;
    for (i=1; i<TAILLE+1; i++)
    {
        if (T[i]==a)
            return true;
        else if (T[i]==b)
            return false;
    }
    return false;
}

int AvantMoi (int T[TAILLE], int b)
{
    int i=0, j=1, tab[TAILLE]={0};
    for (i=1; i<TAILLE+1; i++)
    {
        if (estAvantTableau(T,T[i],b))
        {
            tab[j]=T[i];
            j++;
        }
    }
}


