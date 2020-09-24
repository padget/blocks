#ifndef __libs_map_hpp__
#define __libs_map_hpp__

#include "list.hpp"

namespace libs
{
    template <
        typename key_t,
        typename value_t>
    struct entry
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
        list<entry<key_t, value_t>> nodes;

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

} // namespace libs

template <
    typename key_t,
    typename value_t>
void libs::push(
    libs::map<key_t, value_t> &m,
    const key_t &key,
    const value_t &value)
{
    auto b = libs::begin(m.nodes);
    auto e = libs::end(m.nodes);

    while (not libs::equals(b, e))
    { 
    } 
}

#endif