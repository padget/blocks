#include "test.h"

int add (int a, int b)
{
  return a + b;
}

void add_test()
{
  tst_assert("add equality", add(1, 1) == 2);
  tst_assert("add difference", add(1, 2) != 1);
}

int main ()
{
  testf** tests = {&add_test, NULL};
  tst_suite("test of add function", tests)
}
