#ifndef __std_string_h__
#define __std_string_h__

#include <stdlib.h>
#include <stdbool.h>

#include "algorithm.h"

#define EOS '\0'
#define EOL '\n'

/// ////// ///
/// COMMON ///
/// ////// ///

typedef bool(*char_predicate)(iterator);

/// //////////////// ///
/// STRING READ ONLY ///
/// //////////////// ///

struct string_r
{
  const char *begin;
  const char *end;
};

typedef struct string_r string_r;
typedef const char *strr_iterator;

string_r strr_new(const char *beg, const char *end);
string_r strr_copy(string_r strr);
string_r strr_from(const char* str);

size_t strr_len(string_r strr);

strr_iterator strr_find(string_r strr, char c);
strr_iterator strr_find_if(string_r strr, char_predicate pred);
strr_iterator strr_find_if_not(string_r strr, char_predicate pred);

size_t strr_count(string_r strr, char c);
size_t strr_count_if(string_r strr, char_predicate pred);

bool strr_all_of(string_r strr, char_predicate pred);
bool strr_any_of(string_r strr, char_predicate pred);
bool strr_none_of(string_r strr, char_predicate pred);

bool strr_equals(string_r l, string_r r);
bool strr_start_with(string_r l, string_r r);
bool strr_in(string_r s, const char c);
bool strr_contains_only(string_r s, string_r onlys);

/// ///////////////// ///
/// STRING READ WRITE ///
/// ///////////////// ///

struct string_rw
{
  char* begin; 
  char* end;
};

typedef struct string_rw string_rw;
typedef char* strrw_iterator;

string_rw strrw_new(char *beg, char *end);
string_rw strrw_copy(string_rw strr);
string_rw strrw_from(char* str);
void strr_del(string_rw strr);

size_t strrw_len(string_rw strr);

strrw_iterator strrw_find(string_rw strr, char c);
strrw_iterator strrw_find_if(string_rw strr, char_predicate pred);
strrw_iterator strrw_find_if_not(string_rw strr, char_predicate pred);

size_t strrw_count(string_rw strr, char c);
size_t strrw_count_if(string_rw strr, char_predicate pred);

bool strrw_all_of(string_rw strr, char_predicate pred);
bool strrw_any_of(string_rw strr, char_predicate pred);
bool strrw_none_of(string_rw strr, char_predicate pred);

bool strrw_equals(string_rw l, string_r r);
bool strrw_start_with(string_rw l, string_r r);
bool strrw_in(string_rw s, const char c);
bool strrw_contains_only(string_rw s, string_r onlys);



#endif