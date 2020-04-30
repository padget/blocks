#include "compile.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../experimental/argument.h"
#include "../experimental/log.h"
#include "../experimental/i18n.h"

#define EOS '\0'
#define EOL '\n'

typearrayimpl(bl_argument)
typearrayimpl(bl_type_attribute)


void bl_compile()
{
 /* chararray src;
  size_t nb = 0;
  bl_command *cmds = NULL;
  chararray fname;

  if (args_has_value("--file"))
  {
    fname.data = args_value("--file");
    fname.len = strlen(fname.data);
  }
  else
  {
    if (args_exists("--file"))
      log_error(blocks_log_argument_file_no_value);
    else
      log_error(blocks_log_argument_file_mandatory);
    goto finally;
  }

  src = freadall(fname.data);

  if (chara_len(src) == 0)
  {
    log_warn(blocks_log_no_content_in_file, fname);
    goto finally;
  }

  nb = nb_not_blank_lines(src);

  if (nb == 0)
  {
    log_warn(blocks_log_no_command);
    goto finally;
  }

  cmds = bl_cmds_init(nb);
  cmds_fill(cmds, nb, src);

  size_t nbbytes = size_of_commands_int(cmds, nb);
  nbbytes += 1;
  int *bytecodes = calloc(nbbytes, sizeof(int));

  if (bytecodes == NULL)
  {
    log_error(blocks_log_memory_allocation);
    goto finally;
  }

  on_cmds_filled(cmds, nb);

finally:
  free(bytecodes);
  free(&src);
  free(cmds);*/
}