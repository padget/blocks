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

#endif