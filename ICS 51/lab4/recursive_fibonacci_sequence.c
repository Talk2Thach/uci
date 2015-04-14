/*
 * Author      : Edward Xia
 * Description : Lab 4 - Recursive Fibonacci Sequence
 * Date        : 04/20/2015
 */

#include <stdio.h>

int fibonacci(int n) {
  if (n < 1) {
    return 0;
  } else if (n == 1) {
    return 1;
  } else {
    return fibonacci(n - 1) + fibonacci(n - 2);
  }
}

int main() {
  int n;
  printf("Enter a number: ");
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    printf("%d\n", fibonacci(i));
  }
  return 0;
}
