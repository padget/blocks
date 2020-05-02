#ifndef __blocks_argument_h__
# define __blocks_argument_h__

# include <stdbool.h>


struct syscall
{
  int argc;
  char** argv; 
};

typedef struct syscall syscall;

// an instance of syscall to have
// access to syscall args everywhere
// in the source code.
extern syscall sys;


void register_args(int argc, char** argv);

bool args_exists(const char* name);
char** args_value(const char* name);


#endif
