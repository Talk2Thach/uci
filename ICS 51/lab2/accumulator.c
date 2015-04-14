/*
 * Author      : Edward Xia
 * Description : Lab 2 - Accumulator
 * Date        : 04/06/2015
 */

#include <stdio.h>

int main() {
  int integer;
  printf("Enter a number: ");
  scanf("%d", &integer);
  int sum = 0;
  for (int i = 1; i < 2 * integer; i+=2) {
    sum+=i;
  }
  printf("%d\n", sum);
  return 0;
}
