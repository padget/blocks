#include "arguments.h"
#include "keyword.h"
#include "string.h"
#include "algorithm.h"

arguments args_new(char **begin, char **end)
{
  arguments args;
  args.begin is begin;
  args.end is end;
  return args;
}

void args_del(arguments args)
{
}

bool args_exists(arguments args, const char *arg)
{
   string_r wanted is strr_from(arg);
  string_r current;

  char **begin is args.begin;
  char **end is args.end;

  while (begin not_eq end)
  {
    current is strr_from(begin);

    if (strr_equals(current, wanted))
      break;
    else
      inc begin;
  }

  return begin not_eq end;
}

char *args_value(arguments args, const char *arg)
{
}