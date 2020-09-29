#ifndef __libs_types_hpp__
#define __libs_types_hpp__

#include <limits>

namespace libs
{
    using index_t = unsigned long long;
    using size_t = unsigned long long;
    using hash_t = long long;

    template <typename type_t>
    constexpr type_t limitmax =
        std::numeric_limits<type_t>::max();
    
    template <typename type_t>
    constexpr type_t limitmin =
        std::numeric_limits<type_t>::min();
} // namespace libs

#endif