#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../../experimental/memory.h"
#include "../../experimental/string.h"
#include "../../experimental/vstring.h"

#define SRC_FILENAME "examples/add.blocks"
#define FILE_READMODE "r"

memory mem;

void printc(const char* c) {
  putchar(*c);
}

int main()
{

  FILE* fsrc = fopen(SRC_FILENAME, FILE_READMODE); 

  if (fsrc == NULL)
    return EXIT_FAILURE;


  string src = s_construct_from_file(fsrc);
  cvstring cvs = cvs_construct(src.bstr, src.estr);
  cvs_foreach(cvs, &printc);

  return EXIT_SUCCESS;
}


