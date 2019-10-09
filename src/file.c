#include "file.h"
#include "macro.h"
#include <stdint.h>

enum file_error blocks_fsize(FILE *file, size_t *size) {
  notnull(size);

  *size = 0;
  if (file == NULL)
    return FILE_NO_ERROR;
  if (fseek(file, 0, SEEK_END) != FILE_NO_ERROR)
    return FILE_SEEK_ERROR;
  uint64_t len = (uint64_t)ftell(file);
  if (fseek(file, 0, SEEK_SET) != FILE_NO_ERROR)
    return FILE_SEEK_ERROR;
  *size = len;
  return FILE_NO_ERROR;
}

enum file_error blocks_fclose(FILE *file) {
  notnull(file);

  return fclose(file) ? FILE_CLOSE_ERROR : FILE_NO_ERROR;
}

enum file_error blocks_fopen(const char *filename, FILE **file) {
  notnull(file);

  *file = fopen(filename, "r");
  return *file == NULL ? FILE_OPEN_ERROR : FILE_NO_ERROR;
}

enum file_error blocks_freadall(FILE *file, blocks_srange *range) {
  notnull(file);
  notnull(range);

  char *buffer = range->begin;
  int c;
  while ((c = (char)fgetc(file)) != EOF) {
    *buffer = c;
    buffer++;
  }
  *buffer = '\0';
  range->end = buffer;
  return FILE_NO_ERROR;
}

enum file_error blocks_build_buffer(FILE *file, blocks_srange *range) {
  notnull(file);
  notnull(range);

  char *buffer = NULL;
  size_t fsize = 0;
  enum file_error err = FILE_NO_ERROR;
  if ((err = blocks_fsize(file, &fsize)) != FILE_NO_ERROR)
    return err;
  buffer = malloc(fsize + 1);
  if (buffer == NULL)
    return FILE_BUFFER_ALLOCATION_ERROR;
  range->begin = buffer;
  range->end = buffer + fsize + 1;
  return FILE_NO_ERROR;
}
