#ifndef __blocks_command_builder_h__
#define __blocks_command_builder_h__

typedef struct argument
{
  char* type;
  char* value;
} argument;

typedef struct command
{
  char* name;
  argument* bargs;
  argument* eargs;
} command;

typedef struct commands
{
  command* bcmd;
  command* ecmd;
} commands;

void build_commands(const char* src, commands* cmds);
void free_commands(commands cmds);
void free_becommands(command* begin, command* end);

#endif
