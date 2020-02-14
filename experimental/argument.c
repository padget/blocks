#include "argument.h"

#include <string.h>
#include <stdlib.h>

bool args_exists(int argc, char** argv, const char* name)
{
  return args_find(argc, argv, name) != NULL;
}

bool args_exists_at(int argc, char** argv, const char* name, int index)
{
  if (argc == 0 || 
      name == NULL || 
      argv == NULL)
    return false;

  char* arg = argv[index];
  return strcmp(name, arg) == 0;
}

char* args_find(int argc, char** argv, const char* name)
{
  if (argc == 0 || 
      name == NULL || 
      argv == NULL)
    return false;

  int i = args_ifind(argc, argv, name);

  if (i!=-1)
    return argv[i];

  return NULL;
}

char* args_value(int argc, char** argv, const char* name)
{
  if (argc == 0 || 
      argv == NULL ||
      name == NULL) 
    return NULL;

  int i = args_ifind(argc, argv, name);

  if (i!=-1 && i+1<argc)
    return argv[i+1];

  return NULL;
}

char** args_subrange(int argc, char** argv, int index)
{
  if (argv == NULL ||
      argc == 0 ||
      index >= argc)
    return NULL;

  return argv + index;
}

#define NOT_FOUND -1

int args_ifind(int argc, char** argv, const char* name)
{
  if (argv == NULL ||
      argc == 0 ||
      name == NULL)
    return NOT_FOUND;

  int i=0;

  while (i<argc)
    if (strcmp(name, argv[i])==0)
      return i;
    else 
      ++i;
  
  return NOT_FOUND;
}

int args_as_num(int argc, char** argv, const char* name)
{
  char* value=args_value(argc, argv, name);
  char* prev=value;

  while ('0'<=*value&&*value<='9')
    value++;

  if (*value !='\0')
  {
    fprintf(stderr, "the argument %s : %s must be a number", name, prev);
    exit(EXIT_FAILURE);
  }

  return atoi(prev);
}
