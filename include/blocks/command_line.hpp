#ifndef __command_line_hpp__
#define __command_line_hpp__

#include <string>
#include <map>
#include <vector>
#include <optional>
#include <functional>
#include <type_traits>

#include "named_type.hpp"
#include "type_checker.hpp"

#include <iostream>

namespace blocks::cmdl
{
  enum class verbosity
  {
    v,
    vv,
    vvv,
    vvvv
  };

  struct params
  {
    bool compile = false;
    bool execute = false;
    bool help = false;
    bool stats = false;
    bool version = false;

    verbosity verbose = verbosity::v;

    std::string file;
  };
} // namespace blocks::cmdl

namespace std
{
  namespace cmdl = blocks::cmdl;

  inline string
  to_string(const cmdl ::verbosity &v)
  {
    switch (v)
    {
    case cmdl::verbosity::v:
      return "v";
    case cmdl::verbosity::vv:
      return "vv";
    case cmdl::verbosity::vvv:
      return "vvv";
    case cmdl::verbosity::vvvv:
      return "vvvv";
    default:
      return "";
    }
  }
} // namespace std

namespace blocks::cmdl
{
  template <>
  struct type_checker<verbosity>
  {
    bool operator()(const std::string &v)
    {
      return v == "v" or
             v == "vv" or
             v == "vvv" or
             v == "vvvv";
    }
  };

} // namespace blocks::cmdl

namespace blocks::cmdl
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

} // namespace blocks::cmdl

namespace blocks::cmdl::raw
{
  struct argument
  {
    str_t raw;
  };

  using line = vec_t<argument>;

  line from_cmdl(int argc, char **argv);

  bool is_argument(const argument &raw);
  bool is_value(const argument &raw);

} // namespace blocks::cmdl::raw

namespace std
{
  inline string
  to_string(bool __val)
  {
    return __val ? "true" : "false";
  }
} // namespace std

namespace blocks::cmdl::specification
{
  using type_checker_f_t = bool(const std::string &);
  using type_checker_t = std::function<type_checker_f_t>;

  struct argument
  {
    std::string longname;
    std::string doc;
    bool required;
    std::string default_value;
    type_checker_t type_check;
  };

  template <typename type_t>
  struct typed_argument
  {
    argument arg;
  };

  template <typename type_t>
  typed_argument<type_t> arg(
      const str_t &lng,
      const str_t &doc,
      bool required,
      const opt_t<type_t> &def = std::nullopt)
  {
    constexpr type_checker<type_t> tc;

    str_t &&dval = def.has_value() ? std::to_string(def.value()) : "";
    std::cout << "default value " << dval << std::endl;
    return {lng, doc, true, dval, tc};
  }

  template <typename type_t>
  typed_argument<type_t>
  optional_arg(
      const str_t &lng,
      const str_t &doc,
      const opt_t<type_t> &def = std::nullopt)
  {
    return arg(lng, doc, false, def);
  }

  template <typename type_t>
  typed_argument<type_t>
  required_arg(
      const str_t &lng,
      const str_t &doc,
      const opt_t<type_t> &def = std::nullopt)
  {
    return arg(lng, doc, true, def);
  }

  using sdict_arg_t = sdict_t<argument>;

  struct line
  {
    sdict_arg_t arguments;
  };

  template <typename... types_t>
  line specify(
      const std::string &prefix,
      const typed_argument<types_t> &... arg)
  {
    line spec;
    (spec.arguments.insert(
         {prefix + arg.arg.longname, arg.arg}),
     ...);
    return spec;
  }

} // namespace blocks::cmdl::specification

namespace blocks::cmdl::parsed
{
  struct argument
  {
    str_t name;
    str_t value;
  };

  struct report
  {
    sdict_t<argument> avs;
    strs_t not_presents;
    strs_t bad_value_types;
  };

  report init_report(
      const raw::line &rline);

  void init_defaults(
      const specification::line &spec,
      report &rep);

  void check_required(
      const specification::line &spec,
      report &rep);

  void check_types(
      const specification::line &spec,
      report &rep);

  report
  parse_command_line(
      const specification::line &spec,
      const raw::line &args);

} // namespace blocks::cmdl::parsed

namespace blocks::cmdl
{
  cmdl::params
  convert(
      const parsed::report &rep);
}

#endif