#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../../experimental/string.h"
#include "../../experimental/argument.h"

#define SRC_FILENAME "examples/add.blocks"
#define FILE_READMODE "r"

int main(int argc, char** argv)
{
  printf("blocks-compile\n");
  arguments args = args_from_argv(argv, argc);
  argument arg = args_argument(&args, "test");
  printf("%s => %s", arg.name, arg.value);
  return EXIT_SUCCESS;
}



