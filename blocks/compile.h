#ifndef __blocks_compile_h__
#define __blocks_compile_h__

#include "../experimental/config.h"
#include "../experimental/blocks-std.h"

typedef int error_code;

struct bl_type_attribute
{
  char* name;
  char* type;
};

typedef struct bl_type_attribute bl_type_attribute;


struct bl_type
{
  chararray name;
  bl_type_attributearray attributes;
};

struct bl_argument
{
  chararray type;
  chararray value;
};

typedef struct bl_argument bl_argument;

typeref(bl_argument)
typearray(bl_argument)

struct bl_command
{
  chararray name;
  bl_argumentarray args;
  error_code errcode;
};

typedef struct bl_command bl_command;

void bl_compile();

#endif