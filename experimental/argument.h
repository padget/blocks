#ifndef __blocks_argument_h__
# define __blocks_argument_h__

# include "string.h"
# include <stdbool.h>

bool args_exists(int argc, char** argv, const char* name);

bool args_exists_at(int argc, char** argv, const char* name, int index);

char* args_find(int argc, char** argv, const char* name);

char* args_value(int argc, char**argv, const char* name);

char** args_subrange(int argc, char** arg, int index);

int args_ifind(int argc, char** argv, const char* name);
#endif
