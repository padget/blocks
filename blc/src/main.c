#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../../experimental/memory.h"
#include "../../experimental/string.h"
#include "../../experimental/vstring.h"
#include "../../experimental/argument.h"

#define SRC_FILENAME "examples/add.blocks"
#define FILE_READMODE "r"

int main(int argc, char** argv)
{
  printf("blocks-compile\n");
  arguments args = args_default();

  for (unsigned i=0; i<argc; ++i)
  {
    argument arg = arg_from_property(argv[i]);
    args = args_append(args, arg);
  }

  /* FILE* fsrc = fopen(SRC_FILENAME, FILE_READMODE); 

     if (fsrc == NULL)
     return EXIT_FAILURE;



     string src = s_construct_from_file(fsrc);
     cvstring cvs = cvs_construct(src.bstr, src.estr);
  //cvs_foreach(cvs, &printc);
  */
  args_free_arguments(args);
  return EXIT_SUCCESS;
}



