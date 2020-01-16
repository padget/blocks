#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"

#ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS 0
#endif


void on_compile(const property* p);
void on_execute(const property* p);


int main(int argc, char** argv)
{
  arguments args = from_main_args(argc, argv);
  property c = extract_property("--compile", args);
  property e = extract_property("--execute", args);

  on_property(&c, "--compile", &on_compile);
  on_property(&e, "--execute", &on_execute);

  free_arguments(args);
  return EXIT_SUCCESS;
}


void on_compile(const property* p)
{
	char cmd[1024] = "blocks-compile.exe";
	const char* vcmd = cmd;
	argument* begin = p->fvalue;
	argument* end   = p->evalue;
	
	while (begin!=end)
	{
		sprintf(cmd, "%s %s", vcmd, begin->value);
		begin++;
	}

	system(cmd);
}

void on_execute(const property* p)
{
	char cmd[1024] = "blocks-execute.exe";
	const char* vcmd = cmd;
	argument* begin = p->fvalue;
	argument* end   = p->evalue;
	
	while (begin!=end)
	{
		sprintf(cmd, "%s %s", vcmd, begin->value);
		begin++;
	}

	system(cmd);
}

void on_property(const property* p, const char* name, pcallback cb)
{
	bool found = property_found(p);
	bool same  = found && strcmp(name, p->name) == 0;
	
	if (same)
		cb(p);
}

bool property_found(const property* p)
{
	return p->name != NULL;
}

bool property_has_arguments(const property* p)
{
	return p->fvalue != p->evalue;
}


bool start_with_dashdash(const char* str)
{
  return 
    strlen(str) >= 2 && 
    str[0] == str[1] && 
    str[0] == '-';
}


arguments from_main_args(int argc, char** argv)
{
  arguments args;

  args.nargs = argc-1;
  args.args  = malloc(sizeof(argument)*args.nargs);

  for (unsigned i=0; i<args.nargs; ++i)
    args.args[i].value = NULL;

  for (unsigned i=0; i<args.nargs; ++i)
  {
    bool is_name = start_with_dashdash(argv[i+1]);

    if (is_name)
      args.args[i].type = arg_name;
    else 
      args.args[i].type = arg_value;

    args.args[i].value = argv[i+1];
  }

  return args;
}


void free_arguments(arguments args)
{
  free(args.args);
}


property extract_property(const char* propname, arguments args)
{
  property prop = {NULL, NULL, NULL};

  bool found = false;  
  
  argument* current = args.args;
  argument* end     = current + args.nargs;

  while (current != end && !found) 
  {
    if (current->type == arg_name && 
        strcmp(current->value, propname)==0)
      found = true;
    else
      current++;
  }

  if (!found)
    return prop;

  prop.name = current->value;
  current++;
  prop.fvalue = current;
  
  while (current != end && current->type == arg_value)
    current++;

  prop.evalue = current;

  printf("prop.name %s\n", prop.name);

  return prop;
}
