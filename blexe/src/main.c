#include <stdlib.h>
#include <stdio.h>



typedef unsigned long int unslint; 

typedef 
struct bytecode
{
  unslint size;
  unslint* data;
} 
bytecode ;

bytecode fread_bytecode(FILE* f)
{
  bytecode bc; 
  fscanf(f, "%lu", &bc.size);
  unslint size = bc.size * sizeof(unslint);
  bc.data = malloc(size);

  for (int i=0; i<bc.size; ++i)
    fscanf(f, "%lu", &bc.data[i]);
  
  return bc;
}

void free_bytecode(bytecode bc)
{
  free(bc.data);
}

typedef
struct command
{
  unslint id;
  unslint nargs;
  unslint* args;
}
command;

command bcread_command(bytecode bc, unslint offset)
{
  command cmd;
  cmd.id    = bc.data[offset];
  cmd.nargs = bc.data[offset+1];
  cmd.args  = malloc(cmd.nargs*sizeof(unslint));

  unslint min = offset+2;
  unslint max = offset+2+bc.size;

  for(int i=min, j=0; i<max; ++i, ++j)
    cmd.args[j] = bc.data[i];
  
  return cmd;
}

void free_command(command cmd) 
{
  free(cmd.args);
}

typedef
struct commands  
{
  unslint ncmds;
  command* cmds;
}
commands;

commands bcread_commands(bytecode bc, unslint offset)
{
  commands cmds;
  cmds.ncmds = bc.data[offset];
  cmds.cmds  = malloc(cmds.ncmds * sizeof(command));
 
  offset++;
  
  for (int i=0; i<cmds.ncmds; ++i)
  {
    cmds.cmds[i] = bcread_command(bc, offset);
    unslint n = cmds.cmds[i].nargs;
    offset += 1 + n;
  }
  
  return cmds;
}

void free_commands(commands cmds)
{
  for (int i=0; i<cmds.ncmds; ++i)
    free_command(cmds.cmds[i]);

  free(cmds.cmds);
}

int main(int argc, char** argv)
{
  const char* filename = "examples/add.blocks.blb";

  FILE* f = fopen(filename, "r");

  if (f) 
  {
    bytecode bc = fread_bytecode(f);
    commands cmds = bcread_commands(bc, 0);

    free_bytecode(bc);
    free_commands(cmds);
    fclose(f);
  }
}

