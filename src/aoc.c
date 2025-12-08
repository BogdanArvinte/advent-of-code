#include "aoc.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <day_number>\n", argv[0]);
    return EXIT_FAILURE;
  }

  int day = atoi(argv[1]);

  switch (day) {
    case 1:
      extern void day1(void);
      day1();
      break;
    // Add more cases for additional days as needed
    default:
      fprintf(stderr, "Day %d is not implemented yet.\n", day);
      return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
