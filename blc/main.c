#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../experimental/argument.h"
#include "../experimental/blocks-std.h"

#include "command_builder.h"

char *freadall(const char *);
size_t fsize(FILE *file);
void printcmds(int nb, blc_command *cmds);

int main(int argc, char **argv)
{
  if (!args_exists(argc, argv, "--file"))
    return EXIT_FAILURE;

  if (!args_exists(argc, argv, "--nb-cmds"))
    return EXIT_FAILURE;

  char *fname = args_value(argc, argv, "--file");
  int nbcmds = args_as_num(argc, argv, "--nb-cmds");
  char *src = freadall(fname);

  blc_command *cmds = blc_cmds_init(nbcmds);
  blc_cmds_fill(nbcmds, cmds, src);

  printcmds(nbcmds, cmds);

  free(cmds);
  free(src);

  return EXIT_SUCCESS;
}

void printcmds(int nb, blc_command *cmds)
{
  int i = 0;
  while (i < nb)
  {
    printf("command '%s'\n", cmds[i].name);

    int j = 0;

    while (j < ARGS_MAX)
    {
      if (cmds[i].args[j].value[0] != '\0')
        printf("  ->'%s' \n", cmds[i].args[j].value);

      j++;
    }
    ++i;
  }
}
