#ifndef __vector_hpp__
#define __vector_hpp__

#include "pointer.hpp"

namespace libs
{
  using index_t = unsigned long long;
  using size_t = unsigned long long;

  template <typename type_t>
  struct vector
  {
    type_t *data = nullptr;
    size_t size = 0;
    size_t capacity = 0;

    vector() = default;

    vector(type_t *data, size_t size);
    vector(const type_t *data, size_t size);

    template <size_t size_v>
    vector(type_t(&&data)[size_v]);
    template <size_t size_v>
    vector(const type_t (&data)[size_v]);
    vector(size_t size);
    vector(const vector &o);
    vector(vector &&o);
    ~vector();

    vector &operator=(const vector &o);
    vector &operator=(vector &&);
  };

  template <typename type_t>
  using vector_iterator = pointer<type_t>;

  // Size getter
  template <typename type_t>
  size_t size(const vector<type_t> &v);

  template <typename type_t>
  const pointer<type_t> get(
      const vector<type_t> &v, index_t idx);

  template <typename type_t>
  pointer<type_t> get(
      vector<type_t> &v, index_t idx);

  // Setter by move
  template <typename type_t>
  void set(
      vector<type_t> &v,
      index_t index, type_t &&t);

  // Setter by copie
  template <typename type_t>
  void set(
      vector<type_t> &v,
      index_t index, const type_t &t);

  template <typename type_t>
  void push_back(
      vector<type_t> &v,
      const type_t &t);

  template <typename type_t>
  void push_back(
      vector<type_t> &v,
      type_t &&t);

  template <typename type_t>
  void pop_back(vector<type_t> &v);

  template <typename type_t>
  void push_front(
      vector<type_t> &v,
      const type_t &t);

  template <typename type_t>
  void push_front(
      vector<type_t> &v,
      type_t &&t);

  template <typename type_t>
  void pop_front(vector<type_t> &v);

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
  vector_iterator<type_t>
  next(vector_iterator<type_t> it);

  template <typename type_t>
  vector_iterator<type_t>
  pred(vector_iterator<type_t> it);

  template <typename type_t>
  bool equals(
      vector_iterator<type_t> l,
      vector_iterator<type_t> r);

} // namespace libs

template <typename type_t>
libs::vector<type_t>::vector(
    libs::size_t size)
{
  this->data = new type_t[size];
  this->size = size;
  this->capacity = size;
}

template <typename type_t>
libs::vector<type_t>::vector(
    type_t *data, size_t size_v)
    : libs::vector<type_t>::vector(size_v)
{
  for (libs::index_t i = 0;
       i < this->size; ++i)
    this->data[i] = data[i];
}

template <typename type_t>
libs::vector<type_t>::vector(
    const type_t *data, size_t size_v)
    : libs::vector<type_t>::vector(size_v)
{
  for (libs::index_t i = 0;
       i < this->size; ++i)
    this->data[i] = data[i];
}

template <typename type_t>
template <libs::size_t size_v>
libs::vector<type_t>::vector(
    type_t(&&data)[size_v])
    : libs::vector<type_t>::vector(size_v)
{
  for (libs::index_t i = 0;
       i < this->size; ++i)
    this->data[i] = static_cast<type_t &&>(data[i]);
}

template <typename type_t>
template <libs::size_t size_v>
libs::vector<type_t>::vector(
    const type_t (&data)[size_v])
    : libs::vector<type_t>::vector(size_v)
{
  for (libs::index_t i = 0;
       i < this->size; ++i)
    this->data[i] = data[i];
}

template <typename type_t>
libs::vector<type_t>::vector(
    const vector<type_t> &o)
    : libs::vector<type_t>::vector(o.size)
{
  for (index_t i = 0;
       i < this->size; ++i)
    this->data[i] = o.data[i];
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
    libs::size_t osize = o.size;
    this->data = new type_t[osize];
    this->capacity = o.capacity;

    for (index_t i = 0; i < osize; ++i)
      this->data[i] = o.data[i];
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
const libs::pointer<type_t>
libs::get(
    const libs::vector<type_t> &v,
    libs::index_t idx)
{
  if (idx < v.size)
    return libs::pointer<type_t>(&v.data[idx]);
  else
    return libs::pointer<type_t>();
}

template <typename type_t>
libs::pointer<type_t>
libs::get(
    libs::vector<type_t> &v,
    libs::index_t idx)
{
  if (idx < v.size)
    return libs::pointer<type_t>(&v.data[idx]);
  else
    return libs::pointer<type_t>();
}

template <typename type_t>
void libs::set(
    libs::vector<type_t> &v,
    libs::index_t index, type_t &&t)
{
  if (index < v.size)
    v.data[index] = static_cast<type_t &&>(t);
}

template <typename type_t>
void libs::set(
    libs::vector<type_t> &v,
    libs::index_t index, const type_t &t)
{
  if (index < v.size)
    v.data[index] = static_cast<type_t &&>(t);
}

template <typename type_t>
void libs::push_back(
    libs::vector<type_t> &v,
    const type_t &t);

template <typename type_t>
void push_back(
    vector<type_t> &v,
    type_t &&t);

template <typename type_t>
void pop_back(vector<type_t> &v);

template <typename type_t>
void push_front(
    vector<type_t> &v,
    const type_t &t);

template <typename type_t>
void push_front(
    vector<type_t> &v,
    type_t &&t);

template <typename type_t>
void pop_front(vector<type_t> &v);

template <typename type_t>
libs::vector_iterator<type_t>
libs::begin(libs::vector<type_t> &v)
{
  return libs::vector_iterator<type_t>(v.data);
}

template <typename type_t>
libs::vector_iterator<type_t>
libs::end(libs::vector<type_t> &v)
{
  return libs::vector_iterator<type_t>(v.data + v.size);
}

template <typename type_t>
libs::vector_iterator<const type_t>
libs::begin(const libs::vector<type_t> &v)
{
  return libs::vector_iterator<const type_t>(v.data);
}

template <typename type_t>
libs::vector_iterator<const type_t>
libs::end(const libs::vector<type_t> &v)
{
  return libs::vector_iterator<const type_t>(v.data + v.size);
}

template <typename type_t>
libs::vector_iterator<type_t>
libs::rbegin(libs::vector<type_t> &v)
{
  return libs::vector_iterator<type_t>(v.data + v.size - 1);
}

template <typename type_t>
libs::vector_iterator<type_t>
libs::rend(libs::vector<type_t> &v)
{
  return libs::vector_iterator<type_t>(v.data - 1);
}

template <typename type_t>
libs::vector_iterator<const type_t>
libs::rbegin(const libs::vector<type_t> &v)
{

  return libs::vector_iterator<const type_t>(v.data + v.size - 1);
}

template <typename type_t>
libs::vector_iterator<const type_t>
libs::rend(const libs::vector<type_t> &v)
{
  return libs::vector_iterator<const type_t>(v.data - 1);
}

template <typename type_t>
libs::vector_iterator<type_t>
libs::next(
    libs::vector_iterator<type_t> it)
{
  return libs::vector_iterator<type_t>(it.p + 1);
}

template <typename type_t>
libs::vector_iterator<type_t>
libs::pred(
    libs::vector_iterator<type_t> it)
{
  return libs::vector_iterator<type_t>(it.p - 1);
}

template <typename type_t>
bool libs::equals(
    libs::vector_iterator<type_t> l,
    libs::vector_iterator<type_t> r)
{
  return l.p == r.p;
}

#endif