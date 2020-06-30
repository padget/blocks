#ifndef __blocks_std_arguments_h__
# define __blocks_std_arguments_h__
#include <stdbool.h>

struct arguments
{
  char** begin; 
  char** end;
};

typedef struct arguments arguments;

arguments args_new(char**begin, char**end);
void args_del(arguments args);

bool args_exists(arguments args, const char* arg);
char* args_value(arguments args, const char* arg);

#endif