#include "../include/blocks/command_line.hpp"
#include <algorithm>
#include <optional>

namespace cmdl2 = blocks::cmdl2;

bool is_argument(const std::string &str)
{
  return str.rfind("--", 0) == 0;
}

bool is_value(const std::string &str)
{
  return !is_argument(str);
}

std::string
extract_arg(
    const std::string &str)
{
  return str.substr(2);
}

std::vector<std::string>
to_vector(
    cmdl2::length_t argc,
    cmdl2::args_t argv)
{
  std::vector<std::string> args;

  for (int i = 0; i < argc.get(); i++)
    args.push_back(argv.get()[i]);

  return args;
}

cmdl2::parser_results
init_parser_results(
    cmdl2::length_t len,
    cmdl2::args_t args)
{
  cmdl2::parser_results res;

  auto argsv = to_vector(len, args);
  std::string lastarg;

  for (auto &&arg : argsv)
  {
    if (is_argument(arg))
    {
      lastarg = extract_arg(arg);
      res.vm[lastarg] = "";
    }
    else
    {
      res.vm[lastarg] = arg;
      lastarg = "";
    }
  }

  return res;
}

bool inspec(
    const cmdl2::specification &spec,
    const std::string &arg)
{
  return spec.arguments.count(arg) == 1 or
         spec.shortarguments.count(arg) == 1;
}

const cmdl2::argument &
arg_from_spec(
    const cmdl2::specification &spec,
    const std::string &argname)
{
  return spec.arguments.count(argname) == 1
             ? spec.arguments.at(argname)
             : spec.shortarguments.at(argname);
}

const std::string &
default_from_spec(
    const cmdl2::specification &spec,
    const std::string &argname)
{
  return arg_from_spec(spec, argname)
      .default_value.get();
}

bool check_no_unknown_arg(
    const cmdl2::specification &spec,
    const cmdl2::parser_results &res)
{
  bool no_unknown_arg = true;

  for (auto &&argres : res.vm)
  {
    if (no_unknown_arg)
      no_unknown_arg = no_unknown_arg and
                       inspec(spec, argres.first);
    else
      break;
  }

  return no_unknown_arg;
}

void fill_default_value_if_needed(
    const cmdl2::specification &spec,
    cmdl2::parser_results &res)
{
  for (auto &arg : res.vm)
  {
    if (arg.second.empty())
      arg.second = default_from_spec(spec, arg.first);
  }
}

cmdl2::parser_results
cmdl2::parse_command_line(
    const cmdl2::specification &spec,
    cmdl2::length_t argc,
    cmdl2::args_t argv)
{
  cmdl2::parser_results &&res =
      init_parser_results(argc, argv);

  check_no_unknown_arg(spec, res);
  fill_default_value_if_needed(spec, res);
  
  for (auto &&argv : res.vm)
  {
    if (inspec(spec, argv.first))
    {
      const cmdl2::argument &arg =
          arg_from_spec(spec, argv.first);
    }
  }

  return res;
}