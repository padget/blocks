#ifndef __blocks_std_hpp__
#define __blocks_std_hpp__

#include <vector>
#include <initializer_list>
#include <string>
#include <optional>

namespace blocks 
{
  template<typename type_t>
  using vector = std::vector<type_t>;

  template<typename type_t>
  using vector2d = std::vector<std::vector<type_t>>;

  template<typename type_t>
  using native_list = std::initializer_list<type_t>;

  using string = std::string;

  template<typename type_t>
  using optional = std::optional<type_t>;

  using integer = int;
}


#endif