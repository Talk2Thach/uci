/*
 * Author      : Edward Xia
 * Description : Lab 3 - Letter Grade
 * Date        : 04/13/2015
 */

#include <stdio.h>

int main() {
  int sumA = 0, sumB = 0, sumC = 0, sumD = 0, sumF =0;
  char grade;
  while (printf("Enter a score: ") && scanf(" %c", &grade) && grade != 'Z') {
    switch (grade) {
      case 'A':
        ++sumA;
        break;
      case 'B':
        ++sumB;
        break;
      case 'C':
        ++sumC;
        break;
      case 'D':
        ++sumD;
        break;
      case 'F':
        ++sumF;
        break;
      default:
        printf("Not a vaild score: %c, please try again.\n", grade);
    }
  }
  printf("Total Number of Scores Entered:  %d\n", sumA + sumB + sumC + sumD + sumF);
  printf("A: %d\n", sumA);
  printf("B: %d\n", sumB);
  printf("C: %d\n", sumC);
  printf("D: %d\n", sumD);
  printf("F: %d\n", sumF);
  return 0;
}
