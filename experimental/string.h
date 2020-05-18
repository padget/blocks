#ifndef __blocks_string_h__
# define __blocks_string_h__

# include "array.h"
# include <stdlib.h>
# include <stdbool.h>

typedef bool(*char_predicate)(const char);

char* str_find(char* s, char c);
char* str_find_if(char* s, char_predicate pred);
char* str_find_if_not(char* s, char_predicate pred);


void str_copy(const char* s, char* s2);

typedef char (*char_transform)(char);

void str_transform(char* s, char_transform cht);
void str_replace_if(char* s, char c, char_predicate pred);
void str_replace(char* s, char old, char new);

void str_remove_if(char* s, char_predicate pred); // TODO

#endif