#ifndef __command_line_hpp__
#define __command_line_hpp__

#include <string>
#include <map>
#include <vector>
#include <any>

namespace blocks::cmdl
{
  enum class verbosity
  {
    v,
    vv,
    vvv,
    vvvv
  };

  struct command_line_params
  {
    bool compile = false;
    bool execute = false;
    bool help = false;
    bool stats = false;
    bool version = false;

    verbosity verbose = verbosity::v;

    std::string file;
  };

  struct command_line
  {
    command_line_params params;
  };

} // namespace blocks::cmdl

#include "named_type.hpp"
#include <type_traits>

namespace blocks::cmdl2
{
  using longname_t = named_type<std::string, struct longname_tag>;
  using shortname_t = named_type<std::string, struct shortname_tag>;
  using doc_t = named_type<std::string, struct doc_tag>;
  using required_t = named_type<bool, struct required_tag>;
  using valuable_t = named_type<bool, struct valuable_tag>;

  template <typename type_t>
  using default_val_t = named_type<type_t, struct default_val_tag>;

  struct argument
  {
    longname_t longname;
    shortname_t shortname;
    doc_t doc;
    required_t required;
    valuable_t valuable;
    default_val_t<std::string> default_value;
  };

  template <typename type_t>
  struct typed_argument
  {
    argument arg;
  };

  template <typename type_t>
  typed_argument<type_t> arg(
      const longname_t &lng,
      const shortname_t &sht,
      const doc_t &doc,
      const required_t &req,
      const default_val_t<type_t> &def = {})
  {
    return {
        lng, sht, doc, req,
        valuable_t(!std::is_same_v<bool, type_t>),
        default_val_t<std::string>(
            std::to_string(def.get()))};
  }

  struct specification
  {
    std::map<std::string, argument> arguments;
    std::map<std::string, argument&> shortarguments;
  };

  template <typename... types_t>
  specification specify(
      const typed_argument<types_t> &... arg)
  {
    specification spec;
    (spec.arguments.insert({arg.arg.longname.get(), arg.arg}), ...);
    (spec.shortarguments.insert({arg.arg.shortname.get(), spec.arguments.at(arg.arg.longname.get())}), ...);
    return spec;
  }

  struct parser_results
  {
    std::map<std::string, std::string> vm;
  };

  using length_t = named_type<int, struct length_tag>;
  using args_t = named_type<char**, struct args_tag>;

  parser_results parse_command_line(const specification &spec, length_t argc, args_t argv);

} // namespace blocks::cmdl2

#endif