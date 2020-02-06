#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../experimental/argument.h"

#define FIRST_ARG 1
#define SECOND_ARG 2

#define HELP    "blocks-help.exe"
#define COMPILE "blocks-compile.exe"
#define EXECUTE "blocks-execute.exe"
#define REPORTS "blocks-reports.exe"
#define CLEAN   "blocks-clean.exe"

size_t arguments_sum_sizes(arguments* args);
char* concat_name_arguments(const char* exe, arguments* args);


int main(int argc, char** argv)
{
  const char* exe = HELP;

  arguments args = args_from_argv(argv, argc);

  if (args_exists_at(&args, "compile", FIRST_ARG))
    exe = COMPILE;
  else if (args_exists_at(&args, "execute", FIRST_ARG))
    exe = EXECUTE;
  else if (args_exists_at(&args, "reports", FIRST_ARG))
    exe = REPORTS;
  else if (args_exists_at(&args, "clean", FIRST_ARG))
    exe = CLEAN;


  arguments subargs = args_subrange(&args, SECOND_ARG);
  char* cmd = concat_name_arguments(exe, &subargs);
  
  system(cmd);
  
  free(cmd);
  return EXIT_SUCCESS;
}

char* concat_name_arguments(const char* exe, arguments* args)
{
  size_t size = arguments_sum_sizes(args);
  char* cmd = malloc(sizeof(char) * (size + 1 + strlen(exe)+args->size));
  cmd[0] = '\0';

  strcat(cmd, exe);
  for (int i=0; i<args->size; ++i)
  {
    strcat(cmd, " ");
    strcat(cmd, args_at(args, i));
  }
  return cmd;

}

size_t arguments_sum_sizes(arguments* args)
{
  size_t size = 0;

  for (int i=0; i<args->size; ++i)
    size += strlen(args_at(args, i));

  return size;
}
