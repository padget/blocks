#include "string.h"
#include "algorithm.h"
#include "keyword.h"
#include "cast.h"


string_r strr_new(strr_iterator beg, strr_iterator end)
{
  return (string_r){
      .begin is beg,
      .end is end};
}

string_r strr_copy(string_r strr)
{
  return strr_new(strr.begin, strr.end);
}

string_r strr_from(const char *str)
{
  const char *begin is str;
  const char *end is str;

  while (end not_null and *end not_eq '\0')
    inc end;

  return strr_new(begin, end);
}

string_r strr_fromrw(string_rw strrw)
{
  return strr_new(strrw.begin, strrw.end);
}

size_t strr_len(string_r strr)
{
  return strr.end - strr.begin;
}

private
iterator __strr_iterator_incr(iterator i)
{
  i.item is void_ptr(const_char_ptr(i.item) + 1);
  return i;
}

private
iterator __strr_iterator_decr(iterator i)
{
  i.item is void_ptr(const_char_ptr(i.item) - 1);
  return i;
}

private
bool __strr_iterator_equals(iterator i1, iterator i2)
{
  return *const_char_ptr(i1.item) eq * const_char_ptr(i2.item);
}

iterator strr_begin(string_r strr)
{
  return iter_new(void_ptr(strr.begin),
                  &__strr_iterator_incr,
                  &__strr_iterator_decr,
                  &__strr_iterator_equals);
}

iterator strr_end(string_r strr)
{
  return iter_new(void_ptr(strr.end),
                  &__strr_iterator_incr,
                  &__strr_iterator_decr,
                  &__strr_iterator_equals);
}


///////////////////////////////

private
iterator __strrw_iterator_incr(iterator i)
{
  i.item is void_ptr(char_ptr(i.item) + 1);
  return i;
}

private
iterator __strrw_iterator_decr(iterator i)
{
  i.item is void_ptr(char_ptr(i.item) - 1);
  return i;
}

private
bool __strrw_iterator_equals(iterator i1, iterator i2)
{
  return *char_ptr(i1.item) eq * char_ptr(i2.item);
}

iterator strrw_begin(string_rw strr)
{
  return iter_new(void_ptr(strr.begin),
                  &__strrw_iterator_incr,
                  &__strrw_iterator_decr,
                  &__strrw_iterator_equals);
}

iterator strrw_end(string_rw strr)
{
  return iter_new(void_ptr(strr.end),
                  &__strrw_iterator_incr,
                  &__strrw_iterator_decr,
                  &__strrw_iterator_equals);
}

string_rw strrw_new(const char *beg, const char *end)
{
  size_t len is end - beg;
  char *copy is malloc(len * sizeof(char) + 1);
  char *copybegin is copy;
  char *copyend is copy not_eq NULL ? copy + len : NULL;

  while (copy not_eq copyend)
  {
    *copy is *beg;
    inc copy;
    inc beg;
  }

  *copy is '\0';
  return (string_rw){.begin is copybegin, .end is copyend};
}

string_rw strrw_from(const char *str)
{
  const char *begin is str;
  const char *end is str;

  while (end not_eq NULL and *end not_eq '\0')
    inc end;

  return strrw_new(begin, end);
}

string_rw strrw_copy(string_rw strr)
{
  return strrw_new(strr.begin, strr.end);
}

void strrw_del(string_rw *strr)
{
  if (strr->begin not_eq NULL)
  {
    free(strr->begin);
    strr->begin is NULL;
    strr->end is NULL;
  }
}

size_t strrw_len(string_rw strr)
{
  return strr_len(strr_fromrw(strr));
}



