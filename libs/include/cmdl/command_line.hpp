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
  struct typed_argument_builder
  {
  private:
    typed_argument<type_t, string_t> built;
    using tab = typed_argument_builder;

  public:
    tab &name(const string_t &name);
    tab &doc(const string &doc);
    tab &required();
    tab &not_required();
    tab &default_value(const std::optional<type_t> &v);
    typed_argument<type_t, string_t> get();
  };

  template <
      typename type_t,
      typename string_t>
  typed_argument<type_t, string_t>
  optional_arg(
      const str_t &name,
      const str_t &doc,
      const opt_t<type_t> &def = std::nullopt)
  {
    typed_argument_builder<type_t, string_t> builder;
    return builder
        .name(name)
        .doc(doc)
        .default_value(def)
        .not_required()
        .get();
  }

  template <typename type_t>
  typed_argument<type_t>
  required_arg(
      const str_t &lng,
      const str_t &doc,
      const opt_t<type_t> &def = std::nullopt)
  {
    typed_argument_builder<type_t, string_t> builder;
    return builder
        .name(name)
        .doc(doc)
        .default_value(def)
        .required()
        .get();
  }

  template <typename string_t>
  using sdict_arg_t = sdict_t<argument<string_t>>;

  template <typename string_t>
  struct line
  {
    sdict_arg_t<string_t> arguments;
  };

  template <typename string_t, typename... types_t>
  line<string_t> specify(
      const string_t &prefix,
      const typed_argument<types_t, string_t> &... arg)
  {
    line<string_t> spec;
    (spec.arguments.insert(
         {prefix + arg.arg.longname, arg.arg}),
     ...);
    return spec;
  }

} // namespace blocks::cmdl::specification

namespace blocks::cmdl::parsed
{
  template <typename string_t>
  struct argument
  {
    string_t name;
    string_t value;
  };

  template <typename string_t>
  struct report
  {
    sdict_t<argument<string_t>> avs;
    strs_t not_presents;
    strs_t bad_value_types;
  };

  template <typename string_t>
  report<string_t> init_report(
      const raw::line<string_t> &rline);

  template <typename string_t>
  void init_defaults(
      const specification::line<string_t> &spec,
      report<string_t> &rep);

  template <typename string_t>
  void check_required(
      const specification::line<string_t> &spec,
      report<string_t> &rep);

  template <typename string_t>
  void check_types(
      const specification::line<string_t> &spec,
      report<string_t> &rep);

  template <typename string_t>
  report<string_t>
  parse_command_line(
      const specification::line<string_t> &spec,
      const raw::line<string_t> &args);

} // namespace blocks::cmdl::parsed

namespace blocks::cmdl
{
  template <typename target_t, typename string_t>
  target_t convert(const parsed::report<string_t> &rep);
}

#endif