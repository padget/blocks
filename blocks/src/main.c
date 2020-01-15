#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

#ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS 0
#endif

typedef
enum 
{
  name, value
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

int main(int argc, char** argv)
{
  arguments args = from_main_args(argc, argv);

  for (int i=0; i<args.nargs; ++i)
    printf("-- %d -> %s\n", args.args[i].type, args.args[i].value);

  free_arguments(args);
  return EXIT_SUCCESS;
}


#include <stdbool.h>
#include <string.h>

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

  for (int i=0; i<args.nargs; ++i)
    args.args[i].value = NULL;

  for (int i=0; i<args.nargs; ++i)
  {
    bool is_name = start_with_dashdash(argv[i+1]);
    
    if (is_name)
      args.args[i].type = name;
    else 
      args.args[i].type = value;
    
    args.args[i].value = argv[i+1];
  }

  return args;
}

void free_arguments(arguments args)
{
  free(args.args);
}
