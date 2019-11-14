#ifndef __blocks_stdf_hpp__
#define __blocks_stdf_hpp__

namespace blocks {
template<typename iterator>
void
next(iterator& it)
{
  it++;
}

template<typename type_t>
void
set(type_t& target, const type_t& source)
{
  target = source;
}

template<typename container, typename func>
void foreach (container&& c, func && f)
{
  for (auto&& i : c)
    f(i);
}
}

#endif