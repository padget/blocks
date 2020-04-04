#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../experimental/log.h"
#include "../experimental/argument.h"

void call_compile();
void call_execute();
void call_clean();

int main(int argc, char **argv)
{
  args_init(argc, argv);
  char *verb = args_verb();

  if (strcmp(verb, "compile") == 0)
    call_compile();
  else if (strcmp(verb, "execute") == 0)
    call_execute();
  else if (strcmp(verb, "clean") == 0)
    call_clean();
  else
  {
    log_error("pas de verbe valide");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

void call_compile()
{
  log_info("call %s function", "compile");

  char *file_to_compile = NULL;
  char *build_directory = NULL;

  if (args_exists("--file") && args_has_value("--file"))
    file_to_compile = args_value("--file");

  if (args_exists("--builddir") && args_has_value("--builddir"))
    build_directory = args_value("--builddir");

  if (file_to_compile == NULL)
  {
    // FIXME there is an error :
    // file not indicated
    // call_compile_help()
  }

  if (build_directory == NULL)
    build_directory = ".";
}

void call_execute()
{
  printf("call execute");
}

void call_clean()
{
  printf("call clean");
}