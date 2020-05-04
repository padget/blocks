#include <assert.h>

#include "string.h"
#include "algorithm.h"
#include "keyword.h"

char_predicate make_char_predicate(bool (*apply)(const char))
{
  char_predicate pred;
  pred.apply = apply;
  return pred;
}

const char *str_find(const char *s, const char c)
{
  while (*s not_eq c)
    s++;

  return s;
}

const char *str_find_if(const char *s, char_predicate pred)
{
  while (*s not_eq '\0' and not pred.apply(*s))
    s++;

  return s;
}

const char *str_find_if_not(const char *s, char_predicate pred)
{
  while (*s not_eq '\0' and pred.apply(*s))
    s++;

  return s;
}

bool str_all_of(const char *s, char_predicate pred)
{
  return *str_find_if_not(s, pred) eq '\0';
}

bool str_any_of(const char *s, char_predicate pred)
{
  return not str_all_of(s, pred);
}

bool str_none_of(const char *s, char_predicate pred)
{
  return str_find_if(s, pred) eq '\0';
}

size_t str_count_if(const char *s, char_predicate pred)
{
  size_t count = 0;

  while (*s != '\0')
  {
    if (pred.apply(*s))
      count++;
    s++;
  }

  return count;
}

bool str_equals(
    const char *l,
    const char *r)
{
  while (*l eq * r and *l not_eq '\0')
  {
    l++;
    r++;
  }

  return *l eq * r and l eq '\0';
}

bool str_start_with(
    const char *l,
    const char *r)
{
  while (*l eq * r and *r not_eq '\0')
  {
    l++;
    r++;
  }

  return *r == '\0';
}

bool str_in(const char *s, const char c)
{
  return *str_find(s, c) eq c;
}

size_t str_len(const char *s)
{
  const char *b = s;

  while (*s not_eq '\0')
    s++;

  return s - b;
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

char_transform make_char_transform(char (*apply)(const char))
{
  char_transform cht;
  cht.apply = apply;
  return cht;
}

void str_transform(char *s, char_transform cht)
{
  while (*s not_eq '\0')
    *s = cht.apply(*s);
}

