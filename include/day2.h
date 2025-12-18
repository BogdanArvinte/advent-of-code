#ifndef _DAY2_H_
#define _DAY2_H_

#include <stdio.h>

void day2(void);
char** split_line(char* str, const char delimiter);
long* parse_range(char* str);
long add_numbers_with_mirrored_duplicate_digits(long* range);
long add_numbers_with_multiple_duplicate_digits(long* range);
long create_pattern_number(long base, int count);
int is_number_with_identical_digits(long number);
int count_digits(long* number);
int power(int base, int exp);

#endif
