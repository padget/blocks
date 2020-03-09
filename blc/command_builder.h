
#ifndef __blocks_command_builder_h__
#define __blocks_command_builder_h__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define CMD_NAME_MAX 50
#define ARG_VALUE_MAX 50
#define ARG_TYPE_MAX 50
#define ARGS_MAX 10
#define SIZEOF_COMMAND(nb) sizeof(blc_command) * (nb)
#define CMDS_MAX 10000

typedef struct
{
  char type[ARG_TYPE_MAX];
  char value[ARG_VALUE_MAX];
} blc_argument;

typedef int error_code;

typedef struct
{
  char name[CMD_NAME_MAX];
  blc_argument args[ARGS_MAX];
  error_code errcode;
} blc_command;

blc_command *
blc_cmds_init(size_t nb);

void blc_cmds_fill(size_t nb, blc_command *cmds, char *src);

#endif
