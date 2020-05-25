#ifndef __blocks_utest_h__
#define __blocks_utest_h__

#include <stdbool.h>

typedef const char* message;

bool utest_assert(bool expr, message err);

#endif