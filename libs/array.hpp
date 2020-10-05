#ifndef __libs_array_hpp__
#define __libs_array_hpp__

#include "types.hpp"
#include "algorithm.hpp"

namespace libs
{
  template <typename type_t>
  struct array
  {
    type_t *data = nullptr;
    size_t size = 0;
    size_t capacity = 0;

    array() = default;
    array(size_t cap);

    array(type_t *data, size_t cap);
    array(const type_t *data, size_t cap);

    array(const array &o);
    array(array &&o);

    template <size_t size_v>
    array(type_t(&&data)[size_v]);

    template <size_t size_v>
    array(const type_t (&data)[size_v]);

    template <typename iterator_t>
    array(iterator_t b, iterator_t e);

    ~array();

    array &operator=(const array &o) = delete;
    array &operator=(array &&);
  };

  template <typename type_t>
  struct array_iterator
  {
    type_t *p;
  };

  // Size getter
  template <typename type_t>
  size_t size(const array<type_t> &v);

  // Setter by move
  template <typename type_t>
  void push(
      array<type_t> &v,
      type_t &&t);

  // Setter by copie
  template <typename type_t>
  void push(
      array<type_t> &v,
      const type_t &t);

  template <typename type_t>
  array_iterator<type_t>
  begin(array<type_t> &v);

  template <typename type_t>
  array_iterator<type_t>
  end(array<type_t> &v);

  template <typename type_t>
  array_iterator<const type_t>
  begin(const array<type_t> &v);

  template <typename type_t>
  array_iterator<const type_t>
  end(const array<type_t> &v);

  template <typename type_t>
  array_iterator<type_t>
  rbegin(array<type_t> &v);

  template <typename type_t>
  array_iterator<type_t>
  rend(array<type_t> &v);

  template <typename type_t>
  array_iterator<const type_t>
  rbegin(const array<type_t> &v);

  template <typename type_t>
  array_iterator<const type_t>
  rend(const array<type_t> &v);

  template <typename type_t>
  type_t &get(
      array_iterator<type_t> it);

  template <typename type_t>
  const type_t &get(
      array_iterator<const type_t> it);

  template <typename type_t>
  array_iterator<type_t>
  next(array_iterator<type_t> it);

  template <typename type_t>
  array_iterator<type_t>
  pred(array_iterator<type_t> it);

  template <typename type_t>
  bool equals(
      array_iterator<type_t> l,
      array_iterator<type_t> r);

  template <typename type_t>
  size_t distance(
      array_iterator<type_t> l,
      array_iterator<type_t> r);

} // namespace libs

template <typename type_t>
libs::array<type_t>::array(
    libs::size_t cap)
{
  this->data = new type_t[cap];
  this->size = 0;
  this->capacity = cap;
}

template <typename type_t>
libs::array<type_t>::array(
    type_t *data, size_t cap)
    : libs::array<type_t>::array(cap)
{
  for (libs::index_t i = 0; i < cap; ++i)
    libs::push(*this, data[i]);
}

template <typename type_t>
libs::array<type_t>::array(
    const type_t *data, size_t cap)
    : libs::array<type_t>::array(cap)
{
  for (libs::index_t i = 0; i < cap; ++i)
    libs::push(*this, data[i]);
}

template <typename type_t>
template <libs::size_t size_v>
libs::array<type_t>::array(
    type_t(&&data)[size_v])
    : libs::array<type_t>::array(size_v)
{
  for (libs::index_t i = 0; i < size_v; ++i)
    libs::push(*this, static_cast<type_t &&>(data[i]));
}

template <typename type_t>
template <libs::size_t size_v>
libs::array<type_t>::array(
    const type_t (&data)[size_v])
    : libs::array<type_t>::array(size_v)
{
  for (libs::index_t i = 0; i < size_v; ++i)
    this->data[i] = data[i];
}

template <typename type_t>
libs::array<type_t>::array(
    const array<type_t> &o)
    : libs::array<type_t>::array(o.capacity)
{
  for (index_t i = 0; i < o.size; ++i)
    libs::push(*this, o.data[i]);
}

template <typename type_t>
libs::array<type_t>::array(
    array<type_t> &&o)
{
  this->size = o.size;
  this->capacity = o.capacity;
  this->data = o.data;

  o.size = 0;
  o.capacity = 0;
  o.data = nullptr;
}

template <typename type_t>
template <typename iterator_t>
libs::array<type_t>::array(
    iterator_t b, iterator_t e)
    : libs::array<type_t>::array(distance(b, e))
{
  libs::pushall(b, e, *this);
}

template <typename type_t>
libs::array<type_t>::~array()
{
  delete this->data;
}

template <typename type_t>
libs::array<type_t> &
libs::array<type_t>::operator=(
    array<type_t> &&o)
{
  if (this != &o)
  {
    delete this->data;

    this->data = o.data;
    this->size = o.size;
    this->capacity = o.capacity;

    o.data = nullptr;
    o.size = 0;
    o.capacity = 0;
  }

  return *this;
}

template <typename type_t>
libs::size_t
libs::size(
    const libs::array<type_t> &v)
{
  return v.size;
}

template <typename type_t>
void libs::push(
    libs::array<type_t> &v,
    type_t &&t)
{
  if (v.size < v.capacity)
  {
    v.data[v.size] =
        static_cast<type_t &&>(t);
    v.size += 1;
  }
}

template <typename type_t>
void libs::push(
    libs::array<type_t> &v,
    const type_t &t)
{
  if (v.size < v.capacity)
  {
    v.data[v.size] = t;
    v.size += 1;
  }
}

template <typename type_t>
libs::array_iterator<type_t>
libs::begin(libs::array<type_t> &v)
{
  return {v.data};
}

template <typename type_t>
libs::array_iterator<type_t>
libs::end(libs::array<type_t> &v)
{
  return {v.data + v.size};
}

template <typename type_t>
libs::array_iterator<const type_t>
libs::begin(const libs::array<type_t> &v)
{
  return {v.data};
}

template <typename type_t>
libs::array_iterator<const type_t>
libs::end(const libs::array<type_t> &v)
{
  return {v.data + v.size};
}

template <typename type_t>
libs::array_iterator<type_t>
libs::rbegin(libs::array<type_t> &v)
{
  return {v.data + v.size - 1};
}

template <typename type_t>
libs::array_iterator<type_t>
libs::rend(libs::array<type_t> &v)
{
  return {v.data - 1};
}

template <typename type_t>
libs::array_iterator<const type_t>
libs::rbegin(const libs::array<type_t> &v)
{

  return {v.data + v.size - 1};
}

template <typename type_t>
libs::array_iterator<const type_t>
libs::rend(const libs::array<type_t> &v)
{
  return {v.data - 1};
}

template <typename type_t>
type_t &libs::get(
    libs::array_iterator<type_t> it)
{
  return *it.p;
}

template <typename type_t>
const type_t &libs::get(
    libs::array_iterator<const type_t> it)
{
  return *it.p;
}

template <typename type_t>
libs::array_iterator<type_t>
libs::next(
    libs::array_iterator<type_t> it)
{
  return {it.p + 1};
}

template <typename type_t>
libs::array_iterator<type_t>
libs::pred(
    libs::array_iterator<type_t> it)
{
  return {it.p - 1};
}

template <typename type_t>
bool libs::equals(
    libs::array_iterator<type_t> l,
    libs::array_iterator<type_t> r)
{
  return l.p == r.p;
}

template <typename type_t>
libs::size_t libs::distance(
    libs::array_iterator<type_t> b,
    libs::array_iterator<type_t> e)
{
  return e.p - b.p;
}

#endif