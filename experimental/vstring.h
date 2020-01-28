#ifndef __experimental_vstring_h__
# define __experimental_vstring_h__

#include <stdlib.h>

/**
 * A vstring is a string view
 * It represents simply a iterating
 * view on a portion of an existing 
 * string.
 */
typedef struct vstring
{
  char* bstr;
  char* estr;
} vstring;

typedef void(vs_foreach_fn) (char* c);

/**
 *  Execute a function on each element
 *  contained in the vstring.
 *
 *  @param vs the vstring to iterate
 *  @param fn the function to apply on 
 *  each element of vs.
 */
void vs_foreach(vstring vs, vs_foreach_fn fn);

/**
 *  Build default vstring with
 *  bstr and estr at NULL;
 *
 *  @return the default built vstring.
 */
vstring vs_default();

/**
 * Constructs a vstring with begin as bstr
 * and end as estr.
 */
vstring vs_construct(char* begin, char* end);

/**
 * Returns the size of a vstring
 * 
 * @param vs vstring to have the size
 * @return the size of vs
 */
size_t vs_size(const vstring vs);

/**
 * A cvstring represents a constant
 * view on a portion of an existing
 * string.
 */ 
typedef struct cvstring
{
  const char* bstr;
  const char* estr;
} cvstring;

typedef void(cvs_foreach_fn) (const char* c);

/**
 *  Execute a function on each element
 *  contained in the vstring.
 *
 *  @param vs the vstring to iterate
 *  @param fn the function to apply on 
 *  each element of vs.
 */
void cvs_foreach(cvstring vs, cvs_foreach_fn fn);

/**
 *  Build default vstring with
 *  bstr and estr at NULL;
 *
 *  @return the default built vstring.
 */
cvstring cvs_default();

/**
 * Constructs a vstring with begin as bstr
 * and end as estr.
 */
cvstring cvs_construct(const char* begin, 
                       const char* end);

/**
 * Returns the size of a vstring
 * 
 * @param vs vstring to have the size
 * @return the size of vs
 */
size_t cvs_size(const cvstring vs);



#endif
