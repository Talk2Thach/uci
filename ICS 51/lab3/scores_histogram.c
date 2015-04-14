/*
 * Author      : Edward Xia
 * Description : Lab 3 - Scores Histogram
 * Date        : 04/13/2015
 */

#include <stdio.h>

int main() {
  int distribute[10];
  for (int i = 0; i < 10; ++i) {
    distribute[i] = 0;
  }
  int score;
  while (printf("Enter grade, -1 to end: ") && scanf("%d", &score) && score >= 0) {
    if (score > 100) {
      printf("Score > 100: %d, please retry.\n", score);
    } else {
      if (score == 0) {
        ++distribute[0];
      } else {
        ++distribute[(score - 1)/ 10];
      }
    }
  }
  int sum = 0;
  for (int i = 0; i < 10; ++i) {
    sum += distribute[i];
  }
  printf("\n         ");
  for (int i = 0; i < 119; ++i) {
    printf("=");
  }
  printf("\n        |");
  for (int i = 1; i <= 20; ++i) {
    printf("%4d%%|", i * 5);
  }
  printf("\n         ");
  for (int i = 0; i < 119; ++i) {
    printf("=");
  }
  printf("\n");
  for (int i = 0; i < 10; ++i) {
    printf("| %2d-%-3d|", i * 10, i * 10 + 10);
    for (int j = 0; j < (distribute[i] == 0 ? 0 : distribute[i] * 20 / sum); ++j) {
      printf("===== ");
    }
    printf("\n");
  }
  return 0;
}
