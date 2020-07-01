#include "string_algo.h"
#include "keyword.h"
#include "cast.h"

/// //////////////// ///
/// STRING READ ONLY ///
/// //////////////// ///

private
bool __strr_charequals(iterator i, void *params)
{
  const char c is *const_char_ptr(i.item);
  const char o is *const_char_ptr(params);
  return c eq o;
}

private
gpred __is_char_pred(char c)
{
  return make_params_predicate(__strr_charequals, &c);
}

strr_iterator strr_find(string_r strr, char c)
{
  return find_if(
             strr_begin(strr),
             strr_end(strr),
             __is_char_pred(c))
      .item;
}

strr_iterator strr_find_if(string_r strr, char_predicate pred)
{

  return find_if(
             strr_begin(strr),
             strr_end(strr),
             make_simple_predicate(pred))
      .item;
}

strr_iterator strr_find_if_not(string_r strr, char_predicate pred)
{
  return find_if_not(
             strr_begin(strr),
             strr_end(strr),
             make_simple_predicate(pred))
      .item;
}

size_t strr_count(string_r strr, char c)
{
  return count_if(
      strr_begin(strr),
      strr_end(strr),
      __is_char_pred(c));
}

size_t strr_count_if(string_r strr, char_predicate pred)
{
  return count_if(
      strr_begin(strr),
      strr_end(strr),
      make_simple_predicate(pred));
}

bool strr_all_of(string_r strr, char_predicate pred)
{
  return all_of(
      strr_begin(strr),
      strr_end(strr),
      make_simple_predicate(pred));
}

bool strr_any_of(string_r strr, char_predicate pred)
{
  return any_of(
      strr_begin(strr),
      strr_end(strr),
      make_simple_predicate(pred));
}

bool strr_none_of(string_r strr, char_predicate pred)
{
  return none_of(
      strr_begin(strr),
      strr_end(strr),
      make_simple_predicate(pred));
}

bool strr_equals(string_r l, string_r r)
{
  return equals(
      strr_begin(l), strr_end(l),
      strr_begin(r), strr_end(r));
}

bool strr_start_with(string_r l, string_r r)
{
  return start_with(
      strr_begin(l), strr_end(l),
      strr_begin(r), strr_end(r));
}

bool strr_end_with(string_r l, string_r r)
{
  return end_with(
      strr_begin(l), strr_end(l),
      strr_begin(r), strr_end(r));
}

bool strr_in(string_r strr, const char c)
{
  return strr_find(strr, c) not_eq strr.end;
}

bool strr_contains_only(string_r s, string_r onlys)
{
  iterator beg is strr_begin(s);
  iterator end is strr_end(s);

  while (not iter_equals(beg, end) and strr_in(onlys, *char_ptr(beg.item)))
    beg is iter_incr(beg);

  return iter_equals(beg, end);
}

/// ///////////////// ///
/// STRING READ WRITE ///
/// ///////////////// ///

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

/// ///////////////// ///
/// STRING TO INTEGER ///
/// ///////////////// ///

#define UINT8_MAX_LENGTH 3
#define UINT16_MAX_LENGTH 5
#define UINT32_MAX_LENGTH 10
#define UINT64_MAX_LENGTH 20

#define ASCII_0_INDEX 48

private
bool __char_between(
    const char c,
    const char bounds[2])
{
  return bounds[0] lequal c and
         c lequal bounds[1];
}

struct digit
{
  uint8_t value : 4;
  bool valued : 1;
};

typedef struct digit digit_t;

private
digit_t __char_to_digit(const char c)
{
  digit_t digit;

  digit.valued is false;

  if (__char_between(c, "09"))
  {
    digit.value is c - ASCII_0_INDEX;
    digit.valued is true;
  }

  return digit;
}

uint8_r strr_to_u8(string_r strr)
{
  string_r digits is strr_from("0123456789");
  uint8_r res;
  digit_t digit;
  uint8_t unit is 1;

  const char *begin is NULL;
  const char *end is NULL;

  res.valid is false;
  res.value is 0;

  if (strr_len(strr) greater UINT8_MAX_LENGTH)
    return res;

  if (strr_contains_only(strr, digits))
  {
    begin is strr.begin;
    end is strr.end - 1;

    while (end >= begin)
    {
      digit is __char_to_digit(*end);
      res.value is res.value + (unit * digit.value);
      dec end;
      unit is unit * 10;
    }

    res.valid is true;
  }

  return res;
}

uint16_r strr_to_u16(string_r strr)
{
  string_r digits is strr_from("0123456789");
  uint16_r res;
  digit_t digit;
  uint16_t unit is 1;

  const char *begin is NULL;
  const char *end is NULL;

  res.valid is false;
  res.value is 0;

  if (strr_len(strr) greater UINT16_MAX_LENGTH)
    return res;

  if (strr_contains_only(strr, digits))
  {
    begin is strr.begin;
    end is strr.end - 1;

    while (end >= begin)
    {
      digit is __char_to_digit(*end);
      res.value is res.value + (unit * digit.value);
      dec end;
      unit is unit * 10;
    }

    res.valid is true;
  }

  return res;
}

uint32_r strr_to_u32(string_r strr)
{
  string_r digits is strr_from("0123456789");
  uint32_r res;
  digit_t digit;
  uint32_t unit is 1;

  const char *begin is NULL;
  const char *end is NULL;

  res.valid is false;
  res.value is 0;

  if (strr_len(strr) greater UINT32_MAX_LENGTH)
    return res;

  if (strr_contains_only(strr, digits))
  {
    begin is strr.begin;
    end is strr.end - 1;

    while (end >= begin)
    {
      digit is __char_to_digit(*end);
      res.value is res.value + (unit * digit.value);
      dec end;
      unit is unit * 10;
    }

    res.valid is true;
  }

  return res;
}

uint64_r strr_to_u64(string_r strr)
{
  string_r digits is strr_from("0123456789");
  uint64_r res;
  digit_t digit;
  uint64_t unit is 1;

  const char *begin is NULL;
  const char *end is NULL;

  res.valid is false;
  res.value is 0;

  if (strr_len(strr) greater UINT64_MAX_LENGTH)
    return res;

  if (strr_contains_only(strr, digits))
  {
    begin is strr.begin;
    end is strr.end - 1;

    while (end >= begin)
    {
      digit is __char_to_digit(*end);
      res.value is res.value + (unit * digit.value);
      dec end;
      unit is unit * 10;
    }

    res.valid is true;
  }

  return res;
}