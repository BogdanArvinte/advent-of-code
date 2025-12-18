#include "day2.h"

#include <stdio.h>

#include "common.h"

void day2(void) {
  FILE* input = open_input_file("inputs/day2.txt");
  if (input == NULL) return;

  char line[512];
  long sum1 = 0;
  long sum2 = 0;

  while (fgets(line, sizeof(line), input) != NULL) {
    char** items = split_line(line, ',');

    int index = 0;
    while (items[index] != NULL) {
      long* range = parse_range(items[index]);
      sum1 += add_numbers_with_mirrored_duplicate_digits(range);
      sum2 += add_numbers_with_multiple_duplicate_digits(range);
      index++;
    }

    free(items);
  }

  printf("[Part 1] Sum of all numbers with duplicate mirrored digits: %ld\n",
         sum1);
  printf("[Part 2] Sum of all number with multiple duplicate digits: %ld\n",
         sum2);

  fclose(input);
}

char** split_line(char* line, const char delimiter) {
  int count = 0, index = 0, interval_index = 0;
  char* interval = malloc(32 * sizeof(char));
  char** items = malloc(32 * sizeof(interval));

  while (line[index] != '\0') {
    if (line[index] == delimiter || line[index] == '\n') {
      interval[interval_index] = '\0';
      interval_index = 0;
      items[count] = interval;
      interval = malloc(32 * sizeof(char));
      count++;
    } else {
      interval[interval_index++] = line[index];
    }
    index++;
  }
  items[count] = NULL;

  return items;
}

long* parse_range(char* str) {
  long start = 0, end = 0;
  sscanf(str, "%ld-%ld", &start, &end);

  long* range = malloc((end - start) * sizeof(long));
  int index = 0;

  while (start + index <= end) {
    range[index] = start + index;
    index++;
  }

  return range;
}

long add_numbers_with_mirrored_duplicate_digits(long* range) {
  long sum = 0;
  int index = 0;

  while (range[index] != '\0') {
    long number = range[index];
    int digit_count = count_digits(&number);

    if (digit_count > 1 && digit_count % 2 == 0) {
      int divisor = power(10, digit_count / 2);
      long first_half = number / divisor;
      long second_half = number % divisor;
      if (first_half == second_half) sum += number;
    }

    index++;
  }

  return sum;
}

long add_numbers_with_multiple_duplicate_digits(long* range) {
  long sum = 0;
  int index = 0;

  while (range[index] != '\0') {
    long number = range[index];
    int digit_count = count_digits(&number);

    if (number <= 10) {
      index++;
      continue;
    }

    if (is_number_with_identical_digits(number)) {
      sum += number;
    } else {
      int chunk_size = digit_count / 2;
      while (chunk_size > 1) {
        if (digit_count % chunk_size == 0) {
          int digit_pattern = number / power(10, digit_count - chunk_size);
          long pattern_number =
              create_pattern_number(digit_pattern, digit_count / chunk_size);
          if (number == pattern_number) {
            sum += number;
          }
        }
        chunk_size--;
      }
    }

    index++;
  }

  return sum;
}

int count_digits(long* number) {
  int count = 0;
  long num = *number;

  while (num > 0) {
    num /= 10;
    count++;
  }

  return count;
}

int power(int base, int exp) {
  int result = 1;

  for (int i = 0; i < exp; i++) {
    result *= base;
  }

  return result;
}

long create_pattern_number(long base, int count) {
  long number = 0;
  int digits = count_digits(&base);

  for (int i = 0; i < count; i++) {
    number = (number * power(10, digits)) + base;
  }

  return number;
}

int is_number_with_identical_digits(long number) {
  int digit_count = count_digits(&number);
  int first_digit = number % 10;

  for (int i = 0; i < digit_count; i++) {
    if (number % 10 != first_digit) return 0;
    number /= 10;
  }

  return 1;
}
