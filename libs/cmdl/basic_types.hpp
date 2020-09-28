#ifndef __cmdl_basic_types_hpp__
#define __cmdl_basic_types_hpp__

#include "../std.hpp"
#include "../algorithm.hpp"

namespace blocks::cmdl::specification
{
  template <typename type_t>
  bool str_convertible(const str_t &v);
}

namespace blocks::cmdl::specification
{
  template <>
  bool str_convertible<bool>(const str_t &v);
  str_t to_string(const bool &t);

  template <>
  bool str_convertible<int>(const str_t &v);
  str_t to_string(const int &t);

  template <>
  bool str_convertible<str_t>(const str_t &v);
  str_t to_string(const str_t &t);
} // namespace blocks::cmdl::specification

/// //////////////////////// ///
/// TEMPLATE IMPLEMENTATIONS ///
/// //////////////////////// ///

template <>
bool blocks::cmdl::specification::str_convertible<bool>(
    const blocks::str_t &v)
{
  return v == "true" or v == "false";
}

inline blocks::str_t
blocks::cmdl::specification::to_string(
    const bool &b)
{
  return b ? "true" : "false";
}

template <>
bool blocks::cmdl::specification::str_convertible<int>(
    const blocks::str_t &v)
{
  auto is_digit = [](const char c) {
    return '0' <= c and c <= '9';
  };

  return blocks::all(v.begin(), v.end(), is_digit);
}

inline blocks::str_t
blocks::cmdl::specification::to_string(
    const int &i)
{
  return std::to_string(i);
}

template <>
bool blocks::cmdl::specification::str_convertible<blocks::str_t>(
    const blocks::str_t &v)
{
  return true;
}

blocks::str_t
blocks::cmdl::specification::to_string(
    const blocks::str_t &s)
{
  return s;
}

#endif