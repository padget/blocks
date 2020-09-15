#ifndef __libs_pointer_hpp__
#define __libs_pointer_hpp__

namespace libs
{
  template <typename type_t>
  struct pointer
  {
    type_t *p = nullptr;

    pointer() = default;
    pointer(type_t *t);
    pointer(const pointer &) = default;
    pointer(pointer &&) = default;
    ~pointer() = default;

    pointer &operator=(pointer &) = default;
    pointer &operator=(pointer &&) = default;
  };

  template <typename type_t>
  bool empty(const pointer<type_t> &p);

  template <typename type_t>
  type_t &get(pointer<type_t> &p);

  template <typename type_t>
  type_t &get(pointer<type_t> &&p);

  template <typename type_t>
  const type_t &get(const pointer<type_t> &p);

  template <typename type_t>
  const type_t &get(const pointer<type_t> &&p);
} // namespace libs

template <typename type_t>
libs::pointer<type_t>::pointer(
    type_t *t) : p(t)
{
}

template <typename type_t>
bool libs::empty(
    const libs::pointer<type_t> &p)
{
  return p.p == nullptr;
}

template <typename type_t>
type_t &
libs::get(
    libs::pointer<type_t> &p)
{
  return *p.p;
}

template <typename type_t>
type_t &
libs::get(
    libs::pointer<type_t> &&p)
{
  return *p.p;
}

template <typename type_t>
const type_t &
libs::get(
    const libs::pointer<type_t> &p)
{
  return *p.p;
}

template <typename type_t>
const type_t &
libs::get(
    const libs::pointer<type_t> &&p)
{
  return *p.p;
}

#endif