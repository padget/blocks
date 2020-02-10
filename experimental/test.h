#ifndef __experimental_test_h__
# define __experimental_test_h__

# include <stdbool.h>
# include <stdio.h>

# define TEST void
typedef void(*testf)();

FILE* tst_rout();
void tst_setrout(FILE* rout);
void tst_assert ( const char* descr, bool test );
void tst_suite ( const char* descr, testf** tests );

/*
int add(int i1, int i2)
{
  return i1+i2;
}

#define TEST void
TEST add_test ()
{
  tst_assert ( add ( 1, 2 ) == 3, " 1 + 2 == 3 " );
  tst_assert ( add ( 1, 2 ) == 3, " 1 + 2 == 3 " );
}



int protomain(int argc, char** argv)
{
  tst_assert ( add ( 1, 2 ) == 3, " 1 + 2 == 3 " ); // OK
  tst_assert ( add ( 2, 3 ) == 2, " 2 + 3 != 2 " ); // KO

  tst_suite ( "test add ", &add_test);
}
*/

#endif
