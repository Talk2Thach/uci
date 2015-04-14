/*
 * Author      : Edward Xia
 * Description : Lab 5 - Warm Up 1
 * Date        : 04/27/2015
 */

#include <stdio.h>

int main () {
  int no = 100, val;
  // val = no;
  __asm__ __volatile__ (
      "mov ebx, %1;"
      "mov %0, ebx;"
      :"=r" (val)
      :"r" (no)
      :"ebx"
  );
  printf("%d\n", val);
  return 0;
}
