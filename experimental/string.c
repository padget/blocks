#include <assert.h>

#include "string.h"
#include "algorithm.h"
#include "keyword.h"

char_predicate make_char_predicate(bool (*apply)(char))
{
  char_predicate pred;
  pred.apply = apply;
  return pred;
}

char *str_find(char *s, char c)
{
  while (*s not_eq c)
    s++;

  return s;
}

char *str_find_if(char *s, char_predicate pred)
{
  while (*s not_eq '\0' and not pred.apply(*s))
    s++;

  return s;
}

char *str_find_if_not(char *s, char_predicate pred)
{
  while (*s not_eq '\0' and pred.apply(*s))
    s++;

  return s;
}

bool str_all_of(char *s, char_predicate pred)
{
  return *str_find_if_not(s, pred) eq '\0';
}

bool str_any_of(char *s, char_predicate pred)
{
  return not str_all_of(s, pred);
}

bool str_none_of(char *s, char_predicate pred)
{
  return *str_find_if(s, pred) eq '\0';
}

size_t str_count_if(char *s, char_predicate pred)
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

size_t str_count(char *s, char c)
{
  size_t count = 0;

  while (*s != '\0')
  {
    if (*s eq c)
      count++;
    s++;
  }

  return count;
}

bool str_equals(
    char *l,
    char *r)
{
  while (*l eq * r and *l not_eq '\0')
  {
    l++;
    r++;
  }

  return *l eq * r and *l eq '\0';
}

bool str_start_with(
    char *l,
    char *r)
{
  while (*l eq * r and *r not_eq '\0')
  {
    l++;
    r++;
  }

  return *r == '\0';
}

bool str_in(char *s, char c)
{
  return *str_find(s, c) eq c;
}

bool str_contains_only(char *s, char *onlys)
{
  while (*s not_eq '\0' and str_in(onlys, *s))
    s++;

  return *s == '\0';
}

size_t str_len(char *s)
{
  char *b = s;

  while (*s not_eq '\0')
    s++;

  return s - b;
}

void str_copy(char *s, char *s2)
{
  while (*s != '\0')
  {
    *s2 = *s;
    s++;
    s2++;
  }
}

char_transform make_char_transform(char (*apply)(char))
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

void str_replace_if(char *s, char c, char_predicate pred)
{
  while (*s not_eq '\0')
  {
    if (pred.apply(*s))
      *s = c;
    s++;
  }
}

#include "../experimental/log.h"

void str_replace(char* s, char old, char new)
{
  while (*s not_eq '\0')
  {
    if (*s eq old)
      *s = new;
    s++;
  }
}
