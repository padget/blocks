#ifndef __libs_cmdl_cmdl_hpp__
#define __libs_cmdl_cmdl_hpp__

#include <string>
#include <vector>
#include <optional>

namespace libs::cmdl
{
  using raw_argumentst_t =
      std::vector<std::string>;

  std::vector<std::string>
  torawarguments(int argc, char **argv);

  struct argument
  {
    std::string name;
    std::string value;
  };

  std::vector<argument>
  toarguments(
      const std::vector<std::string> &raws);

  struct option
  {
    std::string name;
    std::string default_value;
    std::string possible_values;
    bool mandatory;
  };

  struct action
  {
    std::string name;
    std::vector<option> options;
  };

  struct option_description
  {
    std::string description;
  };

  struct flag_description
  {
    std::string description;
  };

  action
  act(
      const std::string &name);

  flag_description
  flag(
      const std::string &description);

  option_description
  opt(
      const std::string &description);

  std::optional<option>
  to_option(
      const flag_description &flg);

  std::optional<option>
  to_option(
      flag_description &&flg);

  std::optional<option>
  to_option(
      const option_description &opt);

  std::optional<option>
  to_option(
      option_description &&opt);

  void add_option(
      action &act,
      const option &opt);

  void add_option(
      action &act,
      option &&opt);

  template <typename... opts_t>
  action
  specify(
      const std::string &name,
      opts_t &&... opt);
} // namespace libs::cmdl

template <typename... opts_t>
libs::cmdl::action
libs::cmdl::specify(
    const std::string &name,
    opts_t &&... opt)
{
  libs::cmdl::action act{name};
  (libs::cmdl::add_option(
       act,
       libs::cmdl::to_option(
           static_cast<opts_t &&>(opt))
           .value()),
   ...);

  return act;
}

namespace libs::cmdl
{
  using strings_t = std::vector<std::string>;

  struct param
  {
    std::string name;
    std::string value;
  };

  using params_t = std::vector<param>;

  struct report
  {
    bool bad_action = false;
    strings_t not_present;
    strings_t bad_value;
    strings_t unknown;

    params_t params;
  };

  report
  parse(
      const action &act,
      int argc,
      char **argv);

  // template <typename type_t>
  // type_t
  // get(
  //     const report &rep,
  //     const std::string &name);

  template <typename type_t>
  type_t
  get_all(const report &rep);
} // namespace libs::cmdl

// libs::cmdl::report
// libs::cmdl::parse(
//     const libs::cmdl::action &act,
//     int argc, char **argv)
// {
//   return {};
// }

// template <>
// int libs::cmdl::get<int>(
//     const libs::cmdl::report &rep,
//     const std::string &name)
// {
//   return {};
// }

#endif