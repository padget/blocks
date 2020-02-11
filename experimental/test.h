#ifndef __experimental_test_h__
# define __experimental_test_h__

# include <stdbool.h>
# include <stdio.h>

# define TEST void

typedef void(**testf)();

FILE* tst_rout();
void tst_setrout(FILE* rout);
void tst_assert ( const char* descr, bool test );
void tst_suite ( const char* descr, testf** tests );

#endif
