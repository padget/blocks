#ifndef __blocks_algorithm_hpp__
#define __blocks_algorithm_hpp__


namespace libs
{
    template <
        typename iterator_t,
        typename predicate_t>
    bool all(
        iterator_t b,
        iterator_t e,
        predicate_t pred);
} // namespace libs

template <
    typename iterator_t,
    typename predicate_t>
bool libs::all(
    iterator_t b,
    iterator_t e,
    predicate_t p)
{
    while (not libs::equals(b, e))
    {
        if (not p(libs::get(b)))
            return false;
        else
            libs::next(b);
    }

    return true;
}

#endif