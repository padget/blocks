#include "string.h"
#include "algorithm.h"
#include "keyword.h"

string_r strr_new(strr_iterator beg, strr_iterator end)
{
  return (string_r){
      .begin = beg,
      .end = end};
}

string_r strr_copy(string_r strr)
{
  return strr_new(strr.begin, strr.end);
}

string_r strr_from(const char *str)
{
  const char *begin = str;
  const char *end = str;

  while (end not_eq NULL and *end not_eq '\0')
    inc end;

  return strr_new(begin, end);
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
  const char c = *((const char *)i.item);
  const char o = *((const char *)params);
  return c eq o;
}

strr_iterator strr_find(string_r strr, char c)
{
  gpred pred = make_params_predicate(__strr_charequals, &c);
  iterator beg = __strr_begin(strr);
  iterator end = __strr_end(strr);
  iterator res = find_if(beg, end, pred);
  return (strr_iterator)res.item;
}

strr_iterator strr_find_if(string_r strr, char_predicate pred)
{
  gpred predb = make_simple_predicate(pred);
  iterator beg = __strr_begin(strr);
  iterator end = __strr_end(strr);
  iterator res = find_if(beg, end, predb);
  return (strr_iterator)res.item;
}

strr_iterator strr_find_if_not(string_r strr, char_predicate pred)
{
  gpred predb = make_simple_predicate(pred);
  iterator beg = __strr_begin(strr);
  iterator end = __strr_end(strr);
  iterator res = find_if_not(beg, end, predb);
  return (strr_iterator)res.item;
}

size_t strr_count(string_r strr, char c)
{
  gpred pred = make_params_predicate(__strr_charequals, &c);
  iterator beg = __strr_begin(strr);
  iterator end = __strr_end(strr);
  return count_if(beg, end, pred);
}

size_t strr_count_if(string_r strr, char_predicate pred)
{
  gpred predb = make_simple_predicate(pred);
  iterator beg = __strr_begin(strr);
  iterator end = __strr_end(strr);
  return count_if(beg, end, predb);
}

bool strr_all_of(string_r strr, char_predicate pred)
{
  gpred predb = make_simple_predicate(pred);
  iterator beg = __strr_begin(strr);
  iterator end = __strr_end(strr);
  return all_of(beg, end, predb);
}

bool strr_any_of(string_r strr, char_predicate pred)
{
  gpred predb = make_simple_predicate(pred);
  iterator beg = __strr_begin(strr);
  iterator end = __strr_end(strr);
  return any_of(beg, end, predb);
}

bool strr_none_of(string_r strr, char_predicate pred)
{
  gpred predb = make_simple_predicate(pred);
  iterator beg = __strr_begin(strr);
  iterator end = __strr_end(strr);

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

bool strr_in(string_r strr, const char c)
{
  return strr_find(strr, c) not_eq strr.end;
}

bool strr_contains_only(string_r s, string_r onlys)
{
  iterator beg = __strr_begin(s);
  iterator end = __strr_end(s);

  while (not iter_same(beg, end) and strr_in(onlys, *(char *)beg.item))
    beg = iter_next(beg);

  return iter_same(beg, end);
}

///////////////////////////////:

string_rw strrw_new(char *beg, char *end)
{
  return (string_rw){
      .begin = beg,
      .end = end};
}

string_rw strrw_from(char *str)
{
  const char *begin = str;
  const char *end = str;

  while (end not_eq NULL and *end not_eq '\0')
    inc end;

  return strrw_new(begin, end);
}

string_rw strrw_copy(string_rw strr);
string_rw strrw_from(char *str);
void strr_del(string_rw strr);