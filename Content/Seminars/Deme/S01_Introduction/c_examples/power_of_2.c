#include <stdio.h>

int main(int argc, char **argv) {
  int x;
  printf("Enter integer: ");
  scanf("%d", &x);
  
  if (x && !(x & (x - 1))) {
  	printf("%d Is a power of 2\n", x);
  } else {
   	printf("%d Is not a power of 2\n", x);
  }
  return 0;
}
