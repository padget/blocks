#ifndef __blocks_argument_h__
# define __blocks_argument_h__

# include <stdbool.h>


struct syscall
{
  int argc;
  char** argv; 
};

typedef struct syscall syscall;

struct sysargrule
{
	bool mandatory;
	const char* description;
};

typedef struct sysargrule sysargrule;

// an instance of syscall to have
// access to syscall args everywhere
// in the source code.
extern syscall sys;


void register_args(int argc, char** argv);
// TODO implement
void register_arg_rule(const char* name, sysargrule);

bool args_exists(const char* name);
char** args_value(const char* name);


#endif
