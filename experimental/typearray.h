#ifndef __blocks_typearray_h__
#define __blocks_typearray_h__

#include "typeref.h"

#define typearray(type)                                                                   \
  struct type##array                                                                      \
  {                                                                                       \
    type *data;                                                                           \
    size_t len;                                                                           \
  };                                                                                      \
                                                                                          \
  typedef struct type##array type##array;                                                 \
                                                                                          \
  type##ref type##a_begin(type##array arr);                                               \
  type##ref type##a_end(type##array arr);                                                 \
  type##ref type##a_next(type##ref ref);                                                  \
  bool type##a_diff(type##ref ref, type##ref ref2);                                       \
                                                                                          \
  type##ref type##a_at(type##array arr, size_t i);                                        \
  bool type##a_empty(type##array arr);                                                    \
  size_t type##a_len(type##array arr);                                                    \
                                                                                          \
  type##ref type##a_find_if(type##ref begin, type##ref end, bool (*pred)(type##ref));     \
  type##ref type##a_find_if_not(type##ref begin, type##ref end, bool (*pred)(type##ref)); \
  bool type##a_all_of(type##ref begin, type##ref end, bool (*pred)(type##ref));           \
  bool type##a_any_of(type##ref begin, type##ref end, bool (*pred)(type##ref));           \
  bool type##a_none_of(type##ref begin, type##ref end, bool (*pred)(type##ref));          \
                                                                                          \
  size_t type##a_count(type##ref begin, type##ref end, type##ref ref);                    \
  size_t type##a_count_if(type##ref begin, type##ref end, bool (*pred)(type##ref));

#define typearrayimpl(type)                                                        \
                                                                                   \
  type##ref type##a_begin(type##array arr)                                         \
  {                                                                                \
    type##ref ref;                                                                 \
    ref.value = arr.data;                                                          \
    return ref;                                                                    \
  }                                                                                \
                                                                                   \
  type##ref type##a_end(type##array arr)                                           \
  {                                                                                \
    type##ref ref;                                                                 \
    ref.value = arr.data + arr.len;                                                \
    return ref;                                                                    \
  }                                                                                \
                                                                                   \
  type##ref type##a_next(type##ref ref)                                            \
  {                                                                                \
    ref.value++;                                                                   \
    return ref;                                                                    \
  }                                                                                \
                                                                                   \
  bool type##a_diff(type##ref ref, type##ref ref2)                                 \
  {                                                                                \
    return ref.value != ref2.value;                                                \
  }                                                                                \
                                                                                   \
  type##ref type##a_at(type##array arr, size_t i)                                  \
  {                                                                                \
    type##ref ref;                                                                 \
                                                                                   \
    if (i >= arr.len)                                                              \
      ref.value = NULL;                                                            \
    else if (arr.data == NULL)                                                     \
      ref.value = NULL;                                                            \
    else                                                                           \
      ref.value = arr.data + i;                                                    \
                                                                                   \
    return ref;                                                                    \
  }                                                                                \
                                                                                   \
  bool type##a_empty(type##array arr)                                              \
  {                                                                                \
    return arr.data == NULL || arr.len == 0;                                       \
  }                                                                                \
                                                                                   \
  size_t type##a_len(type##array arr)                                              \
  {                                                                                \
    return arr.data == NULL ? 0 : arr.len;                                         \
  }                                                                                \
                                                                                   \
  type##ref type##a_find_if(                                                       \
      type##ref begin,                                                             \
      type##ref end,                                                               \
      bool (*pred)(type##ref))                                                     \
  {                                                                                \
    while (type##a_diff(begin, end) && !pred(begin))                               \
      begin = type##a_next(begin);                                                 \
                                                                                   \
    return begin;                                                                  \
  }                                                                                \
                                                                                   \
  type##ref type##afind_if_not(                                                    \
      type##ref begin,                                                             \
      type##ref end,                                                               \
      bool (*pred)(type##ref))                                                     \
  {                                                                                \
    while (type##a_diff(begin, end) && pred(begin))                                \
      begin = type##a_next(begin);                                                 \
                                                                                   \
    return begin;                                                                  \
  }                                                                                \
                                                                                   \
  bool type##aallof(                                                               \
      type##ref begin,                                                             \
      type##ref end,                                                               \
      bool (*pred)(type##ref))                                                     \
  {                                                                                \
    return !type##a_diff(type##afind_if_not(begin, end, pred), end);               \
  }                                                                                \
                                                                                   \
  bool type##a_any_of(type##ref begin, type##ref end, bool (*pred)(type##ref))     \
  {                                                                                \
    return type##a_diff(type##a_find_if_not(begin, end, pred), end);               \
  }                                                                                \
                                                                                   \
  bool type##a_none_of(type##ref begin, type##ref end, bool (*pred)(type##ref))    \
  {                                                                                \
    return !type##a_diff(type##a_find_if(begin, end, pred), end);                  \
  }                                                                                \
                                                                                   \
  size_t type##a_count(type##ref begin, type##ref end, type##ref ref)              \
  {                                                                                \
    size_t count = 0;                                                              \
    while (type##a_diff(begin, end))                                               \
    {                                                                              \
      if (!type##a_diff(begin, ref))                                               \
        count++;                                                                   \
                                                                                   \
      begin = type##a_next(begin);                                                 \
    }                                                                              \
    return count;                                                                  \
  }                                                                                \
                                                                                   \
  size_t type##a_count_if(type##ref begin, type##ref end, bool (*pred)(type##ref)) \
  {                                                                                \
    size_t count = 0;                                                              \
    while (type##a_diff(begin, end))                                               \
    {                                                                              \
      if (pred(begin))                                                             \
        count++;                                                                   \
                                                                                   \
      begin = type##a_next(begin);                                                 \
    }                                                                              \
    return count;                                                                  \
  }

#endif