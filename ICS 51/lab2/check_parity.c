/*
 * Author      : Edward Xia
 * Description : Lab 2 - Check Parity
 * Date        : 04/06/2015
 */

#include <stdio.h>

int main() {
  int integer;
  printf("Enter a number: ");
  scanf("%d", &integer);
  if (integer % 2 == 0) {
    printf("Even\n");
  } else {
    printf("Odd\n");
  }
  return 0;
}
