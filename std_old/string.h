#ifndef __blocks_string_h__
#define __blocks_string_h__

#include <stdlib.h>
#include <stdbool.h>



typedef bool (*char_predicate)(const char);

const char *str_cfind(const char *s, const char c);
const char *str_cfind_if(const char *s, char_predicate pred);
const char *str_cfind_if_not(const char *s, char_predicate pred);

char *str_find(char *s, char c);
char *str_find_if(char *s, char_predicate pred);
char *str_find_if_not(char *s, char_predicate pred);

size_t str_len(const char* s);

bool str_all_of(const char* s, char_predicate pred);
bool str_any_of(const char* s, char_predicate pred);
bool str_none_of(const char* s, char_predicate pred);

size_t str_count_if(const char* s, char_predicate pred);
size_t str_count(const char* s, const char c);

bool str_equals(const char* l, const char* r);
bool str_start_with(const char* l, const char* r);
bool str_in(const char* s, const char c);
bool str_contains_only(const char* s, const char* onlys);

typedef char (*char_transform)(char);

void str_transform(char *s, char_transform cht);
void str_replace_if(char *s, char c, char_predicate pred);
void str_replace(char *s, char old, char new);

void str_remove_if(char *s, char_predicate pred); // TODO

void str_copy(const char *s, char *s2);





#endif