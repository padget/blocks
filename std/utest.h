#ifndef __blocks_utest_h__
#define __blocks_utest_h__

#include <stdbool.h>
#include <stdlib.h>

struct utest_report 
{
  size_t nb_errors;
  size_t nb_passed;
  size_t nb_tests;
};

typedef struct utest_report utest_report;

typedef const char* message;

bool utest_assert(bool expr, message err, utest_report *report);

#endif