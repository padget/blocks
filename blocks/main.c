#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../experimental/log.h"
#include "../experimental/argument.h"

#include "clean.h" 
#include "execute.h"
#include "compile.h"


int main(int argc, char **argv)
{
  args_init(argc, argv);
  char *verb = args_verb();

  if (strcmp(verb, "compile") == 0)
    bl_compile();
  else if (strcmp(verb, "execute") == 0)
    bl_execute();
  else if (strcmp(verb, "clean") == 0)
    bl_clean();
  else
  {
    log_error("pas de verbe valide");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}