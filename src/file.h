#ifndef __blocks_file_h__
#define __blocks_file_h__

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "srange.h"

enum file_error {
  FILE_NO_ERROR = 0,
  FILE_READ_ERROR,
  FILE_SEEK_ERROR,
  FILE_CLOSE_ERROR,
  FILE_OPEN_ERROR,
  FILE_BUFFER_ALLOCATION_ERROR
};

enum file_error blocks_fsize(FILE *file, size_t *size) ;
enum file_error blocks_fclose(FILE *file);
enum file_error blocks_fopen(const char *filename, FILE **file);
enum file_error blocks_freadall(FILE *file, blocks_srange *range);
enum file_error blocks_build_buffer(FILE *file, blocks_srange *range);

#endif