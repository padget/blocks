#include "command_builder.h"
#include <stdlib.h>

void free_becommands(command* begin, command* end)
{
  while(begin != end)
  {
    free(begin);
    begin++;
  }
}

void free_commands(commands cmds)
{
  free_becommands(cmds.bcmd, cmds.ecmd);
}

const char* until_eol(const char* src)
{
  while (*src!='\n' || *src!='\0')
    src++;
  return src;
}

unsigned count_lines(const char* src)
{
  unsigned count=0;
  while (*src != '\0')
  {
    if (*src=='\n')
      count++;
    src++;
  }
  return count;
}
char* command_name(const char* begin, 
                   const char* end)
{

}

void build_command(const char* begin, 
                   const char* end, 
                   command* cmd)
{
  if (*begin!='\n' && *begin!='\0')
    return;

  char* name = command_name(begin, end);

  while (begin != end)
  {
     begin++;
  }
}

void build_commands(const char* src, commands* cmds)
{
  unsigned lines_count = count_lines(src);
  command* cmds_buffer = malloc(sizeof(command)*lines_count);

  if (cmds_buffer == NULL)
    return;
  command* bcmds = cmds_buffer;
  command* ecmds = cmds_buffer+lines_count;

  // Pour chaque ligne je cherche
  // a construire une commande.
  //
  while (bcmds != ecmds)
  {
    const char* bline = src; 
    const char* eline = until_eol(bline);

    command cmd;
    build_command(bline, eline, &command);
    
    bcmds++;
  }
}
