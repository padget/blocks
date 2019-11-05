#include "std.hpp"
#include <iostream>

namespace blocks {
struct command_token
{
  blocks::string line;
};

struct basic_token
{
  blocks::string value;
};

blocks::vector<command_token>
tokenizes_source_to_commands(const blocks::string& source);

blocks::vector<basic_token>
tokenizes_command_to_tokens(const blocks::command_token& cmd);

blocks::vector2d<basic_token>
tokenizes_commands_to_tokens(const blocks::vector<blocks::command_token>& cmds);
}

int
main(int argc, char const* argv[])
{
  auto&& cmds = blocks::tokenizes_source_to_commands("");
  auto&& tks2d = blocks::tokenizes_commands_to_tokens(cmds);

  return 0;
}

blocks::vector<blocks::command_token>
blocks::tokenizes_source_to_commands(const blocks::string& source)
{
  blocks::vector<command_token> cmds;

  blocks::string::const_iterator begin = source.begin();
  blocks::string::const_iterator end = source.begin();
  blocks::string::const_iterator cursor = begin;

  while (cursor != end) {
    if (*cursor == '\n') {
      cmds.push_back(command_token{ blocks::string{ begin, cursor } });
      begin = cursor + 1;
    }

    cursor++;
  }

  return cmds;
}

namespace blocks {
blocks::optional<basic_token>
try_tokenize_name(blocks::string::const_iterator begin,
                  blocks::string::const_iterator end);

blocks::optional<basic_token>
try_tokenize_colon(blocks::string::const_iterator begin,
                   blocks::string::const_iterator end);

blocks::optional<basic_token>
try_tokenize_space(blocks::string::const_iterator begin,
                   blocks::string::const_iterator end);

blocks::optional<basic_token>
try_tokenize_eol(blocks::string::const_iterator begin,
                 blocks::string::const_iterator end);

blocks::optional<basic_token>
try_tokenize_eos(blocks::string::const_iterator begin,
                 blocks::string::const_iterator end);
} // namespace blocks

blocks::vector<blocks::basic_token>
blocks::tokenizes_command_to_tokens(const blocks::command_token& cmd)
{
  blocks::vector<blocks::basic_token> tokens;
  blocks::string::const_iterator begin = cmd.line.begin();
  blocks::string::const_iterator end = cmd.line.end();
  blocks::string::const_iterator cursor = begin;

  while (cursor != end) {
    {
      auto&& eos = try_tokenize_space(cursor, end);
      if (eos.has_value()) {
        tokens.push_back(eos.value());
        cursor = std::next(cursor, eos.value().value.size());
        continue;
      }
    }
    {
      auto&& space = try_tokenize_space(cursor, end);
      if (space.has_value()) {
        tokens.push_back(space.value());
        cursor = std::next(cursor, space.value().value.size());
        continue;
      }
    }
    {
      auto&& name = try_tokenize_name(cursor, end);
      if (name.has_value()) {
        tokens.push_back(name.value());
        cursor = std::next(cursor, name.value().value.size());
        continue;
      }
    }
    {
      auto&& colon = try_tokenize_colon(cursor, end);
      if (colon.has_value()) {
        tokens.push_back(colon.value());
        cursor = std::next(cursor, colon.value().value.size());
        continue;
      }
    }
    {
      auto&& eol = try_tokenize_eol(cursor, end);
      if (eol.has_value()) {
        tokens.push_back(eol.value());
        cursor = std::next(cursor, eol.value().value.size());
        continue;
      }
    }
  }

  return tokens;
}