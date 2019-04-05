//
// Created by bm383a1n on 05/04/2019.
//

#ifndef BLOCKS_RESULT_HPP
#define BLOCKS_RESULT_HPP

#include <variant>

template<typename some,
         typename error>
using result = std::variant<some, error>;

#endif //BLOCKS_RESULT_HPP
