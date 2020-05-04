#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "algorithm.h"
#include "keyword.h"

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

ivalue_equals make_ivalue_equals(
  bool(*apply)(iterator, iterator))
{
  ivalue_equals ive;
  ive.apply = apply;
  return ive;
}

private
iterator __find_if_simple_predicate(
    iterator b, iterator e,
    simple_predicate pred)
{
  while (not same(b, e) and not pred.apply(b))
    b = next(b);

  return b;
}

private
iterator __find_if_params_predicate(
    iterator b, iterator e,
    params_predicate pred)
{
  while (not same(b, e) and not pred.apply(b, pred.params))
    b = next(b);

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
  while (not same(b, e) and pred.apply(b))
    b = next(b);

  return b;
}

private
iterator __find_if_not_params_predicate(
    iterator b, iterator e,
    params_predicate pred)
{
  while (not same(b, e) and pred.apply(b, pred.params))
    b = next(b);

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

  return same(find_if_not(b, e, pred), e);
}

bool any_of(iterator b, iterator e, gpred pred)
{
  return not all_of(b, e, pred);
}

bool none_of(iterator b, iterator e, gpred pred)
{
  return same(find_if(b, e, pred), e);
}

private
size_t __count_if_simple_predicate(
    iterator b, iterator e,
    simple_predicate pred)
{
  size_t c = 0;

  while (not same(b, e))
  {
    if (pred.apply(b))
      c++;
    b = next(b);
  }

  return c;
}

private
size_t __count_if_params_predicate(
    iterator b, iterator e,
    params_predicate pred)
{
  size_t c = 0;

  while (not same(b, e))
  {
    if (pred.apply(b, pred.params))
      c++;
    b = next(b);
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

bool start_with(
    iterator b, iterator e,
    iterator b2, iterator e2,
    iterator_value_equals sequals)
{
  while (
      not same(b, e) and
      not same(b2, e2) and
      sequals.apply(b, b2))
  {
    b = next(b);
    b2 = next(b2);
  }

  return same(b2, e2);
}

bool equals(
    iterator b, iterator e,
    iterator b2, iterator e2,
    iterator_value_equals sequals)
{
  while (
      not same(b, e) and
      not same(b2, e2) and
      sequals.apply(b, b2))
  {
    b = next(b);
    b2 = next(b2);
  }

  return same(b, e) and same(b2, e2);
}
