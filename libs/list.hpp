#ifndef __libs_list_hpp__
#define __libs_list_hpp__

#include "types.hpp"
#include "algorithm.hpp"

namespace libs
{
  template <typename type_t>
  struct list_node
  {
    type_t object;

    list_node<type_t> *next = nullptr;

    list_node(const type_t &obj);
    list_node(type_t &&obj);
    list_node(const list_node &);
    list_node(list_node &&);
    ~list_node() = default;
    list_node &operator=(const list_node &);
    list_node &operator=(list_node &&);
  };

  template <typename type_t>
  struct list
  {
    size_t size = 0;
    list_node<type_t> *first = nullptr;
    list_node<type_t> *last = nullptr;

    list() = default;
    list(const list &);
    list(list &&);
    ~list();

    list &operator=(const list &) = delete;
    list &operator=(list &&);
  };

  template <typename type_t>
  struct list_iterator
  {
    list_node<type_t> *node = nullptr;
  };

  template <typename type_t>
  size_t size(const list<type_t> &);

  template <typename type_t>
  void push(
      list<type_t> &,
      const type_t &);

  template <typename type_t>
  void push(
      list<type_t> &,
      type_t &&);

  template <typename type_t>
  list_iterator<type_t>
  begin(list<type_t> &);

  template <typename type_t>
  list_iterator<type_t>
  end(list<type_t> &);

  template <typename type_t>
  list_iterator<const type_t>
  begin(const list<type_t> &);

  template <typename type_t>
  list_iterator<const type_t>
  end(const list<type_t> &);

  template <typename type_t>
  type_t &get(
      list_iterator<type_t> it);

  template <typename type_t>
  const type_t &get(
      list_iterator<const type_t> it);

  template <typename type_t>
  list_iterator<type_t>
  next(list_iterator<type_t> it);

  template <typename type_t>
  bool equals(
      list_iterator<type_t> l,
      list_iterator<type_t> r);

  template <typename type_t>
  size_t distance(
      list_iterator<type_t> l,
      list_iterator<type_t> r);
} // namespace libs

template <typename type_t>
libs::list_node<type_t>::list_node(
    const type_t &o)
    : object(o)
{
}

template <typename type_t>
libs::list_node<type_t>::list_node(
    type_t &&o)
    : object(static_cast<type_t &&>(o))
{
}

template <typename type_t>
libs::list_node<type_t>::list_node(
    const libs::list_node<type_t> &o)
    : object(o.object)
{
}

template <typename type_t>
libs::list_node<type_t>::list_node(
    libs::list_node<type_t> &&o)
    : object(static_cast<type_t &&>(o.object))
{
}

template <typename type_t>
libs::list_node<type_t> &
libs::list_node<type_t>::operator=(
    const libs::list_node<type_t> &o)
{
  if (this != &o)
    this->object = o.object;
  return *this;
}

template <typename type_t>
libs::list_node<type_t> &
libs::list_node<type_t>::operator=(
    libs::list_node<type_t> &&o)
{
  if (this != &o)
    object = static_cast<type_t &&>(o.object);
  return *this;
}

template <typename type_t>
libs::list<type_t>::list(
    const list<type_t> &o)
{
  libs::pushall(
      libs::begin(o),
      libs::end(o),
      *this);
}

template <typename type_t>
libs::list<type_t>::list(
    libs::list<type_t> &&o)
{
  this->size = o.size;
  this->first = o.first;
  this->last = o.last;

  o.size = 0;
  o.first = nullptr;
  o.last = nullptr;
}

template <typename type_t>
libs::list<type_t>::~list()
{
  libs::list_node<type_t> *tmp = first;

  while (first != nullptr)
  {
    tmp = first;
    first = tmp->next;
    delete tmp;
  }

  first = nullptr;
  last = nullptr;
  size = 0;
}

template <typename type_t>
libs::list<type_t> &
libs::list<type_t>::operator=(
    libs::list<type_t> &&o)
{
  if (this != &o)
  {
    this->size = o.size;
    this->first = o.first;
    this->last = o.last;

    o.size = 0;
    o.first = nullptr;
    o.last = nullptr;
  }

  return *this;
}

template <typename type_t>
libs::size_t libs::size(
    const libs::list<type_t> &l)
{
  return l.size;
}

template <typename type_t>
void libs::push(
    libs::list<type_t> &l,
    const type_t &o)
{
  libs::list_node<type_t> *node =
      new list_node<type_t>(o);

  if (l.first == nullptr)
  {
    l.first = node;
    l.last = node;
  }
  else
  {
    l.last->next = node;
    l.last = node;
  }

  l.size += 1;
}

template <typename type_t>
void libs::push(
    libs::list<type_t> &l,
    type_t &&o)
{
  libs::list_node<type_t> *node =
      new list_node<type_t>(
          static_cast<type_t &&>(o));

  if (l.first == nullptr)
  {
    l.first = node;
    l.last = node;
  }
  else
  {
    l.last->next = node;
    l.last = node;
  }

  l.size += 1;
}

template <typename type_t>
libs::list_iterator<type_t>
libs::begin(libs::list<type_t> &l)
{
  return {l.first};
}

template <typename type_t>
libs::list_iterator<type_t>
libs::end(libs::list<type_t> &l)
{
  return {};
}

template <typename type_t>
libs::list_iterator<const type_t>
libs::begin(const libs::list<type_t> &l)
{
  return {l.first};
}

template <typename type_t>
libs::list_iterator<const type_t>
libs::end(const libs::list<type_t> &l)
{
  return {};
}

template <typename type_t>
type_t &libs::get(
    libs::list_iterator<type_t> it)
{
  return it.node->object;
}

template <typename type_t>
const type_t &libs::get(
    libs::list_iterator<const type_t> it)
{
  return it.node->object;
}

template <typename type_t>
libs::list_iterator<type_t>
libs::next(libs::list_iterator<type_t> it)
{
  if (it.node != nullptr)
    return {it.node->next};
  else
    return {};
}

template <typename type_t>
bool libs::equals(
    libs::list_iterator<type_t> l,
    libs::list_iterator<type_t> r)
{
  return l.node == r.node;
}

template <typename type_t>
libs::size_t libs::distance(
    libs::list_iterator<type_t> l,
    libs::list_iterator<type_t> r)
{
  libs::size_t dist = 0;

  while (not libs::equals(l, r))
  {
    dist += 1;
    l = libs::next(l);
  }

  return dist;
}

#endif