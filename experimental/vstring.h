#ifndef __experimental_vstring_h__
# define __experimental_vstring_h__

#include <stdlib.h>
#include <stdbool.h>

/**
 * A vstring is a string view
 * It represents simply a iterating
 * view on a portion of an existing 
 * string.
 */
typedef struct vstring
{
  char* view;
  size_t size;
} 
vstring;

/**
 * Builds a vstring with the boundaries of the 
 * view. 
 *
 * @param begin the first character
 * @param end the after last character
 * @return a vstring built with begin and end
 */
vstring vstrbds ( char* begin, char* end );

/**
 * Builds a vstring with the the first character
 * and its size after begin.
 *
 * @param begin the first character
 * @param size the size of the view
 * @return a vstring built with begin and size
 */
vstring vstrlen ( char* begin, size_t size );

/**
 * Compares two vstring by a lexicalographic order
 * and return the 'distance' between the two vstring.
 * 
 * @param s1 the first vstring
 * @param s2 the second vstring
 * @return the lexicalographic distance [s1-s2]
 */
int vstrcmp ( vstring* s1 vstring* s2);

/**
 * Returns the length of the vstring.
 *
 * @param s the vstring 
 * @return the length of s  
 */
size_t vstrlen ( vstring* s );

#endif
