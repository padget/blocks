#ifndef __libs_string_hpp__
#define __libs_string_hpp__

#include "array.hpp"
#include <iostream>

namespace libs
{
  template <typename char_t>
  using basic_string = array<char_t>;

  using string = basic_string<char>;

  template <typename char_t, size_t size>
  basic_string<char_t>
  nullterm(const char_t (&cs)[size]);

  template <typename char_t>
  bool starts_with(
      const basic_string<char_t> &s,
      const basic_string<char_t> &prefix);

  template <typename char_t>
  bool ends_with(
      const basic_string<char_t> &s,
      const basic_string<char_t> &suffix);

} // namespace libs

#include <iostream>

template <typename char_t, size_t size>
libs::basic_string<char_t>
libs::nullterm(const char_t (&cs)[size])
{
  if (size >= 1)
    return libs::basic_string<char_t>(cs, size - 1);
  else
    return libs::basic_string<char_t>();
}

template <typename char_t>
bool libs::starts_with(
    const libs::basic_string<char_t> &s,
    const libs::basic_string<char_t> &prefix)
{
  std::cout << libs::size(s) << '\n';
  std::cout << libs::size(prefix) << '\n';

  if (libs::size(s) < libs::size(prefix))
    return false;
  else
  {
    auto sit = libs::begin(s);
    auto send = libs::end(s);
    auto pit = libs::begin(prefix);
    auto pend = libs::end(prefix);

    while (not libs::equals(pit, pend))
    {
      const char_t &cs = libs::get(sit);
      const char_t &cp = libs::get(pit);

      if (cs == cp)
      {
        sit = libs::next(sit);
        pit = libs::next(pit);
      }
      else
        break;
    }

    return libs::equals(pit, pend);
  }
}

template <typename char_t>
bool libs::ends_with(
    const libs::basic_string<char_t> &s,
    const libs::basic_string<char_t> &suffix)
{

  if (libs::size(s) < libs::size(suffix))
    return false;
  else
  {
    auto srit = libs::rbegin(s);
    auto sufrit = libs::rbegin(suffix);
    auto srend = libs::rend(s);
    auto sufrend = libs::rend(suffix);

    while (not equals(sufrit, sufrend))
    {
      const char_t &cs = libs::get(srit);
      const char_t &csuf = libs::get(sufrit);

      if (cs == csuf)
      {
        srit = libs::pred(srit);
        sufrit = libs::pred(sufrit);
      }
      else
        break;
    }

    return libs::equals(sufrit, sufrend);
  }
}

#endif