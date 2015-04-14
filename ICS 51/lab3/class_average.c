/*
 * Author      : Edward Xia
 * Description : Lab 3 - Class Average
 * Date        : 04/13/2015
 */

#include <stdio.h>

int main() {
  int sum = 0, number = 0, score;
  while (printf("Enter a number less than 100: ") && scanf("%d", &score) && score >= 0) {
    if (score > 100) {
      printf("Score > 100: %d, please retry.\n", score);
    } else {
      sum += score;
      ++number;
    }
  }
  printf("Total Number of Scores Entered:  %d\n", number);
  printf("Average:  %f\n", number == 0 ? 0 : sum / (double)number);
  return 0;
}
