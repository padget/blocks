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
    none(
        iterator_t b,
        iterator_t e,
        predicate_t pred);

    template <
        typename iterator_t,
        typename target_t>
    target_t &
    initialize(
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
size_t
count(
    iterator_t b,
    iterator_t e,
    predicate_t p)
{
    size_t count = 0;

    while (not equals(
        b = libs::find(b, e), e))
        count += 1;

    return count;
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
bool libs::none(
    iterator_t b,
    iterator_t e,
    predicate_t p)
{
    return equals(
        libs::find(b, e, p), e);
}

template <
    typename iterator_t,
    typename target_t>
target_t &
libs::initialize(
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