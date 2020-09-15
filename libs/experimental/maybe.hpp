#ifndef __libs_maybe_hpp__
#define __libs_maybe_hpp__

namespace libs::experimental
{
  struct empty_maybe
  {
  };

  template <
      typename type_t>
  struct maybe
  {
    union
    {
      type_t tp;
      empty_maybe em;
    };

    bool empty;

    maybe();
    maybe(const empty_maybe &e);
    maybe(const type_t &t);
    maybe(type_t &&t);
    maybe(const maybe &o) = default;
    maybe(maybe &&o) = default;
    ~maybe() = default;

    maybe &operator=(const maybe &) = default;
    maybe &operator=(maybe &&) = default;
  };

  template <typename type_t>
  bool empty(const maybe<type_t> &m);

  template <typename type_t>
  type_t &get(maybe<type_t> &m);

  template <typename type_t>
  const type_t &get(const maybe<type_t> &m);

  template <typename type_t>
  type_t &&get(maybe<type_t> &&m);
} // namespace libs

template <typename type_t>
libs::maybe<type_t>::maybe()
    : em(libs::empty_maybe()), empty(true)
{
}

template <typename type_t>
libs::maybe<type_t>::maybe(
    const libs::empty_maybe &em)
    : libs::maybe<type_t>::maybe()
{
}

template <typename type_t>
libs::maybe<type_t>::maybe(
    const type_t &t)
    : tp(t), empty(false)
{
}

template <typename type_t>
libs::maybe<type_t>::maybe(
    type_t &&t)
    : tp(static_cast<type_t &&>(t)),
      empty(false)
{
}

template <typename type_t>
bool libs::empty(
    const libs::maybe<type_t> m)
{
  return m.empty;
}

template <typename type_t>
type_t &libs::get(
    libs::maybe<type_t> &m)
{
  return static_cast<type_t &>(m.tp);
}

template <typename type_t>
const type_t &libs::get(
    const libs::maybe<type_t> &m)
{
  return static_cast<const type_t &>(m.tp);
}

template <typename type_t>
type_t &&libs::get(
    libs::maybe<type_t> &&m)
{
  return static_cast<type_t &&>(m.tp);
}

#endif