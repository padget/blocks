#ifndef __blocks_std_char_h__
# define __blocks_std_char_h__ 

# include <stdbool.h>

bool char_in(const char c, const char* chars);
bool char_inb(const char c, const char bounds[2]);
bool char_is(const char c, const char c2);

#endif