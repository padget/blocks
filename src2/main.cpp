#include "std.hpp"
#include <iostream>

namespace blocks {
struct command_token
{
  blocks::string line;
};

struct basic_token
{
  blocks::string type;
  blocks::string value;
};

struct command
{
  blocks::string name;
  blocks::vector<blocks::string> args;
};

blocks::vector<command_token>
tokenizes_source_to_commands(const blocks::string& source);

blocks::vector<basic_token>
tokenizes_command_to_tokens(const blocks::command_token& cmd);

blocks::vector2d<basic_token>
tokenizes_commands_to_tokens(const blocks::vector<blocks::command_token>& cmds);

blocks::vector<blocks::command>
build_commands_from_tokens(const blocks::vector2d<basic_token>& cmdstok);

blocks::command
build_command_from_tokens(const blocks::vector<basic_token>& cmdtok);
}

int
main(int argc, char const* argv[])
{
  auto&& cmds = blocks::tokenizes_source_to_commands("main:\n add: 1 2");
  auto&& cmds2d = blocks::tokenizes_commands_to_tokens(cmds);
  auto&& cmds = blocks::build_commands_from_tokens(cmds2d);
  return 0;
}

blocks::vector<blocks::command_token>
blocks::tokenizes_source_to_commands(const blocks::string& source)
{
  blocks::vector<command_token> cmds;
  blocks::string::const_iterator begin = source.begin();
  blocks::string::const_iterator end = source.end();
  blocks::string::const_iterator cursor = begin;

  while (cursor != end) {
    if (*cursor == '\n') {
      cmds.push_back(command_token{ blocks::string{ begin, cursor } });
      begin = cursor + 1;
    }
    cursor++;
  }
  cmds.push_back(command_token{ blocks::string{ begin, cursor } });

  return cmds;
}

namespace blocks {
blocks::optional<blocks::basic_token>
try_tokenize_name(blocks::string::const_iterator begin,
                  blocks::string::const_iterator end);

blocks::optional<blocks::basic_token>
try_tokenize_integer(blocks::string::const_iterator begin,
                     blocks::string::const_iterator end);

blocks::optional<blocks::basic_token>
try_tokenize_colon(blocks::string::const_iterator begin,
                   blocks::string::const_iterator end);

blocks::optional<blocks::basic_token>
try_tokenize_space(blocks::string::const_iterator begin,
                   blocks::string::const_iterator end);

blocks::optional<blocks::basic_token>
try_tokenize_eol(blocks::string::const_iterator begin,
                 blocks::string::const_iterator end);

blocks::optional<blocks::basic_token>
try_tokenize_eos(blocks::string::const_iterator begin,
                 blocks::string::const_iterator end);
} // namespace blocks

blocks::vector2d<blocks::basic_token>
blocks::tokenizes_commands_to_tokens(
  const blocks::vector<blocks::command_token>& cmdstok)
{
  blocks::vector2d<blocks::basic_token> cmds;

  for (auto&& cmdtok : cmdstok)
    cmds.push_back(blocks::tokenizes_command_to_tokens(cmdtok));

  return cmds;
}

blocks::vector<blocks::basic_token>
blocks::tokenizes_command_to_tokens(const blocks::command_token& cmd)
{
  blocks::vector<blocks::basic_token> tokens;
  blocks::string::const_iterator begin = cmd.line.begin();
  blocks::string::const_iterator end = cmd.line.end();
  blocks::string::const_iterator cursor = begin;

  while (cursor != end) {
    {
      auto&& eos = blocks::try_tokenize_eos(cursor, end);
      if (eos.has_value()) {
        tokens.push_back(eos.value());
        cursor = std::next(cursor, eos.value().value.size());
        continue;
      }
    }
    {
      auto&& space = blocks::try_tokenize_space(cursor, end);
      if (space.has_value()) {
        tokens.push_back(space.value());
        cursor = std::next(cursor, space.value().value.size());
        continue;
      }
    }
    {
      auto&& name = blocks::try_tokenize_name(cursor, end);
      if (name.has_value()) {
        tokens.push_back(name.value());
        cursor = std::next(cursor, name.value().value.size());
        continue;
      }
    }
    {
      auto&& integer = blocks::try_tokenize_integer(cursor, end);
      if (integer.has_value()) {
        tokens.push_back(integer.value());
        cursor = std::next(cursor, integer.value().value.size());
        continue;
      }
    }
    {
      auto&& colon = blocks::try_tokenize_colon(cursor, end);
      if (colon.has_value()) {
        tokens.push_back(colon.value());
        cursor = std::next(cursor, colon.value().value.size());
        continue;
      }
    }
    {
      auto&& eol = blocks::try_tokenize_eol(cursor, end);
      if (eol.has_value()) {
        tokens.push_back(eol.value());
        cursor = std::next(cursor, eol.value().value.size());
        continue;
      }
    }
    // error case
    {
      tokens.push_back(
        blocks::basic_token{ "error", blocks::string(cursor, cursor + 1) });
      cursor++;
    }
  }

  return tokens;
}

blocks::optional<blocks::basic_token>
blocks::try_tokenize_name(blocks::string::const_iterator begin,
                          blocks::string::const_iterator end)
{
  blocks::string::const_iterator cursor = begin;

  while (cursor != end && 'a' <= *cursor && *cursor <= 'z')
    cursor++;

  if (cursor != begin)
    return blocks::basic_token{ "name", blocks::string{ begin, cursor } };
  else
    return std::nullopt;
}

blocks::optional<blocks::basic_token>
blocks::try_tokenize_integer(blocks::string::const_iterator begin,
                             blocks::string::const_iterator end)
{
  blocks::string::const_iterator cursor = begin;

  while (cursor != end && '0' <= *cursor && *cursor <= '9')
    cursor++;

  if (cursor != begin)
    return blocks::basic_token{ "integer", blocks::string{ begin, cursor } };
  else
    return std::nullopt;
}

blocks::optional<blocks::basic_token>
blocks::try_tokenize_colon(blocks::string::const_iterator begin,
                           blocks::string::const_iterator end)
{
  if (begin != end && *begin == ':')
    return blocks::basic_token{ "colon", blocks::string{ begin, begin + 1 } };
  else
    return std::nullopt;
}

blocks::optional<blocks::basic_token>
blocks::try_tokenize_space(blocks::string::const_iterator begin,
                           blocks::string::const_iterator end)
{
  if (begin != end && *begin == ' ')
    return blocks::basic_token{ "space", blocks::string{ begin, begin + 1 } };
  else
    return std::nullopt;
}

blocks::optional<blocks::basic_token>
blocks::try_tokenize_eol(blocks::string::const_iterator begin,
                         blocks::string::const_iterator end)
{
  if (begin != end && *begin == '\n')
    return blocks::basic_token{ "eol", blocks::string{ begin, begin + 1 } };
  else
    return std::nullopt;
}

blocks::optional<blocks::basic_token>
blocks::try_tokenize_eos(blocks::string::const_iterator begin,
                         blocks::string::const_iterator end)
{
  if (begin == end)
    return blocks::basic_token{ "eos", "" };
  else
    return std::nullopt;
}