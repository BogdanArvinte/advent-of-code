#include "day1.h"

#include <stdio.h>

#include "common.h"

void day1(void) {
  FILE* input = open_input_file("inputs/day1.txt");
  if (input == NULL) return;

  DialNumber* dial = create_dial(MAX_CLICKS, START);
  char line[32];
  char direction;
  int clicks;
  int stops_at_zero = 0;
  int passess_through_zero = 0;

  while (fgets(line, sizeof(line), input) != NULL) {
    sscanf(line, " %c%d", &direction, &clicks);
    while (clicks > 0) {
      if (direction == 'L')
        dial = dial->prev;
      else
        dial = dial->next;

      if (dial->index == 0) passess_through_zero++;

      clicks--;
    }

    if (dial->index == 0) stops_at_zero++;
  }

  printf("[Part 1] Times we stopped at 0: %d\n", stops_at_zero);
  printf("[Part 2] Time we passed through 0: %d\n", passess_through_zero);

  free_dial(dial);
  fclose(input);
}

DialNumber* create_dial(int size, int start) {
  DialNumber* starting_position = NULL;
  DialNumber* head = NULL;
  DialNumber* next = NULL;

  size = size - 1;

  while (size >= 0) {
    DialNumber* new_number = (DialNumber*)malloc(sizeof(DialNumber));
    new_number->index = size;
    new_number->prev = NULL;
    new_number->next = NULL;

    if (head == NULL) {
      head = new_number;
      next = head;
    } else {
      next->prev = new_number;
      new_number->next = next;
    }

    if (size == 0) {
      head->next = new_number;
      new_number->prev = head;
    } else {
      next = new_number;
    }

    if (size == start) {
      starting_position = new_number;
    }

    size--;
  }

  return starting_position;
}

void free_dial(DialNumber* dial) {
  DialNumber* current = dial;
  DialNumber* to_free = NULL;

  while (current != NULL) {
    to_free = current;
    to_free->prev = NULL;
    to_free->next = NULL;
    current = current->next;
    free(to_free);
  }
}
