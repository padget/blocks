#include "cmdl.hpp"
#include <algorithm>

using namespace libs;
using namespace libs::cmdl;
using namespace std;

action act(
    const string &name)
{
  return {.name = name};
}

flag_description flag(
    const string &description)
{
  return {.description = description};
}

option_description opt(
    const string &description)
{
  return {.description = description};
}

enum class brace_frame
{
  both,
  one,
  none
};

brace_frame
braces_framed(
    const string &desc)
{
  if (desc.empty())
    return brace_frame::none;

  char front = desc.front();
  char back = desc.back();

  bool nobraces =
      front != '[' and
      back != ']';

  bool bothbraces =
      front == '[' and
      back == ']';

  bool onebrace =
      not bothbraces and
      not nobraces;

  if (nobraces)
    return brace_frame::none;
  else if (bothbraces)
    return brace_frame::both;
  else
    return brace_frame::one;
}

optional<option> to_option(
    const flag_description &flg)
{
  if (flg.description.empty())
    return nullopt;

  char front = flg.description.front();
  char back = flg.description.back();

  bool nobraces =
      front != '[' and
      back != ']';

  bool bothbraces =
      front == '[' and
      back == ']';

  bool onebrace =
      not bothbraces and
      not nobraces;

  if (onebrace)
    return nullopt;

  auto bname = flg.description.begin();
  auto ename = flg.description.end();

  if (bothbraces) // optional flag
  {
    bname++;
    ename--;
  }

  auto is_letter = [](char c) {
    return 'a' <= c and c <= 'z';
  };

  if (all_of(bname, ename, is_letter))
  {
    option opt;
    opt.mandatory = nobraces;
    opt.name = string(bname, ename);
    return opt;
  }

  return nullopt;
}

optional<option>
to_option(
    flag_description &&flg)
{
}

optional<option>
to_option(
    const option_description &opt)
{
}

optional<option>
to_option(
    option_description &&opt)
{
}

void add_option(
    action &act,
    const option &opt)
{
  libs::push(act.options, opt);
}

void add_option(
    action &act,
    option &&opt)
{
  libs::push(act.options, opt);
}
