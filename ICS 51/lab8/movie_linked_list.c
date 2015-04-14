/*
 * Author      : Edward Xia
 * Description : Lab 8 - Movie Linked List
 * Date        : 05/18/2015
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_LENGTH 10

struct movie {
  char title[250];
  int year;
  unsigned char rating;
  struct movie *next;
};

typedef struct movie movie;

int main() {
  size_t length = 0;
  movie *head = NULL;
  movie *tail = NULL;
  char action;
  char query[250];

  while (printf("%ld Movie(s) in the database. Update, Search, or Quit (U/S/Q): ", length) && scanf(" %c", &action) && action != 'Q') {
    switch (action) {
      case 'U':
        if (head == NULL) {
          tail = malloc(sizeof(movie));
          head = tail;
        } else {
          tail->next = malloc(sizeof(movie));
          tail = tail->next;
        }

        tail->next = NULL;
        printf("Name of the movie: ");
        scanf(" %[^\n]%*c", tail->title);
        printf("Year: ");
        scanf("%d", &tail->year);
        printf("Rating: ");
        scanf("%hhu", &tail->rating);

        ++length;
        printf("Movie \"%s\" is added to the database.\n", tail->title);
        break;
      case 'S':
        printf("Name of the movie: ");
        scanf(" %[^\n]%*c", query);

        movie *node = head;
        for (; node != NULL; node = node->next) {
          if (strcmp(query, node->title) == 0) {
            break;
          }
        }

        if (node == NULL) {
          printf("Movie \"%s\" does not exist in the database.\n", query);
        } else {
          printf("Year: %d\n", node->year);
          printf("Rating: %hhu\n", node->rating);
        }

        break;
      default:
        break;
    }
    printf("\n");
  }

  for (movie *node = head; head != NULL; node = head) {
    head = node->next;
    free(node);
  }

  return 0;
}
