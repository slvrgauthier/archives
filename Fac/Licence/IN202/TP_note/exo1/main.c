#include <stdio.h>
#include <stdlib.h>

int main()
{
    int T[12][12]={{0,0}}, i=0, j=0;
    for (i=2;i<12;i++)
    {
        T[1][i]=i-1;
        T[i][1]=i-1;
    }
    for (i=2;i<12;i++)
        for (j=2;j<12;j++)
            T[i][j]=(i-1)*(j-1);
    for (i=1;i<12;i++)
    {
        for (j=1;j<12;j++)
        {
            if (T[i][j]<10)
                printf("  %d ",T[i][j]);
            else if (T[i][j]<100)
                printf(" %d ",T[i][j]);
            else printf("%d ",T[i][j]);
                        }
                    printf("\n");
    }
    return 0;
}
