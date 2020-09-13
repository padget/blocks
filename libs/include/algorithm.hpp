#ifndef __blocks_algorithm_hpp__
#define __blocks_algorithm_hpp__

namespace blocks
{
    template <typename iterator_t, typename predicate_t>
    bool all(iterator_t b, iterator_t e, predicate_t pred)
    {
        while (b != e and pred(*b))
            ++b;
        return b == e;
    }
} // namespace blocks

#endif