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

private
sysarg init(const char *arg)
{
	return (sysarg){.arg = arg};
}

private
array args_proxy(sysarg *args, size_t len)
{
	return build_array(args, len, sizeof(sysarg));
}

bool register_args(int argc, char **argv)
{
	static bool registered = false;

	if (not registered)
	{
		sysarg *mem = malloc(argc * sizeof(sysarg));

		if (mem eq NULL)
		{
			log_fatal("problème d'allocation de la mémoire");
			return registered;
		}

		array pargv = strarr_proxy(argv, argc);
		iterator b = begin(pargv);
		iterator e = end(pargv);

		array pargs = args_proxy(mem, argc);
		iterator bmem = begin(pargs);
		iterator emem = end(pargs);

		sysarg* ptr = NULL;

		while (b not_eq e)
		{
			ptr = bmem;
			ptr->arg = *(char**)b;
			++bmem;
			++b;
		}
		
		sys.args = mem;
		sys.len = argc;

		registered = true;
		return registered;
	}

	return registered;
}

bool register_arg_rule(const char *name, sysargrule rule)
{


	return false;
}

bool clear_args()
{
	if (sys.len not_eq 0)
	{
		free(sys.args);
		sys.args = NULL;
		sys.len = 0;
		return true;
	}

	return false;
}

static bool localequals(
		const void *l,
		const void *r)
{
	const char *lc = (*(const sysarg *)l).arg;
	const char *rc = (const char *)r;

	return strcmp(lc, rc) eq 0;
}

bool args_exists(const char *name)
{
	array proxy = args_proxy(sys.args, sys.len);

	alctxt_t ctxt;
	ctxt.equals = localequals;

	return find(begin(proxy), end(proxy), name, ctxt) not_eq end;
}

sysarg *args_value(const char *name)
{
	sysarg *begin = sys.args;
	sysarg *end = begin + sys.len;

	alctxt_t ctxt;
	ctxt.equals = localequals;

	sysarg *arg = find(begin, end, name, ctxt);

	if (arg not_eq end)
		return arg;
	else
		return NULL;
}
