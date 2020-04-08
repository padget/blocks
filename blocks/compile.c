#include "compile.h"
#include <stdbool.h>
#include <stdlib.h>

#include "../experimental/blocks-std.h"
#include "../experimental/argument.h"
#include "../experimental/log.h"

#define EOS '\0'
#define EOL '\n'

inline bool cnoteos(char *c)
{
  return c != NULL && *c != EOS;
}

inline bool cnoteol(char *c)
{
  return c != NULL && *c != EOL;
}

inline bool cisblank(char *c)
{
  return c != NULL && (*c == ' ' || *c == '\t');
}

inline bool cisdigit(char *c)
{
  return c != NULL && '0' <= *c && *c <= '9';
}

inline bool cislower(char *c)
{
  return c != NULL && 'a' <= *c && *c <= 'z';
}

void blc_cmds_init_cstr(int nb, bl_command *cmds)
{
  int i = 0;

  while (i < nb)
  {
    cmds[i].name[0] = EOS;

    int j = 0;
    while (j < BLOCKS_ARGS_MAXSIZE)
    {
      cmds[i].args[j].type[0] = EOS;
      cmds[i].args[j].value[0] = EOS;
      ++j;
    }

    i++;
  }
}

bl_command *
blc_cmds_init(size_t nb)
{
  size_t s_cmd = sizeof(bl_command);
  size_t s_cmds = nb * s_cmd;

  bl_command *cmds = malloc(s_cmds);
  blc_cmds_init_cstr(nb, cmds);

  return cmds;
}

char *overblank(char *c)
{
  while (cisblank(c))
    c++;
  return c;
}

char *overcmdname(char *c)
{
  while (cislower(c))
    c++;
  if (c != NULL && *c == ':')
    c++;
  return c;
}

char *overargnumber(char *c)
{
  while (cisdigit(c))
    c++;
  return c;
}

char *overargname(char *c)
{
  while (cislower(c))
    c++;
  return c;
}

char *overarg$$(char *c)
{
  if (cnoteol(c) && cnoteos(c))
    if (cnoteol(c + 1) && cnoteos(c + 1))
      if (*c == '$' && *(c + 1) == '$')
        return c + 2;
  return c;
}

char *untileol(char *c)
{
  while (cnoteos(c) && cnoteol(c))
    c++;
  return c;
}

bool isblankline(char *b, char *e)
{
  while (b != e)
  {
    if (cisblank(b))
      b++;
    else
      break;
  }

  return b == e;
}

char *overblanklines(char *c)
{
  char *b = c;
  char *e = c;

  while (isblankline(b, e = untileol(b)))
  {
    b = e + 1;
    printf("je saute une ligne vide\n");
  }
  return b;
}

void copy(char *b, char *e, char *buf)
{
  while (b != e)
  {
    *buf = *b;
    ++buf;
    ++b;
  }

  *buf = '\0';
}

bool checkcmdname(char *b, char *e)
{
  int s = e - b;
  bool not_empty = 0 < s && s < BLOCKS_CMD_NAME_MAXSIZE;
  bool start_letter = not_empty && cislower(b);
  bool end_colon = not_empty && *(e - 1) == ':';
  return start_letter && end_colon;
}

bool checkargnumber(char *b, char *e)
{
  int s = e - b;
  bool not_empty = 0 < s && s < BLOCKS_ARG_VALUE_MAXSIZE;
  bool start_digit = not_empty && cisdigit(b);
  bool end_digit = not_empty && cisdigit(e - 1);
  return start_digit && end_digit;
}

bool checkargname(char *b, char *e)
{
  int s = e - b;
  bool not_empty = 0 < s && s < BLOCKS_ARG_VALUE_MAXSIZE;
  bool start_lower = not_empty && cislower(b);
  bool end_lower = not_empty && cislower(e - 1);
  return start_lower && end_lower;
}

bool checkarg$$(char *b, char *e)
{
  int s = e - b;
  bool length_two = s == 2;
  bool start_$ = length_two && *b == '$';
  bool end_$ = length_two && *b == '$';
  return start_$ && end_$;
}

void cmds_fill(size_t nb, bl_command *cmds, char *src)
{
  size_t i = 0;

  // Commandes
  while (cnoteos(src) && i < nb)
  {
    char *bol = overblanklines(src);
    char *eol = untileol(bol);

    bol = overblank(bol);

    char *bname = bol;
    char *ename = bol;

    ename = overcmdname(ename);

    if (checkcmdname(bname, ename))
      copy(bname, ename, cmds[i].name);
    else
      // TODO error
      return;

    bol = ename;
    bol = overblank(bol);

    size_t j = 0;
    char *bargs = bol;
    char *eargs = eol;

    // Arguments
    while (bargs != eargs && j < BLOCKS_ARGS_MAXSIZE)
    {
      char *bnb = bargs;
      char *enb = overargnumber(bargs);

      if (checkargnumber(bnb, enb))
        copy(bnb, enb, cmds[i].args[j].value);
      else
      {
        enb = overargname(bargs);

        if (checkargname(bnb, enb))
          copy(bnb, enb, cmds[i].args[j].value);
        else
        {
          enb = overarg$$(bargs);

          if (checkarg$$(bnb, enb))
            copy(bnb, enb, cmds[i].args[j].value);
          else
            // TODO erreur
            return;
        }
      }

      enb = overblank(enb);

      ++j;
      bargs = enb;
    }

    if (j == BLOCKS_ARGS_MAXSIZE && bargs != eargs)
      // TODO ERROR
      return;

    ++i;

    if (*eol == EOS)
      src = eol;
    else
      src = eol + 1;
  }

  if (i == nb && cnoteos(src))
    // TODO ERROR
    return;
}

void bl_compile()
{
  char *src = NULL;
  size_t nb = 0;
  bl_command *cmds = NULL;
  char *fname = NULL;

  if (args_has_value("--file"))
    fname = args_value("--file");
  else if (args_exists("--file"))
    log_error("--file must have a value");
  else
    log_error("--file is mandatory");

  src = freadall(fname);

  if (src == NULL || strlen(src) == 0)
  {
    log_warn("the content is NULL or empty");
    goto free_mem;
  }

  nb = strcount(src, '\n');

  if (nb == 0)
  {
    log_warn("no command to read in the content");
    goto free_mem;
  }

  cmds_fill(nb, cmds, src);
free_mem:
  free(src);
  free(cmds);
}