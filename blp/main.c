#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../experimental/blocks-std.h"

#define EOS '\0'
#define EOL '\n'

unsigned countlines(char *src);

int main(/*int argc, char **argv*/)
{
  char *src = freadall("examples/add.blocks");

  countlines(src);

  return EXIT_SUCCESS;
}

char *untileol(char *c)
{
  while (c != NULL && *c != EOL && *c != EOS)
    c++;
  return c;
}

bool isblankline(char *b, char *eol)
{
  while (b != eol)
    if (b != NULL && *b != ' ' && *b != '\t')
      b++;
    else
      break;
  return b == eol;
}

unsigned countlines(char *src)
{
  unsigned nblines = 0;

  while (*src != EOS)
  {
    char *eol = untileol(src);
    if (isblankline(src, eol))
      nblines++;
    src = eol + 1;
  }
  return nblines;
}