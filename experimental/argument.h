#ifndef __blocks_argument_h__
#define __blocks_argument_h__

#include <stdbool.h>
#include <stdlib.h>

#include "string.h"



struct system_argument_rule
{
  bool mandatory;
  const char *description;
};

typedef struct system_argument_rule sysargrule;



struct system_argument
{
  const char* arg;
  sysargrule rule;
};

typedef struct system_argument sysarg;



struct system_call
{
  sysarg* args;
  size_t len;
};

typedef struct system_call syscall;



// an instance of syscall to have
// access to syscall args everywhere
// in the source code.
extern syscall sys;



bool register_args(int argc, char **argv);
bool register_arg_rule(const char *name, sysargrule rule);
bool clear_args();


bool args_exists(const char *name);
sysarg *args_value(const char *name);



#endif
