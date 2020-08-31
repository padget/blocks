#include "../include/blocks/command_line.hpp"
#include <algorithm>

namespace cmdl = blocks::cmdl;

template <>
bool cmdl::convert<std::string, bool>(
    const std::string &src)
{
  return !src.empty();
}

template <>
std::string cmdl::convert<bool, std::string>(
    const bool &src)
{
  return src ? "true" : "false";
}

template <>
std::string cmdl::convert<std::string, std::string>(
    const std::string &src)
{
  return src;
}

template <>
int cmdl::convert<std::string, int>(
    const std::string &src)
{
  return std::stoi(src);
}

template <>
std::string cmdl::convert<int, std::string>(
    const int &src)
{
  return std::to_string(src);
}

template <>
long long cmdl::convert<std::string, long long>(
    const std::string &src)
{
  return std::stoll(src.c_str());
}

template <>
std::string cmdl::convert<long long, std::string>(
    const long long &src)
{
  return std::to_string(src);
}

template <>
cmdl::argument_builder<bool>
cmdl::expect<bool>(
    const std::string &longname,
    const std::string &shortname)
{
  cmdl::argument_builder<bool> builder;

  builder.arg.longname = longname;
  builder.arg.shortname = shortname;
  builder.arg.valueable = false;
  builder.arg.default_value = "false";

  return builder;
}

cmdl::specification_builder
cmdl::specify()
{
  return {};
}

cmdl::specification_builder &
cmdl::specification_builder::arg(
    const cmdl::argument &a)
{
  specs.arguments.push_back(a);
  return *this;
}

cmdl::specification
cmdl::specification_builder::build()
{
  return specs;
}

/**
 *  PARSER
 */

const char *cmdl::technical_parser_exception::what() const throw()
{
  return "error during commandline parsing";
}

cmdl::parser_results
cmdl::parser::init_default_results()
{
  cmdl::parser_results results;

  for (const cmdl::argument &arg : specs.arguments)
    results.m[arg.longname] = arg.default_value;

  return results;
}

std::vector<std::string>
to_vector(int argc, char **argv)
{
  std::vector<std::string> args;

  for (int i = 0; i < argc; ++i)
    args.push_back(argv[i]);

  return args;
}

bool is_argument(const std::string& str)
{
  return str.rfind("--", 0) == 0;
}

bool is_value(const std::string& str)
{
  return !is_argument(str);
}

std::string extract_arg(const std::string& arg)
{
  return arg.substr(2);
}

cmdl::parser_results
cmdl::parser::parse(
    int argc, char **argv)
{
  cmdl::parser_results results = init_default_results();
  std::vector<std::string> &&args = to_vector(argc, argv);

  for (const std::string &arg : args)
  {
    if (is_argument(arg))
    {
      std::find(std::begin(specs.arguments), std::end(specs.arguments), extract_arg(arg));
      if (specs.arguments. )
      
      
    }
  }

  return results;
}

cmdl::parser
cmdl::from(
    const cmdl::specification &specs)
{
  parser p;
  p.specs = specs;
  return p;
}

cmdl::argument_builder<bool>
cmdl::abool(
    const std::string &longname,
    const std::string &shortname)
{
  return cmdl::expect<bool>(longname, shortname);
}

cmdl::argument_builder<int>
cmdl::aint(
    const std::string &longname,
    const std::string &shortname)
{
  return cmdl::expect<int>(longname, shortname);
}

cmdl::argument_builder<long long>
cmdl::allint(
    const std::string &longname,
    const std::string &shortname)
{
  return cmdl::expect<long long>(longname, shortname);
}

cmdl::argument_builder<std::string>
cmdl::astring(
    const std::string &longname,
    const std::string &shortname)
{
  return cmdl::expect<std::string>(longname, shortname);
}