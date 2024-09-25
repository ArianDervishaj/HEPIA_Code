#ifndef _SERIE_1_H_
#define _SERIE_1_H_

#include <stdbool.h>
#include <stdio.h>

struct replace {
  char *string;
  char new_char;
};

void ex1();
void ex2(struct replace *data);
bool test_ex2(struct replace *data);
char *ex3(struct replace *data);
#endif