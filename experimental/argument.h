#ifndef __blocks_argument_h__
# define __blocks_argument_h__

# include <stdbool.h>

void args_init(int argc, char** argv);

bool args_exists(const char* name);

bool args_exists_at(const char* name, int index);

char* args_find(const char* name);

char* args_value(const char* name);

bool args_has_value(const char* name);

char** args_subrange(int index);

int args_ifind(const char* name);

int args_as_num(const char* name);

char* args_verb();

typedef 
struct syscall
{
  int argc;
  char** argv; 
} 
syscall;

extern syscall sys;

#endif
