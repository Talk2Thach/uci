/*
 * Author      : Edward Xia
 * Description : Lab 9 - Rolodex
 * Date        : 05/27/2015
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <limits.h>

#ifndef LINE_MAX
#define LINE_MAX 509
#endif

#define ROLODEX_INITIAL_CAPACITY 64

struct contact {
  char last_name[LINE_MAX];
  char first_name[LINE_MAX];
  char phone_number[LINE_MAX];
};

int contactcmp(const struct contact *c1, const struct contact *c2) {
  int result = strcasecmp(c1->last_name, c2->last_name);
  if (result == 0) {
    return strcasecmp(c1->first_name, c2->first_name);
  }
  return result;
}

struct rolodex {
  size_t size;
  size_t capacity;
  bool sorted;
  struct contact *data;
};

void rolodex_init(struct rolodex *r) {
  r->size = 0;
  r->capacity = ROLODEX_INITIAL_CAPACITY;
  r->sorted = true;
  r->data = malloc(sizeof(struct contact) * r->capacity);
}

void rolodex_add(struct rolodex *r, struct contact *c) {
  if (r->size >= r->capacity) {
    r->capacity *= 2;
    r->data = realloc(r->data, sizeof(struct contact) * r->capacity);
  }
  r->sorted = false;
  r->data[r->size++] = *c;
}

void rolodex_load(struct rolodex *r, const char *filename) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    fprintf(stderr, "Can't open %s for reading.\n", filename);
    return;
  }

  struct contact c;
  while (fscanf(fp, "%s %s %s", c.last_name, c.first_name, c.phone_number) != EOF) {
    rolodex_add(r, &c);
  }

  fclose(fp);
}

void rolodex_print(struct rolodex *r) {
  for (size_t i = 0; i < r->size; ++i) {
    printf("%zu %s %s %s\n", i, r->data[i].last_name, r->data[i].first_name, r->data[i].phone_number);
  }
}

void rolodex_save(struct rolodex *r, const char *filename) {
  FILE *fp = fopen(filename, "w");
  if (fp == NULL) {
    fprintf(stderr, "Can't open %s for writing.\n", filename);
    return;
  }

  for (size_t i = 0; i < r->size; ++i) {
    fprintf(fp, "%s %s %s\n", r->data[i].last_name, r->data[i].first_name, r->data[i].phone_number);
  }

  fclose(fp);
}

void rolodex_binary_search(struct rolodex *r, const char *last_name) {
  if (r->size == 0) {
    return;
  }
  size_t imin = 0, imax = r->size - 1;
  while (imax >= imin) {
    size_t i = imin + ((imax - imin) / 2);
    int result = strcasecmp(r->data[i].last_name, last_name);
    if (result == 0) {
      for (imin = i; imin > 0 && strcasecmp(r->data[imin - 1].last_name, last_name) == 0; --imin) {}
      for (imax = i; imax < r->size - 1 && strcasecmp(r->data[imax + 1].last_name, last_name) == 0; ++imax) {}
      for (i = imin; i <= imax; ++i) {
        printf("%zu %s %s %s\n", i, r->data[i].last_name, r->data[i].first_name, r->data[i].phone_number);
      }
      return;
    } else if (result < 0) {
      ++imin;
    } else {
      --imax;
    }
  }
}

void rolodex_linear_search(struct rolodex *r, const char *last_name) {
  for (size_t i = 0; i < r->size; ++i) {
    if (strcasecmp(r->data[i].last_name, last_name) == 0) {
      printf("%zu %s %s %s\n", i, r->data[i].last_name, r->data[i].first_name, r->data[i].phone_number);
    }
  }
}

void rolodex_lookup(struct rolodex *r, const char *last_name) {
  if (r->sorted) {
    rolodex_binary_search(r, last_name);
  } else {
    rolodex_linear_search(r, last_name);
  }
}

bool rolodex_delete(struct rolodex *r, const char *last_name) {
  size_t size = r->size;
  for (size_t i = 0; i < r->size; ++i) {
    if (strcasecmp(r->data[i].last_name, last_name) == 0) {
      --r->size;
      for (size_t j = i; j < r->size; ++j) {
        r->data[j] = r->data[j + 1];
      }
      --i;
    }
  }
  return size != r->size;
}

void rolodex_sort(struct rolodex *r) {
  for (size_t i = 1; i < r->size; ++i) {
    struct contact c = r->data[i];
    size_t j = i;
    while (j > 0 && contactcmp(&r->data[j - 1], &c) > 0) {
      r->data[j] = r->data[j - 1];
      --j;
    }
    r->data[j] = c;
  }
  r->sorted = true;
}

void rolodex_free(struct rolodex *r) {
  free(r->data);
}

int main(int argc, char *argv[]) {
  char *filename;
  struct rolodex r;
  rolodex_init(&r);

  if (argc > 1) {
    filename = argv[1];
  } else {
    filename = "myRolodex";
  }

  rolodex_load(&r, filename);

  char action;
  char last_name[LINE_MAX];
  struct contact c;
  while (printf("%s Command: ", filename) && scanf(" %c", &action) && action != 'Q' && action != 'q') {
    switch (action) {
      case 'I':
      case 'i':
        printf("Enter card: last first phone\n");
        scanf("%s %s %s", c.last_name, c.first_name, c.phone_number);
        rolodex_add(&r, &c);
        break;
      case 'P':
      case 'p':
        rolodex_print(&r);
        break;
      case 'D':
      case 'd':
        printf("Enter last name of card to remove\n");
        scanf("%s", last_name);
        rolodex_delete(&r, last_name);
        break;
      case 'L':
      case 'l':
        printf("Enter last name of card to lookup\n");
        scanf("%s", last_name);
        rolodex_lookup(&r, last_name);
        break;
      case 'S':
      case 's':
        rolodex_sort(&r);
        break;
      default:
        break;
    }
    printf("\n");
  }

  rolodex_save(&r, filename);

  rolodex_free(&r);

  return 0;
}
