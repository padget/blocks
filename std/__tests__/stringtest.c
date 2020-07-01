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

bool test_strr_fromrw()
{
  string_rw strrw = strrw_from("coucou");
  string_r strr = strr_fromrw(strrw);

  char *rwb = strrw.begin;
  const char *rb = strr.begin;

  while (rb not_eq strr.end and
         rwb not_eq strrw.end)
  {
    inc rb;
    inc rwb;
  }

  bool res = rb eq strr.end and
             rwb eq strrw.end;
  strrw_del(&strrw);
  return res;
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

int main()
{
  bool res = true;

  res = res and test_strr_new();
  res = res and test_strr_from();
  res = res and test_strr_copy();
  res = res and test_strr_fromrw();

  res = res and test_strrw_new();
  res = res and test_strrw_copy();
  res = res and test_strrw_from();
  res = res and test_strrw_del();
  res = res and test_strrw_len();

  if (res)
    printf("no error\n");
  else
    printf("error found\n");

  return EXIT_SUCCESS;
}