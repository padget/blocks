
#ifndef __blocks_command_builder_h__
#define __blocks_command_builder_h__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#define CMD_NAME_MAX 50
#define ARG_VALUE_MAX 50
#define ARG_TYPE_MAX 50
#define ARGS_MAX 10
#define SIZEOF_COMMAND(nb) sizeof(blc_command)*(nb)
#define CMDS_MAX 10000


typedef struct 
{
  char type[ARG_TYPE_MAX];
  char value[ARG_VALUE_MAX];
} 
blc_argument;

typedef struct
{
  char name[CMD_NAME_MAX];
  blc_argument args[ARGS_MAX];
} 
blc_command;

typedef struct 
{
  blc_command* mem;
  size_t size;
}
blc_commands;

/**
 * Initialize a commands_memory with
 * size octet in memory.
 *
 * @param size nb octet of the memory
 * @return the initialized memory
 */
blc_commands
cmdm_init(size_t nbcmds);

/**
 * Get the command at the index i in the
 * commands_memory cmdm.
 * 
 * @param cmdm commands_memory to search
 * @param i index of the command
 * @return a pointer to command present (or NULL)
 * at the index i in cmdm.
 */
blc_command* 
cmdm_command_at(blc_commands* cmdm,
                size_t i);
                
void cmdm_fill(blc_commands* cmdm, 
               string* source);
 
void 
cmdm_free(blc_commands cmdm);
                
#endif
