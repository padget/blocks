#include "argument.h"
#include "log.h"
#include "i18n.h"
#include "string.h"
#include "keyword.h"

#include <stdlib.h>
#include <stdio.h>

syscall sys;

private
void __check_nb_semicolon(
		char *rules,
		size_t nb_to_have)
{
	size_t nb = str_count(rules, ';');

	if (nb not_eq nb_to_have)
	{
		log_fatal("number of ';' must be equal to %d", nb_to_have);
		exit(EXIT_FAILURE);
	}
}

private
void __check_mandatory(char *mandatory)
{
	if (not str_equals(mandatory, "true") and
			not str_equals(mandatory, "false"))
	{
		log_fatal("mandatory rule must be equal to true or false");
		exit(EXIT_FAILURE);
	}
}

private
void __check_index(char *index)
{
	if (not str_contains_only(index, "0123456789"))
	{
		log_fatal("index must be a parsable positive integer");
		exit(EXIT_FAILURE);
	}
}

private
void __check_dependencies(char *dependencies)
{
	bool has_or = str_in(dependencies, '|');
	bool has_and = str_in(dependencies, '&');

	if (has_and and has_or)
	{
		log_fatal("dependencies must not contain | and & symbols at same time");
		exit(EXIT_FAILURE);
	}
}

sysarg make_sysarg(
		char *arg,
		char *rules)
{
	log_debug("1");
	__check_nb_semicolon(rules, 2);
	log_debug("2");
	sysarg sarg;
	sarg.arg = arg;
	char *cursor = rules;

	for (int i = 0; i < 3; ++i)
	{
		sarg.rules[i] = cursor;
		cursor = str_find(rules, ';') + 1;
	}
	log_debug("2bis");
	str_replace(rules, ';', '\0');
	log_debug("3");
	__check_mandatory(sarg.rules[0]);
	log_debug("4");
	__check_index(sarg.rules[1]);
	log_debug("5");
	__check_dependencies(sarg.rules[2]);

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
