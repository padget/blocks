#include "cmdl.hpp"
#include <algorithm>

std::vector<std::string>
libs::cmdl::torawarguments(
    int argc, char **argv)
{
  std::vector<std::string> args;
  for (int i = 0; i < argc; ++i)
    args.push_back(argv[i]);
  return args;
}

namespace
{
  std::array<std::string, 2>
  split2(
      const std::string &s,
      const char delim)
  {
    std::array<std::string, 2> res;

    auto b = s.begin();
    auto e = s.end();
    auto it = std::find(b, e, delim);

    res[0] = std::string(b, it);
    res[1] = std::string(it == e ? it : it + 1, e);

    return res;
  }

  // std::vector<std::string>
  // split(
  //     const std::string &s,
  //     const char delim)
  // {
  //   std::vector<std::string> res;

  //   auto b = s.begin();
  //   auto e = s.end();

  //   while (b not_eq e)
  //   {
  //     auto it = find(b, e, delim);

  //     if (it != e)
  //       res.push_back(std::string(b, it));

  //     b = it + 1;
  //   }

  //   return res;
  // }
} // namespace

std::vector<libs::cmdl::argument>
libs::cmdl::toarguments(
    const std::vector<std::string> &rargs)
{
  std::vector<libs::cmdl::argument> args;

  for (const std::string &rarg : rargs)
  {
    auto &&[name, val] = split2(rarg, '=');
    args.push_back(argument{name, val});
  }

  return args;
}

libs::cmdl::action
libs::cmdl::act(
    const std::string &name)
{
  libs::cmdl::action a;
  a.name = name;
  return a;
}

libs::cmdl::flag_description
libs::cmdl::flag(
    const std::string &desc)
{
  libs::cmdl::flag_description f;
  f.description = desc;
  return f;
}

libs::cmdl::option_description
libs::cmdl::opt(
    const std::string &desc)
{
  libs::cmdl::option_description o;
  o.description = desc;
  return o;
}

namespace
{
  bool islower(
      char c)
  {
    return 'a' <= c and c <= 'z';
  }

  bool onlylower(
      const std::string &s)
  {
    auto b = s.begin();
    auto e = s.end();

    return std::all_of(b, e, islower);
  }

  enum class opcl
  {
    both,
    one,
    none
  };

  opcl isopcl(
      const std::string &s,
      char open, char close)
  {
    auto b = s.begin();
    auto e = s.end();

    if (s.empty())
      return opcl::none;

    bool opened = *b == open;
    bool closed = *(e - 1) == close;

    if (opened and closed)
      return opcl::both;
    else if (opened or closed)
      return opcl::one;
    else
      return opcl::none;
  }

  std::string inopcl(
      const std::string s)
  {
    auto b = s.begin();
    auto e = s.end();
    return std::string(b + 1, e - 1);
  }

  std::optional<libs::cmdl::option>
  __to_option(
      const std::string &description,
      const bool simple)
  {
    std::string desc = description;
    libs::cmdl::option o;

    switch (isopcl(desc, '[', ']'))
    {
    case opcl::both:
      desc = inopcl(desc);
      o.mandatory = false;
      break;
    case opcl::none:
      o.mandatory = true;
      break;
    case opcl::one:
      return std::nullopt;
    }

    auto &&[first, second] = split2(desc, '=');

    if (not onlylower(first))
      return std::nullopt;
    else
      o.name = first;

    if (simple and not second.empty())
      return std::nullopt;

    switch (isopcl(second, '<', '>'))
    {
    case opcl::both:
      o.possible_values = inopcl(second);
      break;
    case opcl::none:
    case opcl::one:
      return std::nullopt;
    }

    return o;
  }
} // namespace

std::optional<libs::cmdl::option>
libs::cmdl::to_option(
    const libs::cmdl::flag_description &flg)
{
  return __to_option(flg.description, true);
}

std::optional<libs::cmdl::option>
libs::cmdl::to_option(
    libs::cmdl::flag_description &&flg)
{
  return __to_option(flg.description, true);
}

std::optional<libs::cmdl::option>
libs::cmdl::to_option(
    const libs::cmdl::option_description &opt)
{
  return __to_option(opt.description, false);
}

std::optional<libs::cmdl::option>
libs::cmdl::to_option(
    libs::cmdl::option_description &&opt)
{
  return __to_option(opt.description, false);
}

void libs::cmdl::add_option(
    libs::cmdl::action &act,
    const libs::cmdl::option &opt)
{
  act.options.push_back(opt);
}

void libs::cmdl::add_option(
    libs::cmdl::action &act,
    libs::cmdl::option &&opt)
{
  act.options.push_back(opt);
}
