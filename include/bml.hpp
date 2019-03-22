#ifndef __BLOCKS_BML_HPP__
#define __BLOCKS_BML_HPP__

#include <string>
#include <type_traits>

template <typename char_t>
class char_wrapper
{
private:
  char_t c;

public:
  explicit char_wrapper(char_t c)
      : c(c) {}

public:
  bool in(char_t first, char_t end) const
  {
    return first <= c and c <= end;
  }

  bool is(char_t o) const
  {
    return c == o;
  }

  void reset(char_t c)
  {
    this->c = c;
  }
};

template <
    typename enum_t,
    typename str_t = std::string>
class token
{
  static_assert(std::is_enum_v<enum_t>);

private:
  enum_t __type;
  str_t __value;

public:
  explicit token(const str_t &value)
      : __value(value) {}

  token(token &&other)
      : __type(std::move(other.__type)),
        __value(std::move(other.__value)) {}

public:
  const str_t &value() const
  {
    return __value;
  }

  str_t &value()
  {
    return __value;
  }

public:
  const enum_t &type() const
  {
    return __type;
  }

  enum_t &type()
  {
    return __type;
  }
};

template <typename str_t = std::string>
class lexer
{
public:
  token<str_t> token()
  {
  }
};

template <typename it_t>
bool is_label(it_t begin, it_t end)
{
  char_wrapper<decltype(*begin)> c;
  it_t cursor = begin;

  while (cursor != end and c.reset(*cursor).in('a', 'z'))
    cursor++;

  return true;
}

template <typename it_t>
bool is_colon(it_t begin, it_t end)
{
  return char_wrapper(*begin).is(':');
}

#endif