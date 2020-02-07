#include "command_builder.h"
#include <stdlib.h>

bool vs_is_empty(vstring* vs) 
{
	return vs != NULL && 
		vs->bstr != NULL && 
		vs->estr != NULL &&
		vs->bstr != vs->estr;
}

void free_commands(commands cmds)
{
	command* cmd = cmds.bcmd;
	command* end = cmds.ecmd;

	while (cmd != end)
	{
		free(cmd);
		cmd++;
	}
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

vstring command_name(const char* begin, 
		const char* end)
{
	vstring name;
	name.bstr = begin;

	while (begin != end)
	{ 
		char c = *begin;

		if ('a' <= c && c <= 'z')
			begin++;
		else 
			break;
	}

	name.estr = begin;
	return name;
}

vstring argument_name(
		const char* begin, 
		const char* end)
{
	vstring name;
	name->bstr = begin;

	while (begin != end)
	{
		char c = *begin;

		if ('a'<=c&&c<='z')
			begin++;
		else 
			break;
	}

	name->estring = begin;

	return name;
}

vstring argument_type(
		const char* begin, 
		const char* end)
{
	vstring type;
	type->bstr = begin;

	if (*begin!='#')
	{
		type->estr = begin;
		return type;
	}

	begin++;
	
	while (begin != end)
	{
		char c = *begin;

		if ('a'<=c&&c<='z')
			begin++;
		else 
			break;
	}

	type->estr = begin;

	return type;
}

argument command_arg(
		const char* begin, 
		const char* end)
{
	argument arg;

	vstring value = argument_value(begin, end);

	if (!vs_is_empty(&value))
	{
		begin = value.estr;
		vstring type  = argument_type(begin, end);
		arg.value = value;
		arg.type = type;
	}

	return arg;
}

arguments command_args(
		const char* begin, 
		const char* end)
{
	// TODO : Faire du realloc pour augmenter la taille du 
	// tableau d'argument !
	arguments args;

	if (*begin=='\n' || *begin=='\0')
		return args;

	while (begin != end)
	{
		argument arg = command_arg(begin, end);
		begin = arg.type.estr;
	}

	return args;
}

command build_command(
		const char* begin, 
		const char* end)
{
	command cmd; 
	if (*begin=='\n' || *begin=='\0')
		return cmd;

	cmd->name = command_name(begin, end);

	if (vs_is_empty(cmd.name))
		return cmd;
	else 
		begin = cmd.name.estr;

	argument* args = NULL;
	cmd->args = command_args(begin, end, &args); 
}


bool is_in_error(building_error err)
{
	return err.cmd != NULL;
}

building_errors check_commands(commands cmds)
{
	building_errors errors;
	command* bcmd = cmds.bcmd;
	command* ecmd = cmds.ecmd;

	while (bcmd!=ecmd)
	{
		building_error err = check_command(*bcmd);
		
		if (is_in_error(err))
		{
			// Alors il y a une erreur sur la command courante !
		}
		
		bcmd++;
	}

	return errors;
}


building_report build_commands(const char* src)
{
	commands cmds;
	unsigned lines_count = count_lines(src);
	command* cmds_buffer = malloc(sizeof(command)*lines_count);
	command* bcmds = cmds_buffer;
	command* ecmds = cmds_buffer+lines_count;

	while (bcmds != ecmds)
	{
		const char* bline = src; 
		const char* eline = until_eol(bline);

		command cmd;
		build_command(bline, eline, &command);

		bcmds++;
	}

	building_errors errors = check_commands(cmds);
	building_report report;
	report.cmds   = cmds;
	report.errors = errors;

	return report;
}

void free_building_errors(building_errors errors)
{
	building_error* berr = errors->berr;
	building_error* eerr = errors->eerr;
	
	while (berr!=eerr)
	{
		free(berr);
		berr++;
	}
}

void free_building_report(building_report report)
{
	free_commands       (report.cmds);
	free_building_errors(report.errors);
}

