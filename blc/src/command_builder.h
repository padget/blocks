#ifndef __blocks_command_builder_h__
#define __blocks_command_builder_h__

#include <stdbool.h>
#include <stdlib.h>

typedef struct vstring
{
  const char* bstr;
  const char* estr;
} vstring;

bool vs_is_empty(vstring* vs);

typedef struct argument
{
  vstring type;
  vstring value;
} argument;

typedef struct arguments
{
  argument* barg;
  argument* earg;
} arguments;

typedef struct command
{
  vstring name;
  arguments args;
} command;

typedef struct commands
{
  command* bcmd;
  command* ecmd;
} commands;

void free_commands(commands cmds);

typedef struct building_error
{
	command* cmd;
	char* error;
	size_t column;
} building_error;

typedef struct building_errors
{
	building_error berr;
	building_error eerr;
} building_errors;

typedef struct building_report 
{
	commands cmds;
	building_errors errs  ;
} building_report;

building_report build_commands(const char* src);

void free_building_errors(building_errors errors);
void free_building_report(building_report report);
