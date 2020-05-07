#ifndef __blocks_string_h__
# define __blocks_string_h__

# include "array.h"
# include <stdlib.h>
# include <stdbool.h>

struct char_predicate
{
  bool (*apply)(const char c);
};

typedef struct char_predicate char_predicate;

char_predicate make_char_predicate(bool(*apply)(const char));

const char* str_find(const char* s, const char c);
const char* str_find_if(const char* s, char_predicate pred);
const char* str_find_if_not(const char* s, char_predicate pred);

bool str_all_of(const char* s, char_predicate pred);
bool str_any_of(const char* s, char_predicate pred);
bool str_none_of(const char* s, char_predicate pred);

size_t str_count_if(const char* s, char_predicate pred);

bool str_equals(const char* l, const char* r);
bool str_start_with(const char* l, const char* r);
bool str_in(const char* s, const char c);

size_t str_len(const char* s);

void str_copy(const char* s, char* s2);

struct char_transform
{
  char (*apply)(const char);
};

typedef struct char_transform char_transform;

char_transform make_char_transform (char(*apply)(const char));

void str_transform(char* s, char_transform cht);
void str_remove_if(char* s, char_predicate pred);

#endif