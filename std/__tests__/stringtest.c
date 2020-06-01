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
  return *(const char *)it.item == 'l';
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
  res = res and test_strr_in();
  res = res and test_strr_contains_only();

  if (res)
    printf("no error");
  else
    printf("error found");

  return EXIT_SUCCESS;
}