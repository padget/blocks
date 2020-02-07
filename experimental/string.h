#ifndef __experimental_string_h__
# define __experimental_string_h__

# include <stdlib.h>
# include <stdio.h>

/**
 * A string represents a portion of 
 * string in memory. The string has been
 * initialized with dynamic allocation
 * and must be destroyed by calling free
 * function.
 */
typedef struct string
{
  char* data;
  size_t size;
}
string;

/**
 * Construct a default empty string;
 * here bstr and estr are NULL.
 *
 * @return empty string
 */
string s_default();

/**
 * Copy str into a new string (copy 
 * in memory).
 * 
 * @param str string to copy
 * @returns a new copy of str.
 */
string s_copy(const string str);

/**
 * Copy all chars between b and e
 * into a new string in memory. 
 * e must be accessible by b 
 * incrementation. If not, it will
 * be an undefined behaviour.
 * If the memory can't be allocated
 * a empty string will be returned.
 *
 * @param b begining of the string to copy
 * @param e end of the string to copy
 * @returns a copy of [b, e) chars
 */
string s_from_bounds(const char* b, const char* e);

/**
 * Reserves bytes in memory and
 * copy the cstring into the new
 * string.
 * 
 * @param cstr cstring to copy
 * @return string built by the copy
 */
string s_from_cstring(const char* cstr);

/**
 * Returns the size of s.
 * 
 * @param s string that can be sized
 * @returns the size of s
 */
size_t s_size(const string s);

/**
 * Deallocates the memmory of the 
 * string s.
 * 
 * @param s the string to destroy
 */
void s_free(string s);

/**
 * Constructs a new string from a file
 * opened in the read mode. The file must
 * be a textual file.
 * If a NULL f is passed, then an empty 
 * string will be returned.
 * 
 * @param f opened file to read into a string
 * @returns a new string filled with f content 
 */
string s_from_file(FILE* f);

const char* cs_find(const char* cs, const char* end, const char c);

#endif
