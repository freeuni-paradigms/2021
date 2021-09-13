#include <stdio.h>

int main(int argc, char **argv) {
  printf("Enter integer:\n");
  int x;
  scanf("%d", &x);
  if (x && !(x & (x - 1))){
  	printf("Is a power of 2\n");
  }else{
   	printf("Is not a power of 2\n");
  }
  return 0;
}
