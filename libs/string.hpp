#ifndef __libs_string_hpp__
#define __libs_string_hpp__

#include "vector.hpp"

namespace libs
{
  template <typename char_t>
  using string = vector<char_t>;

  template <typename char_t>
  bool starts_with(
      const string<char_t> &s,
      const string<char_t> &prefix);

  template <typename char_t>
  bool ends_with(
      const string<char_t> &s,
      const string<char_t> &suffix);

} // namespace libs

template <typename char_t>
bool libs::starts_with(
    const libs::string<char_t> &s,
    const libs::string<char_t> &prefix)
{
  if (libs::size(s) < libs::size(prefix))
    return false;
  else
  {
    libs::index_t i = 0;

    while (libs::get(s, i) == libs::get(prefix, i))
      i++;

    return i == libs::size(prefix);
  }
}

template <typename char_t>
bool libs::ends_with(
    const libs::string<char_t> &s,
    const libs::string<char_t> &suffix)
{

  if (libs::size(s) < libs::size(suffix))
    return false;
  else
  {
    libs::index_t i = libs::size(s) - libs::size(suffix);

    while (libs::get(s, i) == libs::get(suffix, i - libs::size(suffix)))
      i++;

    return i == libs::size(s);
  }
}

#endif