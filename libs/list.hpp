#ifndef __libs_list_hpp__
#define __libs_list_hpp__

#include "pointer.hpp"

namespace libs
{
  using size_t = unsigned long long;

  template <typename type_t>
  struct list_node
  {
    type_t object;

    list_node<type_t> *next;

    list_node(const type_t &obj);
    list_node(type_t &&obj);
    list_node(const list_node &) = default;
    list_node(list_node &&) = default;
    ~list_node();
    list_node &operator=(const list_node &) = default;
    list_node &operator=(list_node &&) = default;
  };

  template <typename type_t>
  struct list
  {
    size_t size;
    list_node<type_t> *first;
    list_node<type_t> *last;

    list();
    list(const list &);
    list(list &&);
    ~list();

    list &operator=(const list &);
    list &operator=(list &&);
  };

  template <typename type_t>
  struct list_iterator
  {
    list_node<type_t> *data;
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
  list_iterator<type_t>
  next(list_iterator<type_t> it);

  template <typename type_t>
  list_iterator<type_t>
  pred(list_iterator<type_t> it);

  template <typename type_t>
  bool equals(
      list_iterator<type_t> l,
      list_iterator<type_t> r);

  template <typename type_t>
  size_t distance(
      list_iterator<type_t> l,
      list_iterator<type_t> r);
} // namespace libs

#endif