/*
 * Author      : Edward Xia
 * Description : Lab 4 - Selection Sort
 * Date        : 04/20/2015
 */

#include <stdio.h>

int index_of_min(int array[], size_t from, size_t to) {
  int index = from;
  for (++from; from < to; ++from) {
    if (array[from] < array[index]) {
      index = from;
    }
  }
  return index;
}

int main() {
  size_t size = 20;
  int A[size];
  for (size_t i = 0; i < size; ++i) {
    printf("Enter a number: ");
    scanf("%d", &A[i]);
  }
  int min_index, tmp;
  for (size_t i = 0; i < size; ++i) {
    min_index = index_of_min(A, i, size);
    tmp = A[min_index];
    A[min_index] = A[i];
    A[i] = tmp;
  }
  for (size_t i = 0; i < size; ++i) {
    printf("%d\n", A[i]);
  }
  return 0;
}
