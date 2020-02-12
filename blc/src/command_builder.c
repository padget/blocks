#include "command_builder.h"
#include <stdlib.h>

#define EOS '\0'
#define EOL '\n'

void blc_cmds_init_cstr(int nb, blc_command* cmds);

blc_command* 
blc_cmds_init(size_t nb)
{
  size_t s_cmd  = sizeof(blc_command);
  size_t s_cmds = nb*s_cmd; 

  blc_command* cmds = malloc(s_cmds);
  blc_cmds_init_cstr(nb, cmds);

  return cmds;
}

char* blc_cmd_name(char* src);
char* blc_cmd_var(char* src);
char* blc_cmd_type(char* src);
char* blc_cmd_number(char* src);
char* blc_cmd_arg(char* src);

char* blc_bypass_blank(char* src);
char* blc_bypass_emptyline(char* src);
char* blc_bypass_emptylines(char* src);

char* blc_cmd_fill_name(blc_command* cmd, char* src);
char* blc_cmd_fill_args(blc_command* cmd, char* src);

char*
blc_cmds_fill_one(blc_command* cmd, char* src)
{
  src=blc_bypass_emptylines(src);
  src=blc_bypass_blank(src);
  src=blc_cmd_fill_name(cmd, src);
  src=blc_bypass_blank(src);
  src=blc_cmd_fill_args(cmd, src);
  src=blc_bypass_emptylines(src);
  return src;
}

void
blc_cmds_fill(size_t nb, blc_command* cmds, char* src)
{
  size_t i=0;

  while (i<nb)
  {
    src=blc_cmds_fill_one(&cmds[i], src);
    ++i;
  }
}

char*
blc_cmd_fill_name(blc_command* cmd, char* src)
{
  char* begin=src;
  char* end=blc_cmd_name(src);

  if (begin==end)
    return NULL;

  if (end-begin>CMD_NAME_MAX)
    return NULL;

  char* name=cmd->name;

  while (begin!=end)
  {
    *name=*begin;
    ++name;
    ++begin;
  }

  name='\0';

  return end;
}

void 
blc_extract_type(blc_argument* arg, char* begin, char* end)
{
  while (begin!=end)
    if (*begin!='#')
      begin++;
    else 
      break;

  if (begin!=end)
    begin++;

  size_t dist=end-begin;

  if (0<dist&&dist<ARG_TYPE_MAX)
  {
    char* type = arg->type;

    while (begin!=end)
    {
      *type=*begin;
      ++type;
      ++begin;
    }
  }
}

void 
blc_extract_value(blc_argument* arg, char* begin, char* end)
{
  char* value=arg->value;

  while (begin!=end)
  {
    if (*begin!='#')
    {
      *value=*begin;
      begin++;
      value++;
    } 
    else 
      break;
  }
}

char*
blc_cmd_fill_args(blc_command* cmd, char* src)
{
  blc_argument* arg = cmd->args;

  char* begin=src;
  char* end;

  while ((end=blc_cmd_arg(begin))==begin)
  {
    blc_extract_type(arg, begin, end);
    blc_extract_value(arg, begin, end);
    ++arg;
  }

  return end;
}


void 
blc_cmds_init_cstr(int nb, blc_command* cmds)
{
  int i=0;

  while (i<nb)
  {
    blc_command* cmd = &cmds[i];
    cmd->name[0]=EOS;

    int j=0;

    while (j<ARGS_MAX)
    {
      cmd->args[j].value[0]=EOS;
      cmd->args[j].type[0]=EOS;

      ++j;
    }

    ++i;
  }
}


char* blc_cmd_name(char* src)
{
  char* prev = src;

  while (*src!=EOS)
    if ('a'<=*src&&*src<='z')
      ++src;
    else 
      break;

  if (*src==':')
    return src;
  else 
    return prev; 
}

char* blc_bypass_blank(char* src)
{
  while (*src!=EOS)
    if (*src==' '||*src=='\t')
      ++src;
    else 
      break;

  return src;
}

char* blc_bypass_emptyline(char* src)
{
  src=blc_bypass_blank(src);

  if (*src=='\n')
    ++src;

  return src;
}

char* blc_bypass_emptylines(char* src)
{
  char* prev = src;
  char* tmp;

  while ((tmp=blc_bypass_emptyline(prev))!=prev)
    ;

  return tmp;
}


char* blc_cmd_var(char* src)
{
  while (*src!=EOS)
    if ('a'<=*src&&*src<='z')
      ++src;
    else 
      break;

  return src;
}

char* blc_cmd_type(char* src)
{
  char* prev=src;

  if (*src=='#')
    ++src;
  else 
    return prev;

  while (*src!=EOS)
    if ('a'<=*src&&*src<='z')
      ++src;
    else 
      break;

  if (src>prev+1)
    return src;
  else 

    return prev;
}

char* blc_cmd_number(char* src)
{
  while (*src!=EOS)
    if ('0'<=*src&&*src<='9')
      ++src;
    else 
      break;

  return src;
}

char* blc_cmd_arg(char* src)
{
  char* prev=src;

  src=blc_cmd_var(src);

  if (src!=prev)
  {
    char* prev2=src;
    src=blc_cmd_type(src);
    if (src!=prev2)
      return src;
  }

  src=blc_cmd_number(src);

  if (src!=prev)
    return src;

  return prev;
}
