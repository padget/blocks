#ifndef __blocks_algorithm_hpp__
#define __blocks_algorithm_hpp__

#include "types.hpp"

namespace libs
{
  template <
      typename iterator_t,
      typename predicate_t>
  iterator_t
  find(
      iterator_t b,
      iterator_t e,
      predicate_t pred);

  template <
      typename iterator_t,
      typename predicate_t>
  iterator_t
  find_not(
      iterator_t b,
      iterator_t e,
      predicate_t pred);

  template <
      typename iterator_t,
      typename predicate_t>
  size_t
  count(
      iterator_t b,
      iterator_t e,
      predicate_t p);

  template <
      typename iterator_t,
      typename predicate_t>
  size_t
  offset(
      iterator_t b,
      iterator_t e,
      predicate_t p);

  template <
      typename iterator_t,
      typename predicate_t>
  bool
  all(
      iterator_t b,
      iterator_t e,
      predicate_t pred);

  template <
      typename iterator_t,
      typename predicate_t>
  bool
  any(
      iterator_t b,
      iterator_t e,
      predicate_t pred);

  template <
      typename iterator_t,
      typename predicate_t>
  bool
  between(
      iterator_t b,
      iterator_t e,
      predicate_t pred,
      size_t min,
      size_t max);

  template <
      typename iterator_t,
      typename predicate_t>
  bool
  times(
      iterator_t b,
      iterator_t e,
      predicate_t pred,
      size_t nb);

  template <
      typename iterator_t,
      typename predicate_t>
  bool
  none(
      iterator_t b,
      iterator_t e,
      predicate_t pred);

  template <
      typename iterator_t,
      typename predicate_t>
  bool
  one(
      iterator_t b,
      iterator_t e,
      predicate_t pred);

  template <
      typename iterator_t,
      typename predicate_t>
  bool
  more(
      iterator_t b,
      iterator_t e,
      predicate_t pred);

  template <
      typename iterator_t,
      typename target_t>
  target_t &
  pushall(
      iterator_t b,
      iterator_t e,
      target_t &target);

  template <
      typename iterator_t,
      typename action_t>
  void foreach (
      iterator_t b,
      iterator_t e,
      action_t action);

} // namespace libs

template <
    typename iterator_t,
    typename predicate_t>
iterator_t libs::find(
    iterator_t b,
    iterator_t e,
    predicate_t p)
{
  while (not equals(b, e))
    if (not p(get(b)))
      b = next(b);
    else
      break;
  return b;
}

template <
    typename iterator_t,
    typename predicate_t>
iterator_t libs::find_not(
    iterator_t b,
    iterator_t e,
    predicate_t p)
{
  while (not equals(b, e))
    if (p(get(b)))
      b = next(b);
    else
      break;
  return b;
}

template <
    typename iterator_t,
    typename predicate_t>
libs::size_t
libs::count(
    iterator_t b,
    iterator_t e,
    predicate_t p)
{
  libs::size_t count = 0;

  while (not equals(
      b = libs::find(b, e, p), e))
    count += 1;

  return count;
}

template <
    typename iterator_t,
    typename predicate_t>
libs::size_t
libs::offset(
    iterator_t b,
    iterator_t e,
    predicate_t p)
{
  libs::size_t offs = 0;

  while (not equals(b, e))
  {
    if (p(get(b)))
    {
      offs += 1;
      b = next(b);
    }
    else
      break;
  }

  return offs;
}

template <
    typename iterator_t,
    typename predicate_t>
bool libs::all(
    iterator_t b,
    iterator_t e,
    predicate_t p)
{
  return equals(
      libs::find_not(b, e, p), e);

  return true;
}

template <
    typename iterator_t,
    typename predicate_t>
bool libs::any(
    iterator_t b,
    iterator_t e,
    predicate_t p)
{
  return not equals(
      libs::find(b, e, p), e);
}

template <
    typename iterator_t,
    typename predicate_t>
bool between(
    iterator_t b,
    iterator_t e,
    predicate_t pred,
    size_t min,
    size_t max)
{
  size_t tms = 0;

  while (not equals(b, e))
  {
    if (pred(get(b)))
      tms += 1;

    if (tms > max)
      break;
  }

  return min <= tms and tms <= max;
}

template <
    typename iterator_t,
    typename predicate_t>
bool libs::times(
    iterator_t b,
    iterator_t e,
    predicate_t pred,
    size_t nb)
{
  return libs::between(
      b, e, pred, nb, nb);
}

template <
    typename iterator_t,
    typename predicate_t>
bool libs::none(
    iterator_t b,
    iterator_t e,
    predicate_t p)
{
  return libs::times(
      b, e, p, 0);
}

template <
    typename iterator_t,
    typename predicate_t>
bool one(
    iterator_t b,
    iterator_t e,
    predicate_t pred)
{

  return libs::times(
      b, e, pred, 1);
}

template <
    typename iterator_t,
    typename predicate_t>
bool libs::more(
    iterator_t b,
    iterator_t e,
    predicate_t pred)
{
  return between(
      b, e, pred, 2,
      libs::limitmax<libs::size_t>);
}

template <
    typename iterator_t,
    typename target_t>
target_t &
libs::pushall(
    iterator_t b,
    iterator_t e,
    target_t &target)
{
  while (not equals(b, e))
  {
    push(target, get(b));
    b = next(b);
  }

  return target;
}

template <
    typename iterator_t,
    typename action_t>
void libs::foreach (
    iterator_t b,
    iterator_t e,
    action_t action)
{
  while (not equals(b, e))
  {
    action(get(b));
    b = next(b);
  }
}
#endif