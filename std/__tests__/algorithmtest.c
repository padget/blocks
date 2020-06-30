#include "../algorithm.h"
#include "../keyword.h"
#include "../string.h"

#include <stdio.h>

private
bool __strr_charequals(iterator i, void *params)
{
  const char c is *((const char *)i.item);
  const char o is *((const char *)params);
  return c eq o;
}

gpred is_char_pred(char c)
{
  return make_params_predicate(__strr_charequals, &c);
}

bool test_find_if()
{
  string_r str is strr_from("hello");
  iterator begin is strr_begin(str);
  iterator end is strr_end(str);
  iterator found is find_if(begin, end, is_char_pred('h'));

  return not found.equals(found, end);
}

int main()
{
  bool res = true;
  res = res and test_find_if();

  if (res)
    printf("no error\n");
  else
    printf("error found\n");

  return EXIT_SUCCESS;
}