#include "../include/blocks/command_line.hpp"
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
  parsed::argument* last = nullptr;

  for (auto&& arg : rline)
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
      if (not (last eq nullptr))
      {
        (*last).value = arg.raw;
        last = nullptr;
      }
    }
  }

  return rep;
}

void parsed::init_defaults(
  const spec::line& spec,
  parsed::report& rep)
{
  for (auto&& [name, arg]: rep.avs)
  {
    if (spec.arguments.count(name) == 1)
      if (arg.value.empty())
        arg.value = spec.arguments.at(name).default_value;
  }
}

void parsed::check_required(
    const spec::line &spec,
    report &rep)
{

}

void parsed::check_types(
    const spec::line &spec,
    report &rep)
{
}

parsed::report
parsed::parse_command_line(
    const spec::line &spec,
    const raw::line &args)
{
  parsed::report rep =
      parsed::init_report(spec);

  parsed::check_required(spec, rep);
  parsed::check_types(spec, rep);

  return rep;
}