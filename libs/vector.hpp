#ifndef __vector_hpp__
#define __vector_hpp__

#include "types.hpp"

namespace libs
{
  template <typename type_t>
  struct vector
  {
    type_t *data = nullptr;
    size_t size = 0;
    size_t capacity = 0;

    vector() = default;
    vector(size_t cap);

    vector(type_t *data, size_t cap);
    vector(const type_t *data, size_t cap);

    vector(const vector &o);
    vector(vector &&o);

    template <size_t size_v>
    vector(type_t(&&data)[size_v]);
    template <size_t size_v>
    vector(const type_t (&data)[size_v]);

    ~vector();

    vector &operator=(const vector &o);
    vector &operator=(vector &&);
  };

  template <typename type_t>
  struct vector_iterator
  {
    type_t *p;
  };

  // Size getter
  template <typename type_t>
  size_t size(const vector<type_t> &v);

  // Setter by move
  template <typename type_t>
  void push(
      vector<type_t> &v,
      type_t &&t);

  // Setter by copie
  template <typename type_t>
  void push(
      vector<type_t> &v,
      const type_t &t);

  template <typename type_t>
  vector_iterator<type_t>
  begin(vector<type_t> &v);

  template <typename type_t>
  vector_iterator<type_t>
  end(vector<type_t> &v);

  template <typename type_t>
  vector_iterator<const type_t>
  begin(const vector<type_t> &v);

  template <typename type_t>
  vector_iterator<const type_t>
  end(const vector<type_t> &v);

  template <typename type_t>
  vector_iterator<type_t>
  rbegin(vector<type_t> &v);

  template <typename type_t>
  vector_iterator<type_t>
  rend(vector<type_t> &v);

  template <typename type_t>
  vector_iterator<const type_t>
  rbegin(const vector<type_t> &v);

  template <typename type_t>
  vector_iterator<const type_t>
  rend(const vector<type_t> &v);

  template <typename type_t>
  type_t &get(
      vector_iterator<type_t> it);

  template <typename type_t>
  const type_t &get(
      vector_iterator<const type_t> it);

  template <typename type_t>
  vector_iterator<type_t>
  next(vector_iterator<type_t> it);

  template <typename type_t>
  vector_iterator<type_t>
  pred(vector_iterator<type_t> it);

  template <typename type_t>
  bool equals(
      vector_iterator<type_t> l,
      vector_iterator<type_t> r);

  template <typename type_t>
  size_t distance(
      vector_iterator<type_t> l,
      vector_iterator<type_t> r);

} // namespace libs

template <typename type_t>
libs::vector<type_t>::vector(
    libs::size_t cap)
{
  this->data = new type_t[cap];
  this->size = 0;
  this->capacity = cap;
}

template <typename type_t>
libs::vector<type_t>::vector(
    type_t *data, size_t cap)
    : libs::vector<type_t>::vector(cap)
{

  for (libs::index_t i = 0; i < cap; ++i)
    push(*this, data[i]);
}

template <typename type_t>
libs::vector<type_t>::vector(
    const type_t *data, size_t cap)
    : libs::vector<type_t>::vector(cap)
{
  for (libs::index_t i = 0; i < cap; ++i)
    push(*this, data[i]);
}

template <typename type_t>
template <libs::size_t size_v>
libs::vector<type_t>::vector(
    type_t(&&data)[size_v])
    : libs::vector<type_t>::vector(size_v)
{
  for (libs::index_t i = 0; i < size_v; ++i)
    push(*this, static_cast<type_t &&>(data[i]));
}

template <typename type_t>
template <libs::size_t size_v>
libs::vector<type_t>::vector(
    const type_t (&data)[size_v])
    : libs::vector<type_t>::vector(size_v)
{
  for (libs::index_t i = 0; i < size_v; ++i)
    this->data[i] = data[i];
}

template <typename type_t>
libs::vector<type_t>::vector(
    const vector<type_t> &o)
    : libs::vector<type_t>::vector(o.capacity)
{
  for (index_t i = 0; i < o.size; ++i)
    push(*this, o.data[i]);
}

template <typename type_t>
libs::vector<type_t>::vector(
    vector<type_t> &&o)
{
  this->size = o.size;
  this->capacity = o.capacity;
  this->data = o.data;

  o.size = 0;
  o.capacity = 0;
  o.data = nullptr;
}

template <typename type_t>
libs::vector<type_t>::~vector()
{
  delete this->data;
}

template <typename type_t>
libs::vector<type_t> &
libs::vector<type_t>::operator=(
    const vector<type_t> &o)
{
  if (this != &o)
  {
    delete this->data;
    libs::size_t ocap = o.capacity;
    this->data = new type_t[ocap];
    this->capacity = ocap;

    for (index_t i = 0; i < ocap; ++i)
      push(*this, o.data[i]);
  }

  return *this;
}

template <typename type_t>
libs::vector<type_t> &
libs::vector<type_t>::operator=(
    vector<type_t> &&o)
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
    const libs::vector<type_t> &v)
{
  return v.size;
}

template <typename type_t>
void libs::push(
    libs::vector<type_t> &v,
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
    libs::vector<type_t> &v,
    const type_t &t)
{
  if (v.size < v.capacity)
  {
    v.data[v.size] =
        static_cast<type_t &&>(t);
    v.size += 1;
  }
}

template <typename type_t>
libs::vector_iterator<type_t>
libs::begin(libs::vector<type_t> &v)
{
  return {v.data};
}

template <typename type_t>
libs::vector_iterator<type_t>
libs::end(libs::vector<type_t> &v)
{
  return {v.data + v.size};
}

template <typename type_t>
libs::vector_iterator<const type_t>
libs::begin(const libs::vector<type_t> &v)
{
  return {v.data};
}

template <typename type_t>
libs::vector_iterator<const type_t>
libs::end(const libs::vector<type_t> &v)
{
  return {v.data + v.size};
}

template <typename type_t>
libs::vector_iterator<type_t>
libs::rbegin(libs::vector<type_t> &v)
{
  return {v.data + v.size - 1};
}

template <typename type_t>
libs::vector_iterator<type_t>
libs::rend(libs::vector<type_t> &v)
{
  return {v.data - 1};
}

template <typename type_t>
libs::vector_iterator<const type_t>
libs::rbegin(const libs::vector<type_t> &v)
{

  return {v.data + v.size - 1};
}

template <typename type_t>
libs::vector_iterator<const type_t>
libs::rend(const libs::vector<type_t> &v)
{
  return {v.data - 1};
}

template <typename type_t>
type_t &libs::get(
    libs::vector_iterator<type_t> it)
{
  return *it.p;
}

template <typename type_t>
const type_t &libs::get(
    libs::vector_iterator<const type_t> it)
{
  return *it.p;
}

template <typename type_t>
libs::vector_iterator<type_t>
libs::next(
    libs::vector_iterator<type_t> it)
{
  return {it.p + 1};
}

template <typename type_t>
libs::vector_iterator<type_t>
libs::pred(
    libs::vector_iterator<type_t> it)
{
  return {it.p - 1};
}

template <typename type_t>
bool libs::equals(
    libs::vector_iterator<type_t> l,
    libs::vector_iterator<type_t> r)
{
  return l.p == r.p;
}

template <typename type_t>
libs::size_t libs::distance(
    libs::vector_iterator<type_t> b,
    libs::vector_iterator<type_t> e)
{
  return e.p - b.p;
}

#endif