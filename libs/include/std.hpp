#ifndef __cmdl_std_hpp__
#define __cmdl_std_hpp__

#include <string>
#include <map>
#include <vector>
#include <optional>

namespace blocks
{
  using str_t = std::string;

  template <typename... args_t>
  using vec_t = std::vector<args_t...>;

  template <typename... args_t>
  using dict_t = std::map<args_t...>;

  template <typename... args_t>
  using sdict_t = dict_t<str_t, args_t...>;

  using strs_t = vec_t<str_t>;

  template <typename type_t>
  using opt_t = std::optional<type_t>;

} // namespace blocks

#endif