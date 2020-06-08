#include "../string.h"
#include "../keyword.h"
#include "../utest.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

bool test_strr_new()
{
  const char *c = "hello";
  const char *ce = c + 5;
  string_r strr = strr_new(c, ce);
  return strr.begin eq c and
         strr.end eq ce;
}

bool test_strr_from()
{
  const char *c = "hello";
  const char *ce = c + 5;
  string_r strr = strr_from(c);
  return strr.begin eq c and
         strr.end eq ce;
}

bool test_strr_copy()
{
  string_r strr = strr_from("coucou");
  string_r copy = strr_copy(strr);
  return strr.begin eq copy.begin and
         strr.end eq copy.end;
}

bool test_strr_find()
{
  string_r strr = strr_from("hello world !");
  strr_iterator cfound = strr_find(strr, 'o');
  return *cfound eq 'o';
}

bool __is_o(iterator c)
{
  return *((char *)c.item)eq 'o';
}

bool test_strr_find_if()
{
  string_r strr = strr_from("hello world !");
  strr_iterator cfound = strr_find_if(strr, __is_o);
  return *cfound eq 'o';
}

bool test_strr_find_if_not()
{
  string_r strr = strr_from("hello world !");
  strr_iterator cfound = strr_find_if_not(strr, __is_o);
  return *cfound eq 'h';
}

bool test_strr_count()
{
  string_r strr = strr_from("hello world !");
  size_t count = strr_count(strr, 'l');
  return count eq 3;
}

bool __is_l(iterator it)
{
  return *(const char *)it.item eq 'l';
}

bool test_strr_count_if()
{
  string_r strr = strr_from("hello world !");
  size_t count = strr_count_if(strr, __is_l);
  return count eq 3;
}

bool test_strr_all_of()
{
  string_r strr = strr_from("lllllllll");
  return strr_all_of(strr, __is_l);
}

bool test_strr_any_of()
{
  string_r strr = strr_from("ooooollll");
  return strr_any_of(strr, __is_l);
}

bool test_strr_none_of()
{
  string_r strr = strr_from("ooooooooo");
  return strr_none_of(strr, __is_l);
}

bool test_strr_equals()
{
  string_r strr = strr_from("ooooo");
  string_r strr2 = strr_from("ooooo");
  return strr_equals(strr, strr2);
}

bool test_strr_start_with()
{
  string_r strr = strr_from("coucou");
  string_r cou = strr_from("cou");
  return strr_start_with(strr, cou);
}

bool test_strr_end_with()
{
  string_r hello = strr_from("hello");
  string_r llo = strr_from("llo");
  return strr_end_with(hello, llo);
}

bool test_strr_in()
{
  string_r strr = strr_from("coucou");
  return strr_in(strr, 'c');
}

bool test_strr_contains_only()
{
  string_r strr = strr_from("12542");
  string_r digits = strr_from("0123456789");
  return strr_contains_only(strr, digits);
}

///////////////////////////////////////

bool test_strrw_new()
{
  const char *hello = "hello world !";
  string_rw str = strrw_new(hello, hello + 13);
  bool res = *str.begin eq 'h' and *str.end eq '\0';
  strrw_del(&str);
  return res;
}

bool test_strrw_copy()
{
  const char *hello = "hello world !";
  string_rw str = strrw_new(hello, hello + 13);
  string_rw copy = strrw_copy(str);
  bool res = *copy.begin eq 'h' and *copy.end eq '\0';
  strrw_del(&str);
  strrw_del(&copy);
  return res;
}

bool test_strrw_from()
{
  const char *hello = "hello";
  string_rw str = strrw_from(hello);
  bool res = *str.begin eq 'h' and *str.end eq '\0';
  strrw_del(&str);
  return res;
}

bool test_strrw_del()
{
  const char *hello = "hello";
  string_rw str = strrw_from(hello);
  strrw_del(&str);
  return str.begin eq NULL and str.end eq NULL;
}

bool test_strrw_len()
{
  string_rw hello = strrw_from("hello");
  bool res = strrw_len(hello) eq 5;
  strrw_del(&hello);
  return res;
}

bool test_strrw_find()
{
  string_rw hello = strrw_from("hello");
  bool res = *strrw_find(hello, 'h') eq 'h';
  strrw_del(&hello);
  return res;
}

bool test_strrw_find_if()
{
  string_rw hello = strrw_from("hello");
  bool res = *strrw_find_if(hello, __is_l) eq 'l';
  strrw_del(&hello);
  return res;
}

bool test_strrw_find_if_not()
{
  string_rw hello = strrw_from("hello");
  bool res = *strrw_find_if_not(hello, __is_l) eq 'h';
  strrw_del(&hello);
  return res;
}

bool test_strrw_count()
{
  string_rw hello = strrw_from("hello");
  bool res = strrw_count(hello, 'h') eq 1;
  strrw_del(&hello);
  return res;
}

bool test_strrw_count_if()
{
  string_rw hello = strrw_from("hello");
  bool res = strrw_count_if(hello, __is_l) eq 2;
  strrw_del(&hello);
  return res;
}

bool test_strrw_all_of()
{
  string_rw strr = strrw_from("lllllllll");
  bool res = strrw_all_of(strr, __is_l);
  strrw_del(&strr);
  return res;
}

bool test_strrw_any_of()
{
  string_rw strr = strrw_from("ooooollll");
  bool res = strrw_any_of(strr, __is_l);
  strrw_del(&strr);
  return res;
}

bool test_strrw_none_of()
{
  string_rw strr = strrw_from("ooooooooo");
  bool res = strrw_none_of(strr, __is_l);
  strrw_del(&strr);
  return res;
}

bool test_strrw_equals()
{
  string_rw strr = strrw_from("ooooo");
  string_r strr2 = strr_from("ooooo");
  bool res = strrw_equals(strr, strr2);
  strrw_del(&strr);
  return res;
}

bool test_strrw_start_with()
{
  string_rw strr = strrw_from("coucou");
  string_r cou = strr_from("cou");
  bool res = strrw_start_with(strr, cou);
  strrw_del(&strr);
  return res;
}

bool test_strrw_end_with()
{
  string_rw hello = strrw_from("hello");
  string_r llo = strr_from("llo");
  bool res = strrw_end_with(hello, llo);
  strrw_del(&hello);
  return res;
}

bool test_strrw_in()
{
  string_rw strr = strrw_from("coucou");
  bool res = strrw_in(strr, 'c');
  strrw_del(&strr);
  return res;
}

bool test_strrw_contains_only()
{
  string_rw strr = strrw_from("12542");
  string_r digits = strr_from("0123456789");
  bool res = strrw_contains_only(strr, digits);
  strrw_del(&strr);
  return res;
}

bool test_strrw_replace()
{
  string_rw hello = strrw_from("hello");
  strrw_replace(hello, 'l', 'd');
  string_r heddo = strr_from("heddo");
  bool res = strr_equals(strr_fromrw(hello), heddo);
  strrw_del(&hello);

  return res;
}

int main()
{
  bool res = true;

  res = res and test_strr_new();
  res = res and test_strr_from();
  res = res and test_strr_copy();
  res = res and test_strr_find();
  res = res and test_strr_find_if();
  res = res and test_strr_find_if_not();
  res = res and test_strr_count();
  res = res and test_strr_count_if();
  res = res and test_strr_all_of();
  res = res and test_strr_none_of();
  res = res and test_strr_any_of();
  res = res and test_strr_equals();
  res = res and test_strr_start_with();
  res = res and test_strr_end_with();
  res = res and test_strr_in();
  res = res and test_strr_contains_only();

  res = res and test_strrw_new();
  res = res and test_strrw_copy();
  res = res and test_strrw_from();
  res = res and test_strrw_del();
  res = res and test_strrw_len();
  res = res and test_strrw_find();
  res = res and test_strrw_find_if();
  res = res and test_strrw_find_if_not();
  res = res and test_strrw_count();
  res = res and test_strrw_count_if();
  res = res and test_strrw_all_of();
  res = res and test_strrw_any_of();
  res = res and test_strrw_none_of();
  res = res and test_strrw_equals();
  res = res and test_strrw_start_with();
  res = res and test_strrw_end_with();
  res = res and test_strrw_in();
  res = res and test_strrw_contains_only();
  res = res and test_strrw_replace();

  if (res)
    printf("no error");
  else
    printf("error found");

  return EXIT_SUCCESS;
}