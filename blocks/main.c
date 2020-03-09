#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../experimental/argument.h"

#define HELP "blocks-help.exe"
#define COMPILE "blocks-compile.exe"
#define EXECUTE "blocks-execute.exe"
#define REPORTS "blocks-reports.exe"
#define CLEAN "blocks-clean.exe"

size_t arguments_sum(int argc, char **argv);
char *build_command_call(const char *exe, int argc, char **argv);

int main(int argc, char **argv)
{
  const char *exe = HELP;
  printf("main");

  if (args_exists_at(argc, argv, "compile", 1))
    exe = COMPILE;
  else if (args_exists_at(argc, argv, "execute", 1))
    exe = EXECUTE;
  else if (args_exists_at(argc, argv, "reports", 1))
    exe = REPORTS;
  else if (args_exists_at(argc, argv, "clean", 1))
    exe = CLEAN;
  else
  {
    printf("une soucis d'arguemnt");
    exit(EXIT_FAILURE);
  }

  printf("%s", exe);
  char **exearg = args_subrange(argc, argv, 2);
  char *cmd = build_command_call(exe, argc - 2, exearg);

  system(cmd);

  free(cmd);
  return EXIT_SUCCESS;
}

char *build_command_call(const char *exe, int argc, char **argv)
{
  size_t sum = arguments_sum(argc, argv);
  size_t s_char = sizeof(char);
  size_t s_exe = strlen(exe);
  size_t s_cmd = s_char * (s_exe + argc + sum + 1);
  char *cmd = malloc(s_cmd);

  cmd[0] = '\0';

  strcat(cmd, exe);
  int i = 0;

  while (i < argc)
  {
    strcat(cmd, " ");
    strcat(cmd, argv[i]);
    ++i;
  }

  return cmd;
}

size_t arguments_sum(int argc, char **argv)
{
  size_t sum = 0;
  int i = 0;

  while (i < argc)
  {
    char *arg = argv[i];
    size_t sarg = strlen(arg);
    sum += sarg;
    ++i;
  }

  return sum;
}
