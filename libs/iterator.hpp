#ifndef __libs_iterator_hpp__
#define __libs_iterator_hpp__

namespace libs
{
  template <
      template <typename>
      typename container_t,
      typename type_t>
  void push(
      container_t<type_t> &v,
      type_t &&t);

  // Setter by copie
  template <
      template <typename>
      typename container_t,
      typename type_t>
  void push(
      container_t<type_t> &v,
      const type_t &t);

  template <
      template <typename>
      typename iterator_t,
      typename type_t>
  type_t &get(
      iterator_t<type_t> it);

  template <
      template <typename>
      typename iterator_t,
      typename type_t>
  const type_t &get(
      iterator_t<const type_t> it);

  template <typename iterator_t>
  iterator_t
  next(iterator_t it);

  template <typename iterator_t>
  iterator_t
  pred(iterator_t it);

  template <typename iterator_t>
  bool equals(
      iterator_t l,
      iterator_t r);

  template <typename iterator_t>
  size_t distance(
      iterator_t l,
      iterator_t r);
} // namespace libs

#endif