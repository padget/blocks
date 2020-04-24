#ifndef __blocks_compile_h__
#define __blocks_compile_h__
#include "../experimental/config.h"
#include "../experimental/blocks-std.h"


#ifndef BLOCKS_ARGS_MAXSIZE
#define BLOCKS_ARGS_MAXSIZE 10
#endif

typedef int error_code;

typedef struct
{
  chararray type;
  chararray value;
} bl_argument;

typedef struct
{
  chararray name;
  bl_argument args[BLOCKS_ARGS_MAXSIZE];
  error_code errcode;
} bl_command;

void bl_compile();

#endif