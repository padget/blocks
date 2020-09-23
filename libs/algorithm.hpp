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

} // namespace libs

template <
    typename iterator_t,
    typename predicate_t>
iterator_t libs::find(
    iterator_t b,
    iterator_t e,
    predicate_t p)
{
    while (not libs::equals(b, e))
        if (not p(libs::get(b)))
            b = libs::next(b);
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
    while (not libs::equals(b, e))
        if (p(libs::get(b)))
            b = libs::next(b);
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

    while (not libs::equals(
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
    return libs::equals(
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
    return not libs::equals(
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
    return libs::equals(
        libs::find(b, e, p), e);
}

#endif