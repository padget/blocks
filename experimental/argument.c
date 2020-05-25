#include "argument.h"
#include "log.h"
#include "i18n.h"
#include "string.h"
#include "cstring.h"
#include "keyword.h"

#include <stdlib.h>
#include <stdio.h>

syscall sys;

private
void __check_nb_semicolon(
		char *rules,
		size_t nb_to_have)
{
	size_t nb = cstr_count(rules, ';');

	if (nb not_eq nb_to_have)
	{
		log_fatal("number of ';' must be equal to %d", nb_to_have);
		exit(EXIT_FAILURE);
	}
}

private
void __check_mandatory(char *mandatory)
{
	if (not cstr_equals(mandatory, "true") and
			not cstr_equals(mandatory, "false"))
	{
		log_fatal("mandatory rule must be equal to true or false");
		exit(EXIT_FAILURE);
	}
}

private
void __check_index(char *index)
{
	if (not cstr_contains_only(index, "0123456789"))
	{
		log_fatal("index must be a parsable positive integer");
		exit(EXIT_FAILURE);
	}
}

private
void __check_dependencies(char *dependencies)
{
	bool has_or = cstr_in(dependencies, '|');
	bool has_and = cstr_in(dependencies, '&');

	if (has_and and has_or)
	{
		log_fatal("dependencies must not contain | and & symbols at same time");
		exit(EXIT_FAILURE);
	}
}

sysarg make_sysarg(
		const char *arg,
		bool mandatory, 
		int index, 
		const char* dependencies)
{
	sysarg sarg;
	sarg.arg = arg;
	sarg.mandatory = mandatory;
	sarg.index = index;
	sarg.dependencies = dependencies;
	return sarg;
}

private
syscall __make_syscall(sysarg *args, size_t len)
{
	syscall scall;
	scall.args = args;
	scall.len = len;
	return scall;
}

bool define_sysargs(sysarg *args, size_t nbargs)
{
	static bool defined = false;

	if (not defined)
	{
		sys = __make_syscall(args, nbargs);
		defined = true;
	}
	else
		log_error(blocks_log_argument_already_defined);

	return defined;
}

bool check_args(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	return true;
}
