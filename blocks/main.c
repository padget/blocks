#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../experimental/version.h"
#include "../experimental/log.h"
#include "../experimental/argument.h"
#include "../experimental/algorithm.h"
#include "../experimental/string.h"
#include "../experimental/keyword.h"

#include "clean.h"
#include "execute.h"
//#include "compile.h"

int main(int argc, char **argv)
{
  (void) argc;
  (void) argv;
 // char* compile = "compile";
  char* compile_deps = "true;;qsd";
  char* s = compile_deps;

  while (*s!='\0')
  {
    if (*s == ';')
      *s = 'c';
    ++s;
  }

  
  //make_sysarg(compile, compile_deps);



  // log_error("%d", sys.len);

  // if (args_exists("--file"))
  // {
  //   log_info("file arg found");

  //   sysarg *value = args_value("--file");

  //   if (value != NULL)
  //     log_info("found %s", (*value).arg);
  //   else
  //     log_error("no value found");
  // }

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
