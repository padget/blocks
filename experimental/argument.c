#include "argument.h"
#include <string.h>

argument arg_default()
{
  argument arg;
  arg.name = vs_default();
  arg.value = vs_default();
  return arg;
}

argument arg_construct(vstring name, vstring value)
{
  argument arg;
  arg.name = name;
  arg.value = value;
  return arg;
}

argument arg_from_property(char* prop)
{
  size_t size = strlen(prop);
  char* begin = prop;
  char* end   = prop+size;
  size_t eqi  = 0;

  while (eqi < size)
  {
    if (prop[eqi] == '=')
      break;
    eqi++;
  }

  argument arg = arg_default();
  arg.name = vs_construct(prop, prop+eqi);

  if (eqi == size)
    arg.value = vs_default();
  else 
    arg.value = vs_construct(prop+eqi+1, prop+size);

  return arg;
}

bool arg_has_value(argument arg)
{
  return vs_size(arg.value);
}

arguments args_default()
{
  arguments args;
  args.barg = NULL;
  args.earg = NULL;
  return args;
}

arguments args_construct_from_size(size_t size)
{
  arguments args;
  args.barg = malloc(sizeof(argument)*size);

  if (args.barg == NULL)
    return args_default();

  args.earg = args.barg + size;

  argument* barg;
  argument* earg;
  argument def = arg_default();

  while (barg!=earg)
  {
    *barg = def;
    barg++;
  }

  return args;
}

size_t args_size(arguments args)
{
  return args.earg - args.barg;
}

arguments args_insert(arguments args, size_t index, argument arg)
{
  if (index < args_size(args))
    args.barg[index] = arg;

  return args;
}

arguments args_append(arguments args, argument arg)
{
  size_t size = args_size(args);

  argument* barg = args.barg;
  argument* targ = realloc(barg, size+1);

  if (targ == NULL)
    return args;

  targ[size] = arg;
  args.barg = targ;
  args.earg = targ+size+1;

  return args;
}

argument args_at(arguments args, vstring name)
{
  argument* begin = args.barg;
  argument* end   = args.earg;

  while (begin!=end)
  {
    if (vs_isequal(begin->name, name))
      return *begin;
    else
      begin++;
  }

  return arg_default();
}

void args_free_arguments(arguments args)
{
  free(args.barg);
}
