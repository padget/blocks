#include "argument.h"

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

arguments args_append(arguments args, argument arg)
{
  size_t size = args_size(args);
