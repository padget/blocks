#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../../experimental/argument.h"
#include "../../experimental/string.h"

#define SRC_FILENAME "examples/add.blocks"
#define FILE_READMODE "r"


/**
 * --file <file to compile>
 */
int main(int argc, char** argv)
{
  printf("blocks-compile\n");

  arguments args = args_from_argv(argv, argc);

  if (!args_exists(&args, "--file"))
    return EXIT_FAILURE;
  
  argument filearg = args_argument(&args, "--file");

  FILE* srcfile = fopen(filearg.value, FILE_READMODE);

  if (!srcfile)
  {
    perror("oops");
    return EXIT_FAILURE;
  }

  string source = s_from_file(srcfile);  
  
  printf("%s", source.data);  

  s_free(source);
  return EXIT_SUCCESS;
}

