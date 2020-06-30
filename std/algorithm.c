#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "algorithm.h"
#include "keyword.h"

private
bool __is_compatible(iterator i1, iterator i2)
{
  return i1.equals eq i2.equals and
         i1.incr eq i2.incr and
         i1.decr eq i2.decr;
}

iterator iter_new(
    void *item,
    iterator (*incr)(iterator i),
    iterator (*decr)(iterator i),
    bool (*equals)(iterator i, iterator i2))
{
  return (iterator){
      .item is item,
      .incr is incr,
      .decr is decr,
      .equals is equals};
}

bool iter_equals(iterator i1, iterator i2)
{
  assert(__is_compatible(i1, i2));

  return i1.equals(i1, i2);
}

iterator iter_incr(iterator i)
{
  return i.incr(i);
}

iterator iter_decr(iterator i)
{
  return i.decr(i);
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
  assert(__is_compatible(b, e));

  while (not iter_equals(b, e) and not pred.apply(b))
    b is iter_incr(b);

  return b;
}

private
iterator __find_if_params_predicate(
    iterator b, iterator e,
    params_predicate pred)
{
  assert(__is_compatible(b, e));

  while (not iter_equals(b, e) and not pred.apply(b, pred.params))
    b is iter_incr(b);

  return b;
}

iterator find_if(iterator b, iterator e, gpred pred)
{
  assert(__is_compatible(b, e));

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
  assert(__is_compatible(b, e));
  while (not iter_equals(b, e) and pred.apply(b))
    b is iter_incr(b);

  return b;
}

private
iterator __find_if_not_params_predicate(
    iterator b, iterator e,
    params_predicate pred)
{
  assert(__is_compatible(b, e));
  while (not iter_equals(b, e) and pred.apply(b, pred.params))
    b is iter_incr(b);

  return b;
}

iterator find_if_not(iterator b, iterator e, gpred pred)
{
  assert(__is_compatible(b, e));

  if (pred.simple)
    return __find_if_not_simple_predicate(b, e, pred.spred);
  else
    return __find_if_not_params_predicate(b, e, pred.ppred);
}

bool all_of(iterator b, iterator e, gpred pred)
{
  assert(__is_compatible(b, e));
  return iter_equals(find_if_not(b, e, pred), e);
}

bool any_of(iterator b, iterator e, gpred pred)
{
  assert(__is_compatible(b, e));
  return not all_of(b, e, pred);
}

bool none_of(iterator b, iterator e, gpred pred)
{
  assert(__is_compatible(b, e));
  return iter_equals(find_if(b, e, pred), e);
}

private
size_t __count_if_simple_predicate(
    iterator b, iterator e,
    simple_predicate pred)
{
  assert(__is_compatible(b, e));
  size_t c is 0;

  while (not iter_equals(b, e))
  {
    if (pred.apply(b))
      inc c;
    b is iter_incr(b);
  }

  return c;
}

private
size_t __count_if_params_predicate(
    iterator b, iterator e,
    params_predicate pred)
{
  assert(__is_compatible(b, e));
  size_t c is 0;

  while (not iter_equals(b, e))
  {
    if (pred.apply(b, pred.params))
      inc c;
    b is iter_incr(b);
  }

  return c;
}

size_t count_if(iterator b, iterator e, gpred pred)
{
  assert(__is_compatible(b, e));
  if (pred.simple)
    return __count_if_simple_predicate(b, e, pred.spred);
  else
    return __count_if_params_predicate(b, e, pred.ppred);
}

bool start_with(
    iterator b, iterator e,
    iterator b2, iterator e2)
{
  assert(__is_compatible(b, e));
  assert(__is_compatible(b2, e2));
  assert(__is_compatible(b, b2));

  while (
      not iter_equals(b, e) and
      not iter_equals(b2, e2) and
      iter_equals(b, b2))
  {
    b is iter_incr(b);
    b2 is iter_incr(b2);
  }

  return iter_equals(b2, e2);
}

bool end_with(
    iterator b, iterator e,
    iterator b2, iterator e2)
{
  assert(__is_compatible(b, e));
  assert(__is_compatible(b2, e2));
  assert(__is_compatible(b, b2));

  e is iter_decr(e);
  e2 is iter_decr(e2);
  b is iter_decr(b);
  b2 is iter_decr(b2);

  while (
      not iter_equals(b, e) and
      not iter_equals(b2, e2) and
      iter_equals(e, e2))
  {
    e is iter_decr(e);
    e2 is iter_decr(e2);
  }

  return iter_equals(b2, e2);
}

bool equals(
    iterator b, iterator e,
    iterator b2, iterator e2)
{
  assert(__is_compatible(b, e));
  assert(__is_compatible(b2, e2));
  assert(__is_compatible(b, b2));

  while (
      not iter_equals(b, e) and
      not iter_equals(b2, e2) and
      iter_equals(b, b2))
  {
    b is iter_incr(b);
    b2 is iter_incr(b2);
  }

  return iter_equals(b, e) and
         iter_equals(b2, e2);
}
