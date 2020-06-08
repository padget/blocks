#include "string.h"
#include "algorithm.h"
#include "keyword.h"

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
iterator __strr_begin(string_r strr)
{
  return iter_new((void *)strr.begin, sizeof(char));
}

private
iterator __strr_end(string_r strr)
{
  return iter_new((void *)strr.end, sizeof(char));
}

private
bool __strr_charequals(iterator i, void *params)
{
  const char c is *((const char *)i.item);
  const char o is *((const char *)params);
  return c eq o;
}

strr_iterator strr_find(string_r strr, char c)
{
  gpred pred is make_params_predicate(__strr_charequals, &c);
  iterator beg is __strr_begin(strr);
  iterator end is __strr_end(strr);
  iterator res is find_if(beg, end, pred);
  return (strr_iterator)res.item;
}

strr_iterator strr_find_if(string_r strr, char_predicate pred)
{
  gpred predb is make_simple_predicate(pred);
  iterator beg is __strr_begin(strr);
  iterator end is __strr_end(strr);
  iterator res is find_if(beg, end, predb);
  return (strr_iterator)res.item;
}

strr_iterator strr_find_if_not(string_r strr, char_predicate pred)
{
  gpred predb is make_simple_predicate(pred);
  iterator beg is __strr_begin(strr);
  iterator end is __strr_end(strr);
  iterator res is find_if_not(beg, end, predb);
  return (strr_iterator)res.item;
}

size_t strr_count(string_r strr, char c)
{
  gpred pred is make_params_predicate(__strr_charequals, &c);
  iterator beg is __strr_begin(strr);
  iterator end is __strr_end(strr);
  return count_if(beg, end, pred);
}

size_t strr_count_if(string_r strr, char_predicate pred)
{
  gpred predb is make_simple_predicate(pred);
  iterator beg is __strr_begin(strr);
  iterator end is __strr_end(strr);
  return count_if(beg, end, predb);
}

bool strr_all_of(string_r strr, char_predicate pred)
{
  gpred predb is make_simple_predicate(pred);
  iterator beg is __strr_begin(strr);
  iterator end is __strr_end(strr);
  return all_of(beg, end, predb);
}

bool strr_any_of(string_r strr, char_predicate pred)
{
  gpred predb is make_simple_predicate(pred);
  iterator beg is __strr_begin(strr);
  iterator end is __strr_end(strr);
  return any_of(beg, end, predb);
}

bool strr_none_of(string_r strr, char_predicate pred)
{
  gpred predb is make_simple_predicate(pred);
  iterator beg is __strr_begin(strr);
  iterator end is __strr_end(strr);

  return none_of(beg, end, predb);
}

bool strr_equals(string_r l, string_r r)
{
  return equals(
      __strr_begin(l), __strr_end(l),
      __strr_begin(r), __strr_end(r));
}

bool strr_start_with(string_r l, string_r r)
{
  return start_with(
      __strr_begin(l), __strr_end(l),
      __strr_begin(r), __strr_end(r));
}

bool strr_end_with(string_r l, string_r r)
{
  return end_with(
      __strr_begin(l), __strr_end(l),
      __strr_begin(r), __strr_end(r));
}

bool strr_in(string_r strr, const char c)
{
  return strr_find(strr, c) not_eq strr.end;
}

bool strr_contains_only(string_r s, string_r onlys)
{
  iterator beg is __strr_begin(s);
  iterator end is __strr_end(s);

  while (not iter_same(beg, end) and strr_in(onlys, *(char *)beg.item))
    beg is iter_next(beg);

  return iter_same(beg, end);
}

///////////////////////////////:

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

strrw_iterator strrw_find(string_rw strr, char c)
{
  return (strrw_iterator)
      strr_find(strr_fromrw(strr), c);
}

strrw_iterator strrw_find_if(string_rw strr, char_predicate pred)
{
  return (strrw_iterator)
      strr_find_if(strr_fromrw(strr), pred);
}

strrw_iterator strrw_find_if_not(string_rw strr, char_predicate pred)
{
  return (strrw_iterator)
      strr_find_if_not(strr_fromrw(strr), pred);
}

size_t strrw_count(string_rw strr, char c)
{
  return strr_count(strr_fromrw(strr), c);
}

size_t strrw_count_if(string_rw strr, char_predicate pred)
{
  return strr_count_if(strr_fromrw(strr), pred);
}

bool strrw_all_of(string_rw strr, char_predicate pred)
{
  return strr_all_of(strr_fromrw(strr), pred);
}

bool strrw_any_of(string_rw strr, char_predicate pred)
{
  return strr_any_of(strr_fromrw(strr), pred);
}

bool strrw_none_of(string_rw strr, char_predicate pred)
{
  return strr_none_of(strr_fromrw(strr), pred);
}

bool strrw_equals(string_rw l, string_r r)
{
  return strr_equals(strr_fromrw(l), r);
}

bool strrw_start_with(string_rw l, string_r r)
{
  return strr_start_with(strr_fromrw(l), r);
}

bool strrw_end_with(string_rw l, string_r r)
{
  return strr_end_with(strr_fromrw(l), r);
}

bool strrw_in(string_rw s, const char c)
{
  return strr_in(strr_fromrw(s), c);
}

bool strrw_contains_only(string_rw s, string_r onlys)
{
  return strr_contains_only(strr_fromrw(s), onlys);
}

void strrw_replace(string_rw s, const char old, const char neo)
{
  strrw_iterator ch;

  while ((ch is strrw_find(s, old)) not_eq s.end)
    *ch is neo;
}

