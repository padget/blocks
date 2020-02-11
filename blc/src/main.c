#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../../experimental/argument.h"
#include "../../experimental/string.h"

#define SRC_FILENAME "examples/add.blocks"
#define FILE_READMODE "r"

string extract_source(const char*);

/**
 * --file <file to compile>
 */
int main(int argc, char** argv)
{
  arguments args = args_from_argv(argv, argc);

  if (!args_exists(&args, "--file"))
    return EXIT_FAILURE;
  
  argument filearg = args_argument(&args, "--file");
  string source = extract_source(filearg.value);
   
  
  printf("%s", source.data);  

  s_free(source);
  return EXIT_SUCCESS;
}

string extract_source(const char* filename)
{
  FILE* srcfile = fopen(filename, FILE_READMODE);

  if (!srcfile)
  {
    perror("oops");
    exit(EXIT_FAILURE);
  }

  return s_from_file(srcfile);
}

