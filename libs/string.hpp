#ifndef __libs_string_hpp__
#define __libs_string_hpp__

#include "array.hpp"
#include "algorithm.hpp"

namespace libs
{

  template <typename char_t>
  struct basic_string_iterator
  {
    array_iterator<char_t> it;
  };

  template <typename char_t>
  struct basic_string
  {
    array<char_t> data;

  public:
    basic_string() = default;
    template <typename iterator_t>
    basic_string(
        iterator_t b,
        iterator_t e);
    basic_string(const char_t *data);
    basic_string(const basic_string &) = default;
    basic_string(basic_string &&) = default;
    ~basic_string() = default;

    basic_string &operator=(const basic_string &) = delete;
    basic_string &operator=(basic_string &&) = default;
  };

  using string = basic_string<char>;
  using wstring = basic_string<wchar_t>;

  // Size getter
  template <typename type_t>
  size_t size(const basic_string<type_t> &v);

  // Setter by move
  template <typename type_t>
  void push(
      basic_string<type_t> &v,
      type_t &&t);

  // Setter by copie
  template <typename type_t>
  void push(
      basic_string<type_t> &v,
      const type_t &t);

  template <typename type_t>
  basic_string_iterator<type_t>
  begin(basic_string<type_t> &v);

  template <typename type_t>
  basic_string_iterator<type_t>
  end(basic_string<type_t> &v);

  template <typename type_t>
  basic_string_iterator<const type_t>
  begin(const basic_string<type_t> &v);

  template <typename type_t>
  basic_string_iterator<const type_t>
  end(const basic_string<type_t> &v);

  template <typename type_t>
  basic_string_iterator<type_t>
  rbegin(basic_string<type_t> &v);

  template <typename type_t>
  basic_string_iterator<type_t>
  rend(basic_string<type_t> &v);

  template <typename type_t>
  basic_string_iterator<const type_t>
  rbegin(const basic_string<type_t> &v);

  template <typename type_t>
  basic_string_iterator<const type_t>
  rend(const basic_string<type_t> &v);

  template <typename type_t>
  type_t &get(
      basic_string_iterator<type_t> it);

  template <typename type_t>
  const type_t &get(
      basic_string_iterator<const type_t> it);

  template <typename type_t>
  basic_string_iterator<type_t>
  next(basic_string_iterator<type_t> it);

  template <typename type_t>
  basic_string_iterator<type_t>
  pred(basic_string_iterator<type_t> it);

  template <typename type_t>
  bool equals(
      basic_string_iterator<type_t> l,
      basic_string_iterator<type_t> r);

  template <typename type_t>
  size_t distance(
      basic_string_iterator<type_t> l,
      basic_string_iterator<type_t> r);

  template <typename char_t>
  bool starts_with(
      const basic_string<char_t> &s,
      const basic_string<char_t> &prefix);

  template <typename char_t>
  bool ends_with(
      const basic_string<char_t> &s,
      const basic_string<char_t> &suffix);

  template <typename char_t>
  bool content_equals(
      const basic_string<char_t> &l,
      const basic_string<char_t> &r);

  template <typename char_t>
  list<basic_string<char_t>>
  split(
      const basic_string<char_t> &str,
      char_t separator,
      size_t limits);

  template <typename char_t>
  list<basic_string<char_t>>
  split(
      const basic_string<char_t> &str,
      char_t separator);
} // namespace libs

namespace libs::internal
{
  template <typename char_t>
  size_t
  cstr_length(const char_t *cstr);
} // namespace libs::internal

template <typename char_t>
libs::basic_string<char_t>::basic_string(
    const char_t *v)
    : data(v, libs::internal::cstr_length(v))
{
}

template <typename char_t>
template <typename iterator_t>
libs::basic_string<char_t>::basic_string(
    iterator_t b,
    iterator_t e)
    : data(b, e)
{
}

template <typename type_t>
libs::size_t libs::size(
    const libs::basic_string<type_t> &v)
{
  return libs::size(v.data);
}

// Setter by move
template <typename type_t>
void libs::push(
    libs::basic_string<type_t> &v,
    type_t &&t)
{
  libs::push(v, t);
}

// Setter by copie
template <typename type_t>
void libs::push(
    libs::basic_string<type_t> &v,
    const type_t &t)
{
  libs::push(v, t);
}

template <typename type_t>
libs::basic_string_iterator<type_t>
libs::begin(
    libs::basic_string<type_t> &v)
{
  return {libs::begin(v.data)};
}

template <typename type_t>
libs::basic_string_iterator<type_t>
libs::end(
    libs::basic_string<type_t> &v)
{
  return {libs::end(v.data)};
}

template <typename type_t>
libs::basic_string_iterator<const type_t>
libs::begin(
    const libs::basic_string<type_t> &v)
{
  return {libs::begin(v.data)};
}

template <typename type_t>
libs::basic_string_iterator<const type_t>
libs::end(
    const libs::basic_string<type_t> &v)
{
  return {libs::end(v.data)};
}

template <typename type_t>
libs::basic_string_iterator<type_t>
libs::rbegin(
    libs::basic_string<type_t> &v)
{
  return {libs::rbegin(v.data)};
}

template <typename type_t>
libs::basic_string_iterator<type_t>
libs::rend(
    libs::basic_string<type_t> &v)
{
  return {libs::rend(v.data)};
}

template <typename type_t>
libs::basic_string_iterator<const type_t>
libs::rbegin(
    const libs::basic_string<type_t> &v)
{
  return {libs::rbegin(v.data)};
}

template <typename type_t>
libs::basic_string_iterator<const type_t>
libs::rend(
    const libs::basic_string<type_t> &v)
{
  return {libs::rend(v.it)};
}

template <typename type_t>
type_t &libs::get(
    libs::basic_string_iterator<type_t> it)
{
  return libs::get(it.it);
}

template <typename type_t>
const type_t &libs::get(
    libs::basic_string_iterator<const type_t> it)
{
  return libs::get(it.it);
}

template <typename type_t>
libs::basic_string_iterator<type_t>
libs::next(
    libs::basic_string_iterator<type_t> it)
{
  return {libs::next(it.it)};
}

template <typename type_t>
libs::basic_string_iterator<type_t>
libs::pred(
    libs::basic_string_iterator<type_t> it)
{
  return {libs::pred(it.it)};
}

template <typename type_t>
bool libs::equals(
    libs::basic_string_iterator<type_t> l,
    libs::basic_string_iterator<type_t> r)
{
  return libs::equals(l.it, r.it);
}

template <typename type_t>
libs::size_t
libs::distance(
    libs::basic_string_iterator<type_t> l,
    libs::basic_string_iterator<type_t> r)
{
  return libs::distance(l.it, r.it);
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

template <typename char_t>
bool libs::content_equals(
    const basic_string<char_t> &l,
    const basic_string<char_t> &r)
{
  return libs::size(l) == libs::size(r) and
         libs::starts_with(l, r);
}

template <typename char_t>
libs::size_t
libs::internal::cstr_length(
    const char_t *cstr)
{
  const char_t *initial = cstr;

  if (cstr != nullptr)
    while (*cstr != '\0')
      cstr++;

  return cstr - initial;
}

template <typename char_t>
libs::list<libs::basic_string<char_t>>
libs::split(
    const libs::basic_string<char_t> &str,
    char_t separator,
    libs::size_t limits)
{
  libs::list<libs::basic_string<char_t>> res;

  if (limits == 0)
    return res;

  auto b = libs::begin(str);
  auto fe = libs::end(str);

  auto same = [separator](char_t c) { return c == separator; };

  while (not libs::equals(b, fe) and libs::size(res) < limits)
  {
    auto e = libs::find(b, fe, same);
    libs::push(res, libs::basic_string<char_t>(b, e));

    if (not libs::equals(e, fe))
      b = libs::next(e);
    else
      b = e;
  }

  return res;
}

template <typename char_t>
libs::list<libs::basic_string<char_t>>
libs::split(
    const libs::basic_string<char_t> &str,
    char_t separator)
{
  return libs::split(
      str, separator,
      libs::limitmax<libs::size_t>());
}

#endif