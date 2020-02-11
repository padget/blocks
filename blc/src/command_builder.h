#ifndef __blocks_command_builder_h__
#define __blocks_command_builder_h__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
  char* type;
  char* value;
} 
argument;

typedef struct
{
  argument* args;
  size_t nbargs;
}
arguments;

typedef struct
{
  char* name;
  arguments args;
} 
command;

typedef struct
{
  command* cmds;
  size_t size;
} 
commands;

commands build_commands(char* source);
void free_commands(command* cmds);
