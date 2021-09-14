#include <stdbool.h>
#include <stdio.h>

bool HaveDifferentSigns(int x, int y) {
  return (x * y) < 0;
  // return (x < 0 && y > 0) || (x > 0 && y < 0);
}

int main(int argc, char **argv) {
  int x, y;
  printf("Enter two integers: ");
  scanf("%d %d", &x, &y);
  
  if (HaveDifferentSigns(x, y)) {
    printf("Given integers have different signs.\n");
  } else {
    printf("Given integers have same sign.\n");
  }
  return 0;
}
