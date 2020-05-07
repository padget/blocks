#include "argument.h"
#include "log.h"
#include "i18n.h"
#include "algorithm.h"
#include "keyword.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// definition of the instance
// syscall that will be accessible
// everywher in source code by
// including argument.h
syscall sys;

// private const char *extract_arg_name(const char *arg);
// private const char *extract_arg_value(const char *arg);

sysarg make_sysarg(const char *arg, sysargrule rule)
{
	sysarg sarg;
	sarg.arg = arg;
	sarg.rule = rule;
	return sarg;
}

sysargrule make_sysargrule(
		bool mandatory,
		int position,
		const char *description)
{
	sysargrule srule;
	srule.mandatory = mandatory;
	srule.position = position;
	srule.description = description;
	return srule;
}

private
syscall make_syscall(sysarg *args, size_t len)
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
		sys = make_syscall(args, nbargs);
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