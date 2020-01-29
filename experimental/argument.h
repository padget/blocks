#ifndef __blocks_argument_h__
# define __blocks_argument_h__

# include "vstring.h"
# include <stdbool.h>

typedef struct argument
{
  vstring name;
  vstring value;
} argument;

argument arg_default();
argument arg_construct(vstring name, vstring value);
bool     arg_has_value(argument arg);

typedef struct arguments
{
  argument* barg;
  argument* earg;
} arguments;

arguments args_default();
arguments args_construct_from_size(size_t size);
arguments args_append(arguments args, argument arg);
void args_free_arguments(arguments args);

#endif
