#ifndef __named_type_hpp__
#define __named_type_hpp__

#include <utility>

namespace blocks
{
  template <typename type_t, typename tag_t>
  class named_type
  {
  private:
    type_t t;

  public:
    explicit named_type() = default;
    explicit named_type(const type_t &_t) : t(_t) {}
    explicit named_type(type_t &&_t) : t(std::move(_t)) {}
    named_type(const named_type &o) = default;
    named_type(named_type &&o) = default;
    ~named_type() = default;
    named_type &operator=(const named_type &) = default;
    named_type &operator=(named_type &&) = default;

  public:
    type_t &get() { return t; }
    const type_t &get() const { return t; }

  public:
    operator type_t &() & { return t; }
    operator type_t const &() const & { return t; }
    operator type_t &&() { return std::move(t); }
  };

  template <typename type_t, typename tag_t>
  using nt = named_type<type_t, tag_t>;
} // namespace blocks

#define tag(name) struct name##_tag

#endif