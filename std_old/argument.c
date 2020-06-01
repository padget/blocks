#include "argument.h"
#include "log.h"
#include "i18n.h"
#include "string.h"
#include "keyword.h"

#include <stdlib.h>
#include <stdio.h>

syscall sys;

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

	for (int i=0; i<argc; i++)
	{

	}
	
	return true;
}
