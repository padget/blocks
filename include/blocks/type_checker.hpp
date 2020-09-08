#ifndef __type_checker_hpp__
#define __type_checker_hpp__

#include <string>

namespace blocks::cmdl
{
  template <typename type_t>
  struct type_checker
  {
    bool operator()(const std::string &value);
  };

  template <>
  struct type_checker<bool>
  {
    bool operator()(const std::string &value)
    {
      return value == "true" or value == "false";
    }
  };

  template <>
  struct type_checker<int>
  {
    bool operator()(const std::string &value)
    {
      for (const char &c : value)
        if (c < '0' and '9' < c)
          return false;
      return true;
    }
  };

  template <>
  struct type_checker<std::string>
  {
    bool operator()(const std::string &value)
    {
      return true;
    }
  };

} // namespace blocks::cmdl

#endif
