#ifndef __libs_intrange_hpp__
#define __libs_intrange_hpp__

namespace libs
{
  template <typename literal_t>
  struct range_iterator
  {
    literal_t value;
    literal_t max;

    literal_t &
    operator*();

    bool operator==(
        const range_iterator &);

    bool operator!=(
        const range_iterator &);

    range_iterator<literal_t> &
    operator++();
  };

  template <typename literal_t>
  struct range_sequence
  {
    literal_t min;
    literal_t max;

    range_iterator<literal_t>
    begin();

    range_iterator<literal_t>
    end();
  };

  template <typename literal_t>
  range_sequence<literal_t>
  range(
      literal_t min,
      literal_t max);
} // namespace libs

template <typename literal_t>
literal_t &
libs::range_iterator<literal_t>::operator*()
{
  return value;
}

template <typename literal_t>
bool libs::range_iterator<literal_t>::operator!=(
    const libs::range_iterator<literal_t> &o)
{
  return o.max == max and o.value != value;
}

template <typename literal_t>
bool libs::range_iterator<literal_t>::operator==(
    const libs::range_iterator<literal_t> &o)
{
  return o.max == max and o.value == value;
}

template <typename literal_t>
libs::range_iterator<literal_t> &
libs::range_iterator<literal_t>::operator++()
{
  value++;
  return *this;
}

template <typename literal_t>
libs::range_iterator<literal_t>
libs::range_sequence<literal_t>::begin()
{
  return range_iterator<literal_t>{min, max};
}

template <typename literal_t>
libs::range_iterator<literal_t>
libs::range_sequence<literal_t>::end()
{
  return range_iterator<literal_t>{max, max};
}

template <typename literal_t>
libs::range_sequence<literal_t>
libs::range(
    literal_t min,
    literal_t max)
{
  return range_sequence<literal_t>{min, max};
}

#endif