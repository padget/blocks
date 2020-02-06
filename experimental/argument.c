#include "argument.h"

#include <string.h>

arguments args_from_argv(char** argv, size_t size)
{
  arguments args;
  args.args = argv;
  args.size = size;
  return args;
}

bool args_exists(arguments* args, const char* name)
{
  return args_find(args, name) == NULL;
} 

char* args_find(arguments* args, const char* name)
{
  if (args == NULL)
    return NULL;

  int i = args_pfind(args, name);

  if (i!=-1)
    return args->args[i];

  return NULL;
}

char* args_value(arguments* args, const char* name)
{
  if (args==NULL)
    return NULL;
  
  int i = args_pfind(args, name);

  if (i!=-1 && i+1<args->size)
    return args->args[i+1];

  return NULL;
}

argument args_argument(arguments* args, const char* name)
{
  argument arg;
  arg.name = NULL;
  arg.value = NULL;

  if (args == NULL)
    return arg; 

  int i = args_pfind(args, name);

  if (i!=-1)
  {
    arg.name = args->args[i];
    
    if (i+1 < args->size)
      arg.value = args->args[i+1];
  }

  return arg;
}

int args_pfind(arguments* args, const char* name)
{
  if (args==NULL)
    return -1;

  for (size_t i=0; i<args->size; ++i)
    if (strcmp(name, args->args[i])==0)
      return i;

  return -1;
}
