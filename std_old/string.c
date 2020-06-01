
#include "string.h"
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

const char *cstr_find(const char *s, const char c)
{
  while (*s not_eq c)
    s++;

  return s;
}

const char *cstr_find_if(const char *s, char_predicate pred)
{
  while (*s not_eq '\0' and not pred(*s))
    s++;

  return s;
}

const char *cstr_find_if_not(const char *s, char_predicate pred)
{
  while (*s not_eq '\0' and pred(*s))
    s++;

  return s;
}

bool cstr_all_of(const char *s, char_predicate pred)
{
  return *cstr_find_if_not(s, pred) eq '\0';
}

bool cstr_any_of(const char *s, char_predicate pred)
{
  return not cstr_all_of(s, pred);
}

bool cstr_none_of(const char *s, char_predicate pred)
{
  return *cstr_find_if(s, pred) eq '\0';
}

size_t cstr_count_if(const char *s, char_predicate pred)
{
  size_t count = 0;

  while (*s != '\0')
  {
    if (pred(*s))
      count++;
    s++;
  }

  return count;
}

size_t cstr_count(const char *s, const char c)
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

bool cstr_equals(
    const char *l,
    const char *r)
{
  while (*l eq * r and *l not_eq '\0')
  {
    l++;
    r++;
  }

  return *l eq * r and *l eq '\0';
}

bool cstr_start_with(
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

bool cstr_in(const char *s, const char c)
{
  return *cstr_find(s, c) eq c;
}

bool cstr_contains_only(const char *s, const char *onlys)
{
  while (*s not_eq '\0' and cstr_in(onlys, *s))
    s++;

  return *s == '\0';
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
