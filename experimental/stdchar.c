#include "stdchar.h"
#include "keyword.h"

#include <assert.h>
#include <stdlib.h>

bool char_in(const char c, const char* chars)
{
  assert(chars not_eq NULL);

  char c2;

  while (*chars not_eq '\0' and *chars not_eq c)
    inc chars;

  return *chars not_eq '\0';
}

bool char_inb(const char c, const char bounds[2])
{
  assert(bounds[0] <= bounds[1]);

  return bounds[0] <= c and c <= bounds[1];
}

bool char_is(const char c, const char c2)
{
  return c == c2;
}