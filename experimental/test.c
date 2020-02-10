#include "test.h"

static FILE* static_rout = STDOUT;

void tst_setrout ( FILE* rout )
{
  if (rout != NULL)
    static_rout = rout;
}

FILE* tst_rout () 
{
  return static_rout;
}

void tst_assert ( const char* descr, bool test )
{
  fprintf ( tst_rout (), "%s : %s\n", descr, ( test ? "OK" : "KO" ) );
}

void tst_suite ( const char* descr, testf** tests)
{


  fprintf ( tst_rout (), "##########\n%s\n");
  
  while (*tests != NULL)
  {
    *tests();
    tests++;
  }

  fprintf( tst_rout (), "end suite\n\n");

}
