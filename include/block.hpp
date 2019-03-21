#ifndef __BLOCKS_BLOCK_HPP__
#define __BLOCKS_BLOCK_HPP__

#include <array>
#include <utility>

using uchar = unsigned char;
using cuchar = const uchar;
using cpuchar = cuchar *;
using cpvoid = const void *;

template <size_t size>
using block = std::array<uchar, size>;

template <typename block_t>
class basic_block_space_allocator
{
private:
  typename block_t::iterator __last_attributed;

public:
  basic_block_space_allocator(block_t &bl)
      : __last_attributed(std::begin(bl)) {}

  template <typename type_t>
  auto malloc(const type_t &)
  {
    auto res = this->__last_attributed;
    this->__last_attributed = this->__last_attributed + sizeof(time_t);
    return res;
  }

  template <typename type_t>
  auto store(type_t &&obj, block_t &)
  {
    auto &&iter = malloc(obj);
    auto &&begin = to_bytes(std::forward<type_t &&>(obj));
    std::copy(begin, begin + sizeof(obj), iter);
    return iter;
  }

  template <typename type_t>
  const type_t &read(const typename block_t::iterator iter) const
  {
    return from_bytes<type_t>(iter);
  }

  template <typename type_t>
  type_t &read(typename block_t::iterator iter)
  {
    return from_bytes<type_t>(iter);
  }

private:
  template <typename type_t>
  const uchar *to_bytes(const type_t &obj) const
  {
    return reinterpret_cast<cuchar *>(
        std::addressof(obj));
  }

  template <typename type_t>
  uchar *to_bytes(type_t &obj)
  {
    return reinterpret_cast<uchar *>(
        std::addressof(obj));
  }

  template <typename type_t>
  const type_t &from_bytes(cuchar *bytes) const
  {
    return *(reinterpret_cast<const type_t *>(
        reinterpret_cast<const void *>(bytes)));
  }

  template <typename type_t>
  type_t &from_bytes(uchar *bytes)
  {
    return *(reinterpret_cast<type_t *>(
        reinterpret_cast<void *>(bytes)));
  }
};

template <
    typename block_t,
    typename bloc_space_allocator = basic_block_space_allocator<block_t>>
class block_manager final
{
private:
  std::reference_wrapper<block_t> __bl;
  bloc_space_allocator __allocator;

public:
  block_manager(block_t &bl)
      : __bl(std::ref(bl)),
        __allocator(bloc_space_allocator(__bl)) {}

public:
  template <typename type_t>
  auto store(type_t &&obj)
  {
    return __allocator.store(std::forward<type_t &&>(obj), this->__bl);
  }

  template <typename type_t>
  const type_t &read(const typename block_t::iterator iter) const
  {
    return __allocator.template read<type_t>(iter);
  }

  template <typename type_t>
  type_t &read(typename block_t::iterator iter)
  {
    return __allocator.template read<type_t>(iter);
  }
};

#endif