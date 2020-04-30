#include "argument.h"
#include "log.h"
#include "i18n.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define NOT_FOUND -1

syscall sys;

void args_init(int argc, char **argv)
{
  sys.argc = argc;
  sys.argv = argv;
}

bool args_exists(const char *name)
{
  return args_find(name) != NULL;
}

bool args_exists_at(const char *name, int index)
{
  if (sys.argc <= index ||
      name == NULL ||
      sys.argv == NULL)
    return false;

  char *arg = sys.argv[index];
  return strcmp(name, arg) == 0;
}

char *args_find(const char *name)
{

  int i = args_ifind(name);

  if (i != -1)
    return sys.argv[i];

  return NULL;
}

#include "algorithm.h"

void *nextarg(void *arg)
{
  return (char **)arg + 1;
}

char *args_value(const char *name)
{
  char **arr = sys.argv;
  char **begin = arr;
  char **end = arr + sys.argc;
  char **found = find(begin, end, name, (alctxt_t){.next = nextarg});
  return found + 1 != end ? *(found + 1) : NULL;
}

bool args_has_value(const char *name)
{

  char *value = args_value(name);

  if (value != NULL)
    if (strlen(value) >= 2)
      if (value[0] != '-' && value[1] != '-')
        return true;

  return false;
}

char **args_subrange(int index)
{
  if (sys.argv == NULL ||
      sys.argc == 0 ||
      index >= sys.argc)
    return NULL;

  return sys.argv + index;
}

int args_ifind(const char *name)
{
  if (sys.argv == NULL ||
      sys.argc == 0 ||
      name == NULL)
    return NOT_FOUND;

  int i = 0;

  while (i < sys.argc)
    if (strcmp(name, sys.argv[i]) == 0)
      return i;
    else
      ++i;

  return NOT_FOUND;
}

int args_as_num(const char *name)
{
  char *value = args_value(name);
  // FIXME the returne value can be NULL
  char *prev = value;

  while ('0' <= *value && *value <= '9')
    value++;

  if (*value != '\0')
  {
    log_error(blocks_log_argument_must_be_number, name, prev);
    exit(EXIT_FAILURE);
  }

  return atoi(prev);
}

char *args_verb()
{
  if (sys.argc >= 1)
    return sys.argv[1];
  else
    return NULL;
}

#undef NOT_FOUND