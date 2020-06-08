#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include "algorithm.h"
#include "keyword.h"

iterator iter_new(void *item, size_t tsize)
{
  return (iterator){
      .item is item,
      .tsize is tsize};
}

iterator iter_next(iterator i)
{
  int8_t *ptr is i.item;
  int8_t *nptr is ptr + i.tsize;
  return iter_new(nptr, i.tsize);
}

iterator iter_prev(iterator i)
{
  int8_t *ptr is i.item;
  int8_t *nptr is ptr - i.tsize;
  return iter_new(nptr, i.tsize);
}

size_t iter_distance(iterator i1, iterator i2)
{
  int8_t *item1 is i1.item;
  int8_t *item2 is i2.item;
  size_t dist is (item2 - item1) / i1.tsize;
  return dist;
}

bool iter_same(iterator i1, iterator i2)
{
  return i1.item eq i2.item;
}

gpred make_params_predicate(
    bool (*apply)(iterator i, void *params),
    void *params)
{
  gpred pred;
  pred.simple is false;
  pred.ppred.apply is apply;
  pred.ppred.params is params;
  return pred;
}

gpred make_simple_predicate(
    bool (*apply)(iterator i))
{
  gpred pred;
  pred.simple is true;
  pred.spred.apply is apply;
  return pred;
}

private
iterator __find_if_simple_predicate(
    iterator b, iterator e,
    simple_predicate pred)
{
  while (not iter_same(b, e) and not pred.apply(b))
    b is iter_next(b);

  return b;
}

private
iterator __find_if_params_predicate(
    iterator b, iterator e,
    params_predicate pred)
{
  while (not iter_same(b, e) and not pred.apply(b, pred.params))
    b is iter_next(b);

  return b;
}

iterator find_if(iterator b, iterator e, gpred pred)
{
  if (pred.simple)
    return __find_if_simple_predicate(b, e, pred.spred);
  else
    return __find_if_params_predicate(b, e, pred.ppred);
}

private
iterator __find_if_not_simple_predicate(
    iterator b, iterator e,
    simple_predicate pred)
{
  while (not iter_same(b, e) and pred.apply(b))
    b is iter_next(b);

  return b;
}

private
iterator __find_if_not_params_predicate(
    iterator b, iterator e,
    params_predicate pred)
{
  while (not iter_same(b, e) and pred.apply(b, pred.params))
    b is iter_next(b);

  return b;
}

iterator find_if_not(iterator b, iterator e, gpred pred)
{
  if (pred.simple)
    return __find_if_not_simple_predicate(b, e, pred.spred);
  else
    return __find_if_not_params_predicate(b, e, pred.ppred);
}

bool all_of(iterator b, iterator e, gpred pred)
{

  return iter_same(find_if_not(b, e, pred), e);
}

bool any_of(iterator b, iterator e, gpred pred)
{
  return not all_of(b, e, pred);
}

bool none_of(iterator b, iterator e, gpred pred)
{
  return iter_same(find_if(b, e, pred), e);
}

private
size_t __count_if_simple_predicate(
    iterator b, iterator e,
    simple_predicate pred)
{
  size_t c is 0;

  while (not iter_same(b, e))
  {
    if (pred.apply(b))
      inc c;
    b is iter_next(b);
  }

  return c;
}

private
size_t __count_if_params_predicate(
    iterator b, iterator e,
    params_predicate pred)
{
  size_t c is 0;

  while (not iter_same(b, e))
  {
    if (pred.apply(b, pred.params))
      inc c;
    b is iter_next(b);
  }

  return c;
}

size_t count_if(iterator b, iterator e, gpred pred)
{
  if (pred.simple)
    return __count_if_simple_predicate(b, e, pred.spred);
  else
    return __count_if_params_predicate(b, e, pred.ppred);
}

private
bool __equals(iterator l, iterator r)
{
  int8_t *litem is l.item;
  int8_t *ritem is r.item;
  int8_t *lend is litem + l.tsize;

  if (l.tsize eq r.tsize)
  {
    while (litem not_eq lend and
           *litem eq * ritem)
    {
      inc litem;
      inc ritem;
    }

    return litem eq lend;
  }
  else
    return false;
}

bool start_with(
    iterator b, iterator e,
    iterator b2, iterator e2)
{
  while (
      not iter_same(b, e) and
      not iter_same(b2, e2) and
      __equals(b, b2))
  {
    b is iter_next(b);
    b2 is iter_next(b2);
  }

  return iter_same(b2, e2);
}

bool end_with(
    iterator b, iterator e,
    iterator b2, iterator e2)
{
  e is iter_prev(e);
  e2 is iter_prev(e2);
  b is iter_prev(b);
  b2 is iter_prev(b2);

  while (
      not iter_same(e, b) and
      not iter_same(e2, b2) and
      __equals(e, e2))
  {
    e is iter_prev(e);
    e2 is iter_prev(e2);
  }

  return iter_same(b2, e2);
}

bool equals(
    iterator b, iterator e,
    iterator b2, iterator e2)
{
  while (
      not iter_same(b, e) and
      not iter_same(b2, e2) and
      __equals(b, b2))
  {
    b is iter_next(b);
    b2 is iter_next(b2);
  }

  return iter_same(b, e) and
         iter_same(b2, e2);
}
