#ifndef __blocks_cstring_h__
#define __blocks_cstring_h__ 

#include <stdbool.h>
#include <stdlib.h>

typedef bool(*cchar_predicate)(const char);

const char* cstr_find(const char* s, const char c);
const char* cstr_find_if(const char* s, cchar_predicate pred);
const char* cstr_find_if_not(const char* s, cchar_predicate pred);

size_t cstr_len(const char* s);

bool cstr_all_of(const char* s, cchar_predicate pred);
bool cstr_any_of(const char* s, cchar_predicate pred);
bool cstr_none_of(const char* s, cchar_predicate pred);

size_t cstr_count_if(const char* s, cchar_predicate pred);
size_t cstr_count(const char* s, const char c);

bool cstr_equals(const char* l, const char* r);
bool cstr_start_with(const char* l, const char* r);
bool cstr_in(const char* s, const char c);
bool cstr_contains_only(const char* s, const char* onlys);

#endif