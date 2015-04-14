/*
 * Author      : Edward Xia
 * Description : Lab 2 - Fibonacci Sequence
 * Date        : 04/06/2015
 */

#include <stdio.h>

int main() {
  int n;
  printf("Enter a number: ");
  scanf("%d", &n);
  for (int i = 0, previous = 0, current = 1, tmp; i < n; tmp = current, current += previous, previous = tmp, ++i) {
    printf("%d\n", current);
  }
  return 0;
}
