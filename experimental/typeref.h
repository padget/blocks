#ifndef __blocks_typeref_h__
#define __blocks_typeref_h__

#define typeref(type) \
                      \
  struct type##ref    \
  {                   \
    type *value;      \
  };                  \
                      \
  typedef struct type##ref type##ref;

#endif