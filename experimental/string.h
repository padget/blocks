#ifndef __blocks_string_h__
# define __blocks_string_h__

# include "array.h"
# include <stdlib.h>
# include <stdbool.h>

struct char_predicate
{
  bool (*apply)(char c);
};

typedef struct char_predicate char_predicate;

char_predicate make_char_predicate(bool(*apply)(char));

char* str_find(char* s, char c);
char* str_find_if(char* s, char_predicate pred);
char* str_find_if_not(char* s, char_predicate pred);

bool str_all_of(char* s, char_predicate pred);
bool str_any_of(char* s, char_predicate pred);
bool str_none_of(char* s, char_predicate pred);

size_t str_count_if(char* s, char_predicate pred);
size_t str_count(char* s, char c);

bool str_equals(char* l, char* r);
bool str_start_with(char* l, char* r);
bool str_in(char* s, char c);
bool str_contains_only(char* s, char* onlys);

size_t str_len(char* s);

void str_copy(char* s, char* s2);

struct char_transform
{
  char (*apply)(char);
};

typedef struct char_transform char_transform;

char_transform make_char_transform (char(*apply)(char));

void str_transform(char* s, char_transform cht);
void str_replace_if(char* s, char c, char_predicate pred);
void str_replace(char* s, char old, char new);
void str_remove_if(char* s, char_predicate pred); // TODO

#endif