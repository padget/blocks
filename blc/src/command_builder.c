#include "command_builder.h"
#include <stdlib.h>

static inline void 
null_init(char* cstr)
{
  *cstr = '\0';
}

blc_commands_memory
cmdm_init(size_t nb)
{
  
  blc_commands_memory cmdm;
  blc_command* mem = malloc(SIZEOF_COMMAND(nb));
  
  size_t i=0;
  
  while (i<nb)
  {
    blc_command* cmd = &mem[i];
    null_init(cmd->name);
    
    size_t j=0;
    
    while (j<ARGS_MAX)
    {
      blc_argument* arg = &cmd->args[j];
      null_init(arg->type);
      null_init(arg->value); 
      j++;
    }
    
    i++;
  }
  
  cmdm.mem = mem;
  cmdm.size = nb;
  
  return cmdm;
}

void cmdm_at(blc_commands*)

void cmdm_fill(blc_commands_memory* cmdm, 
               string* source)
{
}

cmdm_free(blc_commands_memory mem)
{
  free(mem.mem);
}

