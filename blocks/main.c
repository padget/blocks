#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "../std/string.h"
#include "../std/keyword.h"

#define MANDATORY true

int main(int argc, char **argv)
{
  unused(argc);
  unused(argv);
  string_r strr = strr_from("hello world !");
  strr_iterator cfound = strr_find(strr, 'h');
  printf("%c", *cfound);

  // sysarg compile_arg = make_sysarg("compile", MANDATORY, 1, "");
  // sysarg execute_arg = make_sysarg("execute", MANDATORY, 1, "");
  // sysarg file_arg = make_sysarg("file", MANDATORY, 2, "compile|execute");
  // sysarg args[] = {compile_arg, execute_arg, file_arg}; 
 
  // if (define_sysargs(args, 3))
  // {
  //   if (not check_args(argc, argv))
  //   {
  //     log_error("des erreurs d'argument detecté");
  //   }
  //   else 
  //   {
  //     log_info("tout va bien");
  //   }
  // }
  // else 
  // {
  //   log_error("un soucis ");
  // }



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
