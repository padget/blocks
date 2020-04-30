#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../experimental/version.h"
#include "../experimental/log.h"
#include "../experimental/argument.h"
#include "../experimental/algorithm.h"

#include "clean.h"
#include "execute.h"
#include "compile.h"

struct array
{
  void *begin;
  void *end;
  size_t len;
};

typedef struct array array;

typedef void *iterator;
typedef const void * const_iterator;

size_t len(array *a)
{
  return a != NULL && a->begin != NULL && a->end != NULL ? a->len : 0;
}

bool empty(array *a)
{
  return len(a) == 0;
}

iterator begin(array *a)
{
  return a != NULL ? a->begin : NULL;
}

iterator end(array *a)
{
  return a != NULL ? a->end : NULL;
}

iterator nextarg2(iterator arg)
{
  return (iterator)(((char **)arg) + 1);
}

bool equals(const_iterator arg1, const void* arg2)
{
  return (strcmp(*(const char**)arg1, (const char*)arg2) == 0);
}

int main(int argc, char **argv)
{

  array args = {.begin = (void *)argv, .end = (void *)(argv + argc), .len = argc};

  iterator b = begin(&args);
  iterator e = end(&args);

  char **arg = find(b, e, "--file", (alctxt_t){.next = nextarg2, .equals=equals});
  log_info(*arg);
  // args_init(argc, argv);
  // char *verb = args_verb();

  // if (strcmp(verb, "compile") == 0)
  //   bl_compile();
  // else if (strcmp(verb, "execute") == 0)
  //   bl_execute();
  // else if (strcmp(verb, "clean") == 0)
  //   bl_clean();
  // else if (strcmp(verb, "version") == 0)
  //   printf("Blocks version : %s\n", BLOCKS_VERSION);
  // else
  // {
  //   log_error("pas de verbe valide");
  //   return EXIT_FAILURE;
  // }

  return EXIT_SUCCESS;
}