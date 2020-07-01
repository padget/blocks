#ifndef __std_string_h__
#define __std_string_h__

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "algorithm.h"

#define EOS '\0'
#define EOL '\n'

/// ////// ///
/// COMMON ///
/// ////// ///

typedef bool (*char_predicate)(iterator);

struct string_rw
{
  char *begin;
  char *end;
};

typedef struct string_rw string_rw;
typedef char *strrw_iterator;

struct string_r
{
  const char *begin;
  const char *end;
};

typedef struct string_r string_r;
typedef const char *strr_iterator;

/// //////////////// ///
/// STRING READ ONLY ///
/// //////////////// ///

iterator strr_begin(string_r strr);
iterator strr_end(string_r strr);

string_r strr_new(const char *beg, const char *end);
string_r strr_copy(string_r strr);
string_r strr_from(const char *str);
string_r strr_fromrw(string_rw strrw);

size_t strr_len(string_r strr);

/// ///////////////// ///
/// STRING READ WRITE ///
/// ///////////////// ///

iterator strrw_begin(string_rw strr);
iterator strrw_end(string_rw strr);

string_rw strrw_new(const char *beg, const char *end);
string_rw strrw_copy(string_rw strr);
string_rw strrw_from(const char *str);
void strrw_del(string_rw *strr);

size_t strrw_len(string_rw strr);

#endif
