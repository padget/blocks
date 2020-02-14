#include "command_builder.h"
#include <stdlib.h>
#include <stdio.h>

#define EOS '\0'
#define EOL '\n'

void blc_cmds_init_cstr(int nb, blc_command* cmds) 
{
  int i=0; 
  while(i<nb)
  {
    cmds[i].name[0]=EOS;

    int j=0; 
    while(j<ARGS_MAX)
    {
      cmds[i].args[j].type[0]=EOS;
      cmds[i].args[j].value[0]=EOS;
      ++j;
    }

    i++;
  }
}

blc_command* 
blc_cmds_init(size_t nb)
{
  size_t s_cmd  = sizeof(blc_command);
  size_t s_cmds = nb*s_cmd; 

  blc_command* cmds = malloc(s_cmds);
  blc_cmds_init_cstr(nb, cmds);

  return cmds;
}

char* overblank(char* c)
{
  while (c!=NULL&&(*c==' '||*c=='\t'))
    c++;
  return c;
}

char* overcmdname(char* c)
{
  while (c!=NULL&&'a'<=*c&&*c<='z')
    c++;
  if (c!=NULL&&*c==':')
    c++;
  return c;
}

char* overargnumber(char* c)
{
  while (c!=NULL&&'0'<=*c&&*c<='9')
    c++;
  return c;
}

char* untileol(char* c)
{
  while (c!=NULL&&*c!=EOS&&*c!=EOL)
    c++;
  return c;
}

void copy(char*b, char*e, char* buf)
{
  while (b!=e)
  {
    *buf=*b;
    ++buf; 
    ++b;
  }

  *buf='\0';
}

bool checkcmdname(char* b, char* e)
{ 
  int s=e-b;
  return 
    0<s&&s<CMD_NAME_MAX&&
    'a'<=*b&&*b<='z'&&
    *(e-1)==':';
}

bool checkargnumber(char* b, char* e)
{
  int s=e-b;
  return 0<s&&s<ARG_VALUE_MAX;
}

void blc_cmds_fill(size_t nb, blc_command* cmds, char* src)
{
  size_t i=0;

  while (*src!=EOS&&i<nb)
  {
    char* bol=src;
    char* eol=untileol(bol); 

    bol=overblank(bol);

    char* bname=bol;
    char* ename=bol;

    ename=overcmdname(ename);

    if (checkcmdname(bname, ename))
      copy(bname, ename, cmds[i].name);
    else 
      // TODO error
      return;
    
    bol=ename;
    bol=overblank(bol);

    size_t j=0;
    char* bargs=bol;
    char* eargs=eol;

    while (bargs!=eargs&&j<ARGS_MAX)
    {
      char* bnb=bargs;
      char* enb=bargs;

      enb=overargnumber(enb);

      if (checkargnumber(bnb, enb))
        copy(bnb, enb, cmds[i].args[j].value); 
      else 
        // TODO erreur
        return;

      enb=overblank(enb);  

      ++j;
      bargs=enb;
    }

    if (j==ARGS_MAX&&bargs!=eargs)
      // TODO ERROR  
      return;

    ++i;

    if (*eol==EOS)
      src=eol;
    else 
      src=eol+1;
  }

  if (i==nb&&*src!=EOS)
    // TODO ERROR
    return;
}
