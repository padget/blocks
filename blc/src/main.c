#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../../experimental/argument.h"
#include "../../experimental/string.h"

//#include "command_builder.h"

char* freadall(const char*);
size_t fsize(FILE* file);

int main(int argc, char** argv)
{
  
  if (!args_exists(argc, argv, "--file"))
    return EXIT_FAILURE;
  
  char* fname = args_value(argc, argv, "--file");
  printf("file to read%s\n", fname);

  char* src = freadall(fname);
  
  printf("%s", src);  

  free(src);
  return EXIT_SUCCESS;
}

char* freadall(const char* fname)
{
  FILE* file = fopen(fname, "r");
  
  if (!file)
  {
    perror("oops");
    exit(EXIT_FAILURE);
  }
  
  size_t s     = fsize(file);
  size_t schar = sizeof(char);
  char* cstr   = malloc(s*schar+1);
  char* cursor = cstr;
  int c;
  
  while ((c=fgetc(file))!=EOF)
  {
    *cursor = c;
    ++cursor; 
  }
  
  *cursor = '\0';

  return cstr;
}

size_t fsize(FILE* f)
{
  fseek(f, 0L, SEEK_END);
  unsigned size = ftell(f);
  fseek(f, 0L, SEEK_SET);  
  return size;
}

