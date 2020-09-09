#include "../include/blocks/cmdl/command_line.hpp"
#include <optional>
#include <algorithm>

namespace cmdl = blocks::cmdl;

namespace raw = cmdl::raw;

bool raw::is_argument(
    const raw::argument &arg)
{
  return arg.raw.rfind("--", 0) == 0;
}

bool raw::is_value(
    const raw::argument &arg)
{
  return not is_argument(arg);
}

raw::line
raw::from_cmdl(
    int argc, char **argv)
{
  raw::line args;

  for (int i = 0; i < argc; ++i)
    args.push_back(raw::argument{argv[i]});

  return args;
}

namespace parsed = cmdl::parsed;
namespace spec = cmdl::specification;

parsed::report parsed::init_report(
    const raw::line &rline)
{
  parsed::report rep;
  parsed::argument *last = nullptr;

  for (auto &&arg : rline)
  {
    if (raw::is_argument(arg))
    {
      parsed::argument parg;
      parg.name = arg.raw;
      rep.avs.insert({parg.name, parg});
      last = &rep.avs.at(parg.name);
    }
    else if (raw::is_value(arg))
    {
      if (not(last == nullptr))
      {
        (*last).value = arg.raw;
        last = nullptr;
      }
    }
  }

  return rep;
}

void parsed::init_defaults(
    const spec::line &spec,
    parsed::report &rep)
{
  for (auto &&[name, arg] : spec.arguments)
    if (rep.avs.count(name) == 1)
    {
      str_t &value = rep.avs.at(name).value;

      if (not arg.default_value.empty() and value.empty())
        value = arg.default_value;
    }
    else
    {
      if (not arg.default_value.empty())
      {
        rep.avs.insert({name,
                        parsed::argument{name, arg.default_value}});
      }
    }
}

#include <iostream>

void parsed::check_required(
    const spec::line &spec,
    report &rep)
{
  for (auto &&[name, arg] : spec.arguments)
    if (arg.required)
    {
      std::cout << name << " required \n";
      if (rep.avs.count(name) == 0)
      {
        std::cout << name << "not found\n";
        rep.not_presents.push_back(name);
      }
    }
}

void parsed::check_types(
    const spec::line &spec,
    report &rep)
{
  for (auto &&[name, arg] : rep.avs)
    if (spec.arguments.count(name))
      if (not spec.arguments.at(name).type_check(arg.value))
        rep.bad_value_types.push_back(name);
}

parsed::report
parsed::parse_command_line(
    const spec::line &spec,
    const raw::line &args)
{
  parsed::report rep =
      parsed::init_report(args);

  parsed::init_defaults(spec, rep);
  parsed::check_required(spec, rep);
  parsed::check_types(spec, rep);

  return rep;
}

// Externaliser cette fonction ainsi que
// cmdl::params et cmdl::verbosity dans un
// autre fichier dans lequelle on va aussi
// definir les specifications du programme.

// Ce fichier est plutot une API !

cmdl::params
cmdl::convert(
    const parsed::report &rep)
{
  cmdl::params parms;
  bool no_bt = rep.bad_value_types.empty();
  bool no_np = rep.not_presents.empty();

  if (no_bt and no_np)
  {
    parms.compile = rep.avs.at("--compile").value == "true";
  }

  return parms;
}