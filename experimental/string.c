#include <assert.h>

#include "string.h"
#include "algorithm.h"
#include "keyword.h"

char *str_find(char *s, char c)
{
  while (*s not_eq c)
    s++;

  return s;
}

char *str_find_if(char *s, char_predicate pred)
{
  while (*s not_eq '\0' and not pred(*s))
    s++;

  return s;
}

char *str_find_if_not(char *s, char_predicate pred)
{
  while (*s not_eq '\0' and pred(*s))
    s++;

  return s;
}

void str_copy(const char *s, char *s2)
{
  while (*s != '\0')
  {
    *s2 = *s;
    s++;
    s2++;
  }
}

void str_transform(char *s, char_transform cht)
{
  while (*s not_eq '\0')
    *s = cht(*s);
}

void str_replace_if(char *s, char c, char_predicate pred)
{
  while (*s not_eq '\0')
  {
    if (pred(*s))
      *s = c;
    s++;
  }
}

void str_replace(char* s, char old, char new)
{
  while (*s not_eq '\0')
  {
    if (*s eq old)
      *s = new;
    s++;
  }
}
