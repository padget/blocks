#ifndef __blocks_argument_h__
#define __blocks_argument_h__

#include <stdbool.h>
#include <stdlib.h>

#include "string.h"

typedef struct system_argument_rule sysargrule;

struct system_argument
{
  const char *arg;
  const char *rule;
};

typedef struct system_argument sysarg;

struct system_call
{
  sysarg *args;
  size_t len;
};

typedef struct system_call syscall;

// an instance of syscall to have
// access to syscall args everywhere
// in the source code.
extern syscall sys;

sysarg make_sysarg(const char *arg, const char *rule);

bool define_sysargs(sysarg *args, size_t nbargs);

bool check_args(int argc, char **argv);

sysarg *args_value(const char *name);

#endif
