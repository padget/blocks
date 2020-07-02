#include "../io.h"
#include "../keyword.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

bool test_filero_open()
{
  string_r filename is strr_from("std/__tests__/resources/data.csv");
  filero f is filero_open(filename);
  bool res is f.file not_null;
  filero_close(f);
  return res;
}

bool test_filero_readall()
{
  string_r filename is strr_from("std/__tests__/resources/data.csv");
  filero f is filero_open(filename);
  string_rw content is filero_readall(f);
  bool res is strrw_len(content) eq 82;
  filero_close(f);
  strrw_del(&content);
  return res;
}

int main()
{
  bool res is true;

  res is res and test_filero_open();
  res is res and test_filero_readall();

  if (res)
    printf("no error\n");
  else
    printf("error found\n");

  return EXIT_SUCCESS;
}