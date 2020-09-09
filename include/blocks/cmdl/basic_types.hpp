#ifndef __cmdl_basic_types_hpp__
#define __cmdl_basic_types_hpp__

#include "std.hpp"

namespace blocks::cmdl::specification
{
  template<typename type_t>
  struct type_wrapper
  {
    str_t to_string(const type_t& t);
    bool check_type(const str_t& s);
  };

  template<>
  struct type_wrapper<bool>
  {
    str_t to_string(const bool& t)
    {
      return t ? "true" : "false";
    }


  }
}



#endif