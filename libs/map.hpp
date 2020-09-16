#ifndef __libs_map_hpp__
#define __libs_map_hpp__

#include "vector.hpp"

namespace libs
{
  using hash_t = long long;

  template <
      typename key_t,
      typename value_t>
  struct map_node
  {
    hash_t hash;
    key_t key;
    value_t value;
  };

  template <
      typename key_t,
      typename value_t>
  struct map
  {
    vector<map_node> nodes;

    map() = default;
    map(const map &) = default;
    map(map &&) = default;
    ~map() = default;

    map &operator=(const map &) = default;
    map &operator=(map &&) = default;
  };

  template <
      typename key_t,
      typename value_t>
  bool contains(
      const map<key_t, value_t> &m,
      const key_t key);

  template <
      typename key_t,
      typename value_t>
  void push(
      map<key_t, value_t> &m,
      const key_t &key,
      const value_t &value);

  template <
      typename key_t,
      typename value_t>
  void push(
      map<key_t, value_t> &m,
      key_t &&key,
      value_t &&value);

  template <
      typename key_t,
      typename value_t>
  void remove(
      map<key_t, value_t> &m,
      const key_t &key);

} // namespace libs

#endif