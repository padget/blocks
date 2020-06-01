#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include "algorithm.h"
#include "keyword.h"

iterator iter_new(void *item, size_t tsize)
{
  return (iterator){
      .item = item,
      .tsize = tsize};
}

iterator iter_next(iterator i)
{
  int8_t *ptr = i.item;
  int8_t *nptr = ptr + i.tsize;
  return iter_new(nptr, i.tsize);
}

size_t iter_distance(iterator i1, iterator i2)
{
  int8_t *item1 = i1.item;
  int8_t *item2 = i2.item;
  size_t dist = (item2 - item1) / i1.tsize;
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
  pred.simple = false;
  pred.ppred.apply = apply;
  pred.ppred.params = params;
  return pred;
}

gpred make_simple_predicate(
    bool (*apply)(iterator i))
{
  gpred pred;
  pred.simple = true;
  pred.spred.apply = apply;
  return pred;
}

private
iterator __find_if_simple_predicate(
    iterator b, iterator e,
    simple_predicate pred)
{
  while (not iter_same(b, e) and not pred.apply(b))
    b = iter_next(b);

  return b;
}

private
iterator __find_if_params_predicate(
    iterator b, iterator e,
    params_predicate pred)
{
  while (not iter_same(b, e) and not pred.apply(b, pred.params))
    b = iter_next(b);

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
    b = iter_next(b);

  return b;
}

private
iterator __find_if_not_params_predicate(
    iterator b, iterator e,
    params_predicate pred)
{
  while (not iter_same(b, e) and pred.apply(b, pred.params))
    b = iter_next(b);

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
  size_t c = 0;

  while (not iter_same(b, e))
  {
    if (pred.apply(b))
      inc c;
    b = iter_next(b);
  }

  return c;
}

private
size_t __count_if_params_predicate(
    iterator b, iterator e,
    params_predicate pred)
{
  size_t c = 0;

  while (not iter_same(b, e))
  {
    if (pred.apply(b, pred.params))
      inc c;
    b = iter_next(b);
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
  int8_t *litem = l.item;
  int8_t *ritem = r.item;

  int8_t *lend = litem + l.tsize;

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
    b = iter_next(b);
    b2 = iter_next(b2);
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
    b = iter_next(b);
    b2 = iter_next(b2);
  }

  return iter_same(b, e) and
         iter_same(b2, e2);
}
