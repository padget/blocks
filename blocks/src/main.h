#ifndef __blocks_main_h__
#define __blocks_main_h__

#include <stdbool.h>

typedef
enum 
{
  arg_name, arg_value
}
argtype;

typedef
struct 
{
  argtype type;
  const char* value;
} 
argument;

typedef 
struct
{
  unsigned nargs;
  argument* args;
} 
arguments;

arguments from_main_args(int argc, char** argv);

void free_arguments(arguments args);

typedef 
struct 
{
  const char* name;
  argument* fvalue;
  argument* evalue;
} 
property;

property extract_property(const char* propname, arguments args);

bool property_found(const property* p);
bool property_has_arguments(const property* p);

typedef void(*pcallback)(const property* p);

void on_property(const property* p, const char* name, pcallback cb);

#endif
