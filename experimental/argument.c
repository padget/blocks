#include "argument.h"
#include "log.h"
#include "i18n.h"
#include "algorithm.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


// definition of the instance
// syscall that will be accessible
// everywher in source code by 
// including argument.h
syscall sys;

static const char* extract_arg_name(const char* arg);
static const char* extract_arg_value(const char* arg);

void register_args(int argc, char** argv)
{
  static bool registered = false;
  
  if (!registered)
    {
      sys.args = malloc(argc*sizeof(sysarg));
      
      if(sys.args == NULL)
	{
	  log_fatal("problème d'allocation de la mémoire");
	  return registered;
	}
      
      for (int i=0; i<argc; ++i)
	sys.args[i] = (sysarg){.arg = argv[i]};

      
    }
  
  registered = true;
}

void* next(void* cursor)
{
	return ((char**)cursor)+1;
}

bool equals(
		const void* l,
	       	const void* r)
{
	return strcmp(
		(*(const char**)l), 
		(const char*)r) == 0;
}

bool args_exists(const char* name)
{
	char** begin = sys.argv;
	char** end   = begin + sys.argc;
	alctxt_t ctxt;
	ctxt.next = next;
	ctxt.equals = equals;

	return find(begin, end, name, ctxt) != end;
}

char** args_value(const char* name)
{
	char** begin = sys.argv;
	char** end   = begin + sys.argc;
	
	alctxt_t ctxt;
	
	ctxt.next = next;
	ctxt.equals = equals;
	
	char** arg = find(begin, end, name, ctxt);
	char** value = next(arg);
	
	if  (value != end)
		return value;
	else 
		return NULL;
}


