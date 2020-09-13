#ifndef __command_line_hpp__
#define __command_line_hpp__

#include <iostream>
#include <functional>

#include "../std.hpp"
#include "basic_types.hpp"

namespace blocks::cmdl::raw
{
  template <typename string_t>
  struct argument
  {
    string_t raw;
  };

  template <typename string_t>
  using line = vec_t<argument<string_t>>;

  template <typename string_t>
  line<string_t> from_cmdl(int argc, char **argv);

  template <typename string_t>
  bool is_argument(const argument<string_t> &raw);

  template <typename string_t>
  bool is_value(const argument<string_t> &raw);
} // namespace blocks::cmdl::raw

namespace blocks::cmdl::specification
{
  template <typename string_t>
  using type_checker_f_t = bool(const string_t &);

  template <typename string_t>
  using type_checker_t = std::function<type_checker_f_t<string_t>>;

  template <typename string_t>
  struct argument
  {
    string_t longname;
    string_t doc;
    bool required;
    string_t default_value;
    type_checker_t<string_t> type_check;
  };

  template <
      typename type_t,
      typename string_t>
  struct typed_argument
  {
    argument<string_t> arg;
  };

  template <
      typename type_t,
      typename string_t>
  typed_argument<type_t, string_t> arg(
      const string_t &lng,
      const string_t &doc,
      bool required,
      const opt_t<type_t> &def = std::nullopt)
  {
    string_t &&dval = def.has_value() ? to_string(def.value()) : "";
    return {lng, doc, true, dval, &str_convertible<type_t>};
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
  template <typename target_t>
  target_t convert(const parsed::report &rep);
}

#endif