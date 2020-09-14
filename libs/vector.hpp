#ifndef __vector_hpp__
#define __vector_hpp__

#include <stdexcept>

namespace libs
{
  using index_t = unsigned long long;
  using size_t = unsigned long long;

  template <typename type_t>
  struct vector
  {
    type_t *data = nullptr;
    size_t size = 0;

    vector() = default;
    template <size_t size_v>
    vector(type_t(&&data)[size_v]);
    template <size_t size_v>
    vector(const type_t(&data)[size_v]);
    vector(size_t size);
    vector(const vector &o);
    vector(vector &&o);
    ~vector();

    vector &operator=(const vector &o);
    vector &operator=(vector &&);
  };

  // Size getter
  template <typename type_t>
  size_t size(const vector<type_t> &v);

  // Constant getter
  template <typename type_t>
  const type_t &get(
      const vector<type_t> &v, index_t idx);

  // Mutable getter
  template <typename type_t>
  type_t &get(vector<type_t> &v, index_t idx);

  // Setter by move
  template <typename type_t>
  void set(vector<type_t> &v,
           index_t index, type_t &&t);

  // Setter by copie
  template <typename type_t>
  void set(vector<type_t> &v,
           index_t index, const type_t &t);

} // namespace libs

template <typename type_t>
libs::vector<type_t>::vector(
    libs::size_t size)
{
  this->data = new type_t[size];
  this->size = size;
}

template <typename type_t>
template <libs::size_t size_v>
libs::vector<type_t>::vector(
    type_t(&&data)[size_v])
    : libs::vector<type_t>::vector(size_v)
{
  for (libs::index_t i = 0; i < this->size; ++i)
    this->data[i] = static_cast<type_t &&>(data[i]);
}

template <typename type_t>
template <libs::size_t size_v>
libs::vector<type_t>::vector(
    const type_t(&data)[size_v])
    : libs::vector<type_t>::vector(size_v)
{
  for (libs::index_t i = 0; i < this->size; ++i)
    this->data[i] = data[i];
}

template <typename type_t>
libs::vector<type_t>::vector(
    const vector<type_t> &o)
{
  this->size = libs::size(o);
  this->data = new type_t[this->size];

  for (index_t i = 0; i < this->size; ++i)
    this->data[i] = libs::get(o, i);
}

template <typename type_t>
libs::vector<type_t>::vector(
    vector<type_t> &&o)
{
  using namespace libs;
  this->data = o.data;
  this->size = o.size;
  o.size = 0;
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
    o.data = nullptr;
    o.size = 0;
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
const type_t &
libs::get(
    const libs::vector<type_t> &v,
    libs::index_t idx)
{
  if (idx < v.size)
    return v.data[idx];
  else
    throw std::out_of_range(
        "bad range access");
}

template <typename type_t>
type_t &libs::get(
    libs::vector<type_t> &v,
    libs::index_t idx)
{
  if (idx < v.size)
    return v.data[idx];
  else
    throw std::out_of_range(
        "bad range access");
}

template <typename type_t>
void libs::set(
    libs::vector<type_t> &v,
    libs::index_t index, type_t &&t)
{
  if (index < v.size)
    v.data[index] = static_cast<type_t &&>(t);
  else
    throw std::out_of_range(
        "bad range access");
}

template <typename type_t>
void libs::set(
    libs::vector<type_t> &v,
    libs::index_t index, const type_t &t)
{

  if (index < v.size)
    v.data[index] = static_cast<type_t &&>(t);
  else
    throw std::out_of_range(
        "bad range access");
}

#endif