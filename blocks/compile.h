#ifndef __blocks_compile_h__
#define __blocks_compile_h__
#include "../experimental/config.h"

#ifndef BLOCKS_CMD_NAME_MAXSIZE
#define BLOCKS_CMD_NAME_MAXSIZE 50
#endif

#ifndef BLOCKS_ARG_VALUE_MAXSIZE
#define BLOCKS_ARG_VALUE_MAXSIZE 50
#endif

#ifndef BLOCKS_ARG_TYPE_MAXSIZE
#define BLOCKS_ARG_TYPE_MAXSIZE 50
#endif

#ifndef BLOCKS_ARGS_MAXSIZE
#define BLOCKS_ARGS_MAXSIZE 10
#endif

#ifndef BLOCKS_CMDS_MAXSIZE
#define BLOCKS_CMDS_MAXSIZE 10000
#endif

typedef int error_code;

typedef struct
{
  char type[BLOCKS_ARG_TYPE_MAXSIZE];
  char value[BLOCKS_ARG_VALUE_MAXSIZE];
} bl_argument;

typedef struct
{
  char name[BLOCKS_CMD_NAME_MAXSIZE];
  bl_argument args[BLOCKS_ARGS_MAXSIZE];
  error_code errcode;
} bl_command;



void bl_compile();

#endif