#include "common.h"

FILE *open_input_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "Error opening file \"%s\"", filename);
    exit(EXIT_FAILURE);
  }
  return file;
}
