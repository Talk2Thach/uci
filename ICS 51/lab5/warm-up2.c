/*
 * Author      : Edward Xia
 * Description : Lab 5 - Warm Up 2
 * Date        : 04/27/2015
 */

#include <stdio.h>

int main () {
  int arg1, arg2, sum;
  printf("Enter a number: ");
  scanf("%d", &arg1);
  printf("Enter a number: ");
  scanf("%d", &arg2);

  //sum = arg1 + arg2;
  __asm__ __volatile__ (
      "mov %0, %1;"
      "add %0, %2;"
      :"=r" (sum)
      :"r" (arg1), "r" (arg2)
  );
  printf("%d\n", sum);
  return 0;
}
