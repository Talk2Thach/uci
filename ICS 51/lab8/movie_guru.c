/*
 * Author      : Edward Xia
 * Description : Lab 8 - Movie Guru
 * Date        : 05/18/2015
 */

#include <stdio.h>

#define ARRAY_LENGTH 10

struct movie {
  char title[250];
  int year;
  unsigned char rating;
};

typedef struct movie movie;

int index_of_max(movie array[], size_t from, size_t to) {
  int index = from;
  for (++from; from < to; ++from) {
    if (array[from].rating > array[index].rating || (array[from].rating == array[index].rating && array[from].year < array[index].year) ) {
      index = from;
    }
  }
  return index;
}

int main() {
  size_t size = ARRAY_LENGTH;
  movie movies[size];
  for (size_t i = 0; i < size; ++i) {
    printf("Enter info for movie %ld:\n", i + 1);
    printf("Name of the movie: ");
    scanf(" %[^\n]%*c", movies[i].title);
    printf("Year: ");
    scanf("%d", &movies[i].year);
    printf("Rating: ");
    scanf("%hhu", &movies[i].rating);
    printf("\n");
  }
  int max_index;
  movie tmp;
  for (size_t i = 0; i < size; ++i) {
    max_index = index_of_max(movies, i, size);
    tmp = movies[max_index];
    movies[max_index] = movies[i];
    movies[i] = tmp;
  }
  printf("==============Sorted List==============\n");
  for (size_t i = 0; i < size; ++i) {
    printf("(%ld)\n", i + 1);
    printf("Name of the movie: %s\n", movies[i].title);
    printf("Year: %d\n", movies[i].year);
    printf("Rating: %hhu\n", movies[i].rating);
    printf("\n");
  }
  return 0;
}
