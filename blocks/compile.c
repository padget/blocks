#include "compile.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../experimental/argument.h"
#include "../experimental/log.h"
#include "../experimental/i18n.h"

#define EOS '\0'
#define EOL '\n'

bool cisnoteos(const char c)
{
  return c != EOS;
}

bool cisnoteol(const char c)
{
  return c != EOL;
}

bool cisblank(const char c)
{
  return c == ' ' || c == '\t';
}

bool cisdigit(const char c)
{
  return '0' <= c && c <= '9';
}

bool cislower(const char c)
{
  return 'a' <= c && c <= 'z';
}

bl_command *
bl_cmds_init(size_t nb)
{
  size_t s_cmd = sizeof(bl_command);
  size_t s_cmds = nb * s_cmd;

  bl_command *cmds = malloc(s_cmds);

  return cmds;
}

char *overblank(char *c)
{
  while (cisblank(*c))
    c++;
  return c;
}

char *overcmdname(char *c)
{
  while (cislower(*c))
    c++;
  if (c != NULL && *c == ':')
    c++;
  return c;
}

char *overargnumber(char *c)
{
  while (cisdigit(*c))
    c++;
  return c;
}

char *overargname(char *c)
{
  while (cislower(*c))
    c++;
  return c;
}

char *overarg$$(char *c)
{
  if (cisnoteol(*c) && cisnoteos(*c))
    if (cisnoteol(*(c + 1)) && cisnoteos(*(c + 1)))
      if (*c == '$' && *(c + 1) == '$')
        return c + 2;
  return c;
}

char *untileol(char *c)
{
  while (cisnoteos(*c) && cisnoteol(*c))
    c++;
  return c;
}

bool isblankline(const char *b, const char *e)
{
  while (b != e)
  {
    if (cisblank(*b))
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
    b = e + 1;

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
  bool start_letter = not_empty && cislower(*b);
  bool end_colon = not_empty && *(e - 1) == ':';
  return start_letter && end_colon;
}

bool checkargnumber(char *b, char *e)
{
  int s = e - b;
  bool not_empty = 0 < s && s < BLOCKS_ARG_VALUE_MAXSIZE;
  bool start_digit = not_empty && cisdigit(*b);
  bool end_digit = not_empty && cisdigit(*(e - 1));
  return start_digit && end_digit;
}

bool checkargname(char *b, char *e)
{
  int s = e - b;
  bool not_empty = 0 < s && s < BLOCKS_ARG_VALUE_MAXSIZE;
  bool start_lower = not_empty && cislower(*b);
  bool end_lower = not_empty && cislower(*(e - 1));
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

void cmds_fill(bl_command *cmds, size_t nb, char *src)
{
  size_t i = 0;
  // Commandes
  while (cisnoteos(*src) && i < nb)
  {
    char *bol = overblanklines(src);
    char *eol = untileol(bol);

    bol = overblank(bol);

    char *bname = bol;
    char *ename = bol;

    ename = overcmdname(ename);

    if (checkcmdname(bname, ename))
    {
      size_t len = ename - bname;
      char *data = bname;
      cmds[i].name.data = data;
      cmds[i].name.len = len;
    }
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
      {
        size_t len = enb - bnb;
        char *data = bnb;
        cmds[i].args[j].value.data = data;
        cmds[i].args[j].value.len = len;
      }
      else
      {
        enb = overargname(bargs);

        if (checkargname(bnb, enb))
        {
          size_t len = enb - bnb;
          char *data = bnb;
          cmds[i].args[j].value.data = data;
          cmds[i].args[j].value.len = len;
        }
        else
        {
          enb = overarg$$(bargs);

          if (checkarg$$(bnb, enb))
          {
            size_t len = enb - bnb;
            char *data = bnb;
            cmds[i].args[j].value.data = data;
            cmds[i].args[j].value.len = len;
          }
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

  if (i == nb && cisnoteos(*src))
    // TODO ERROR
    return;
}

void on_cmds_filled(bl_command *cmds, size_t nb)
{
  size_t i = 0;
  while (i < nb)
  {
    log_debug("cmd %s", cmds[i].name);
    int j = 0;
    while (j < BLOCKS_ARGS_MAXSIZE)
    {
      if (!strvempty(&cmds[i].args[j].value))
        log_debug("-- arg %s:%s", cmds[i].args[j].value, cmds[i].args[j].type);
      j++;
    }
    i++;
  }
}

// pour une commande, il faut :
// - un int pour identifier la commande
// - un int pour indiquer le nombre d'arguments
// - un int pour chaque argument pour enoncer sa valeur et un int pour son type

size_t size_of_args_int(bl_argument *args)
{
  size_t nb_total = 0;
  for (size_t arg_i = 0; arg_i < BLOCKS_ARGS_MAXSIZE; arg_i++)
    if (strvempty(&args[arg_i].value))
      break;
    else
      nb_total += 1;
  return nb_total;
}

size_t size_of_command_int(bl_command *cmd)
{
  size_t nb_total = 0;
  nb_total += 1;
  nb_total += size_of_args_int(cmd->args);
  return nb_total;
}

size_t size_of_commands_int(bl_command *cmds, size_t nb)
{
  size_t nb_total = 0;
  for (size_t cmd_i = 0; cmd_i < nb; cmd_i++)
    nb_total += size_of_command_int(cmds + cmd_i);
  return nb_total;
}

size_t nb_not_blank_lines(const char *src)
{
  size_t nb = 0;
  const char *c = src;
  while (cisnoteos(*src))
  {
    while (cisnoteol(*src))
      src += 1;

    if (!isblankline(c, src))
      nb += 1;

    c = src += 1;
  }

  return nb;
}

void id_of_cmd(bl_command *cmd)
{
  (void)cmd->args;
}

int fill_bytecodes_for_cmd(int *bytecodes, bl_command *cmd)
{
  size_t id = 0;
  id_of_cmd(cmd);
  *bytecodes = id;
  return 1;
}

void fill_bytecodes(
  int *bytecodes, 
  size_t bcnb, 
  bl_command *cmds, 
  size_t nb)
{
  *bytecodes = bcnb;
  bytecodes += 1;

  for (size_t i = 0; i < nb; i++)
    bytecodes += fill_bytecodes_for_cmd(bytecodes, cmds + i);
}

void bl_compile()
{
  char *src = NULL;
  size_t nb = 0;
  bl_command *cmds = NULL;
  char *fname = NULL;

  if (args_has_value("--file"))
    fname = args_value("--file");
  else
  {
    if (args_exists("--file"))
      log_error(blocks_log_argument_file_no_value);
    else
      log_error(blocks_log_argument_file_mandatory);
    goto free_mem;
  }

  src = freadall(fname);

  if (src == NULL || strlen(src) == 0)
  {
    log_warn(blocks_log_no_content_in_file, fname);
    goto free_mem;
  }

  nb = nb_not_blank_lines(src);

  if (nb == 0)
  {
    log_warn(blocks_log_no_command);
    goto free_mem;
  }

  cmds = bl_cmds_init(nb);
  cmds_fill(cmds, nb, src);

  size_t nbbytes = size_of_commands_int(cmds, nb);
  nbbytes += 1;
  int *bytecodes = calloc(nbbytes, sizeof(int));

  if (bytecodes == NULL)
  {
    log_error(blocks_log_memory_allocation);
    goto free_mem;
  }

  on_cmds_filled(cmds, nb);

  //fill_bytecodes(bytecodes, cmds);

free_mem:
  free(bytecodes);
  free(src);
  free(cmds);
}