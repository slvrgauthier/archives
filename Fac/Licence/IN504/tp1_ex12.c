#include <stdlib.h>
#include <stdio.h>

void f1(void) {
  int t1[10]={0,1,2,3,4,5,6,7,8,9};
  printf("t1 :\n");
  for(int i=0;i<10;i++)
    printf("%d ",t1[i]);
  printf("\n");
  for(int i=0;i<10;i++)
    printf("%hx ",t1+i);
  printf("\n");
}

void f2(void) {
  int t2[10];
  printf("t2 :\n");
  for(int i=0;i<10;i++)
    printf("%d ",t2[i]);
  printf("\n");
  for(int i=0;i<10;i++)
    printf("%hx ",t2+i);
  printf("\n");
}

int main(int argc, char* argv[], char* env[]) {
  f1();
  f2();
  // f2 contient les fantômes de f1 contenus dans la pile
  return 0;
}
