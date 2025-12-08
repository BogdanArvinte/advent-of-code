#ifndef _DAY1_H_
#define _DAY1_H_

#include <stdio.h>

#define START 50
#define MAX_CLICKS 100

typedef struct DialNumber {
  int index;
  struct DialNumber* prev;
  struct DialNumber* next;
} DialNumber;

DialNumber* create_dial(int size, int start);
void free_dial(DialNumber* dial);

void day1(void);

#endif
