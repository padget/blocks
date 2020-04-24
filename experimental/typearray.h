#ifndef __blocks_typearray_h__
#define __blocks_typearray_h__

#include "typeref.h"

#define typearray(type)                                         \
  struct type##array                                            \
  {                                                             \
    char *data;                                                 \
    size_t len;                                                 \
  };                                                            \
                                                                \
  typedef struct type##array type##array;                       \
                                                                \
  type##ref type##abegin(type##array arr);                      \
  type##ref type##aend(type##array arr);                        \
  type##ref type##anext(type##ref ref);                         \
  type##ref type##adiff(type##ref ref, type##ref ref2);         \
                                                                \
  type##ref type##aat(type##array arr, size_t i);               \
  bool type##aempty(type##array arr);                           \
  size_t type##alen(type##array arr);                           \
                                                                \
  bool type##aallof(type##array arr, bool (*pred)(type##ref));  \
  bool type##aanyof(type##array arr, bool (*pred)(type##ref));  \
  bool type##anoneof(type##array arr, bool (*pred)(type##ref)); \
                                                                \
  size_t type##acount(type##array arr, type##ref ref);          \
  size_t type##acountif(type##array arr, bool (*pred)(type##ref));

#define typearrayimpl(type)                                     \
                                                                \
  type##ref type##abegin(type##array arr)                       \
  {                                                             \
    return arr.data;                                            \
  }                                                             \
                                                                \
  type##ref type##aend(type##array arr)                         \
  {                                                             \
    return arr.data + arr.len;                                  \
  }                                                             \
                                                                \
  type##ref type##anext(type##ref ref)                          \
  {                                                             \
    ref.value++;                                                \
    return ref;                                                 \
  }                                                             \
                                                                \
  bool type##adiff(type##ref ref, type##ref ref2)               \
  {                                                             \
    return ref.value != ref2.value;                             \
  }                                                             \
                                                                \
  type##ref type##aat(type##array arr, size_t i)                \
  {                                                             \
    type##ref ref;                                              \
                                                                \
    if (i >= arr.len)                                           \
      ref.value = NULL;                                         \
    else if (arr.data == NULL)                                  \
      ref.value = NULL;                                         \
    else                                                        \
      ref.value = arr.data + i;                                 \
                                                                \
    return ref;                                                 \
  }                                                             \
                                                                \
  bool type##aempty(type##array arr)                            \
  {                                                             \
    return arr.data == NULL || arr.len == 0;                    \
  }                                                             \
                                                                \
  size_t type##alen(type##array *arr)                           \
  {                                                             \
    return arr == NULL ? 0 : arr->len;                          \
  }                                                             \
                                                                \
  bool type##aallof(type##array arr, bool (*pred)(type##ref));  \
  {                                                             \
    if (type##aempty(arr))                                      \
      return false;                                             \
                                                                \
    bool res = true;                                            \
    type##ref begin = type##abegin(arr);                        \
    type##ref end = type##aend(arr);                            \
                                                                \
    while (res && type##adiff(begin, end))                      \
    {                                                           \
      res = res && pred(begin);                                 \
      type##anext(begin);                                       \
    }                                                           \
                                                                \
    return res;                                                 \
  }                                                             \
                                                                \
  bool type##aanyof(type##array *arr, bool (*pred)(type##ref))  \
  {                                                             \
    if (type##aempty(arr))                                      \
      return false;                                             \
                                                                \
    bool res = false;                                           \
    type##ref begin = type##abegin(arr);                        \
    type##ref end = type##aend(arr);                            \
                                                                \
    while (!res && type##adiff(begin, end))                     \
    {                                                           \
      res = res || pred(begin);                                 \
      type##anext(begin);                                       \
    }                                                           \
                                                                \
    return res;                                                 \
  }                                                             \
                                                                \
  bool type##anoneof(type##array *arr, bool (*pred)(type##ref)) \
  {                                                             \
    if (type##aempty(arr))                                      \
      return false;                                             \
                                                                \
    bool res = false;                                           \
    type##ref begin = type##abegin(arr);                        \
    type##ref end = type##aend(arr);                            \
                                                                \
    while (!res && type##adiff(begin, end))                     \
    {                                                           \
      res = res || pred(begin);                                 \
      type##anext(begin);                                       \
    }                                                           \
                                                                \
    return res;                                                 \
  }                                                             \
                                                                \
  size_t type##acount(type##array *arr, type##ref ref);         \
                                                                \
  size_t type##acountif(type##array *arr, bool (*pred)(type##ref));

#endif