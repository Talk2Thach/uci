/*
 * Author      : Edward Xia
 * Description : Lab 6 - String Concatenation
 * Date        : 05/04/2015
 */

#include <stdio.h>
#include <stdlib.h>

#define str_length 250

void str_concat(char* str1, char* str2, char* str) {
  // get length of first str
  int i = 0, j = 0;
  for (; i < str_length && *(str1 + i) != '\0'; ++i) {
    *(str + i) = *(str1 + i);
  }
  for (; i + j < str_length && *(str2 + j) != '\0'; ++j) {
    *(str + i + j) = *(str2 + j);
  }
  *(str + i + j + 1) = '\0';
}

int main() {
  char* str1 = malloc(sizeof(char) * str_length);
  char* str2 = malloc(sizeof(char) * str_length);
  char* str = malloc(sizeof(char) * str_length);
  printf("Enter a string: ");
  scanf("%s", str1);
  printf("Enter a string: ");
  scanf("%s", str2);
  str_concat(str1, str2, str);
  printf("%s\n", str);
  free(str1);
  free(str2);
  free(str);
  return 0;
}
