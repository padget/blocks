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

typedef struct {
union {
file_error error;
FILE* file;
}
int tag;
} io_fopen_result;

typedef struct {
union {
file_error error;
size_t size;
}
int tag;
} io_fsize_result;


typedef struct {
union {
file_error error;
blocks_srange data;
}
int tag;
} io_freadall_result;


void blocks_fsize(FILE *file, io_fsize_result* res) ;
void blocks_fclose(FILE *file, io_fclose_result* res);
void blocks_fopen(const char *filename, io_fopen_result* res);
void blocks_freadall(FILE *file, io_freadall_result* res);
void blocks_fbuffer(FILE *file, io_fbuffer_result* res );

#endif
