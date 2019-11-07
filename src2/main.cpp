#include "std.hpp"
#include <iostream>

namespace blocks {
struct line_token
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
  blocks::integer depth;
  blocks::string name;
  blocks::vector<blocks::string> args;
};

blocks::vector<line_token>
tokenizes_source_to_lines(const blocks::string& source);

blocks::vector<basic_token>
tokenizes_line_to_tokens(const blocks::line_token& line);

blocks::vector2d<basic_token>
tokenizes_lines_to_tokens(const blocks::vector<blocks::line_token>& lines);

blocks::vector<blocks::command>
build_commands_from_tokens(const blocks::vector2d<basic_token>& cmdstok);

blocks::optional<blocks::command>
try_build_command_from_tokens(const blocks::vector<basic_token>& cmdtok);
}

int
main(int argc, char const* argv[])
{
  auto&& cmdstok = blocks::tokenizes_source_to_lines("main: \nadd: 1 2");
  auto&& cmds2d = blocks::tokenizes_lines_to_tokens(cmdstok);
  auto&& cmds = blocks::build_commands_from_tokens(cmds2d);

  std::cout << cmds.size() << "\n";
  for (auto&& cmd : cmds) {
    std::cout << cmd.name << ":";
    for (auto&& arg : cmd.args)
      std::cout << " " << arg;
    std::cout << "\n";
  }
  return 0;
}
//22117655425152 vendredi
//22150940518678 lundi

blocks::vector<blocks::line_token>
blocks::tokenizes_source_to_lines(const blocks::string& source)
{
  blocks::vector<line_token> cmds;
  blocks::string::const_iterator begin = source.begin();
  blocks::string::const_iterator end = source.end();
  blocks::string::const_iterator cursor = begin;

  while (cursor != end) {
    bool is_endline = *cursor == '\n';
    if (is_endline) {
      /* On ignore le passage à la ligne et
         on saute au caractère suivant */
      cmds.push_back(line_token{ blocks::string{ begin, cursor } });
      begin = cursor + 1;
    }
    cursor++;
  }

  /* Au cas où le fichier ne termine pas sur un saut de ligne alors on */
  cmds.push_back(line_token{ blocks::string{ begin, cursor } });

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
blocks::tokenizes_lines_to_tokens(
  const blocks::vector<blocks::line_token>& cmdstok)
{
  blocks::vector2d<blocks::basic_token> cmds;

  for (auto&& cmdtok : cmdstok)
    cmds.push_back(blocks::tokenizes_line_to_tokens(cmdtok));

  return cmds;
}

blocks::vector<blocks::basic_token>
blocks::tokenizes_line_to_tokens(const blocks::line_token& cmd)
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

blocks::vector<blocks::command>
blocks::build_commands_from_tokens(
  const blocks::vector2d<blocks::basic_token>& cmdstok)
{
  blocks::vector<blocks::command> cmds;

  for (auto&& cmdtok : cmdstok) {
    auto&& cmd = try_build_command_from_tokens(cmdtok);

    if (cmd.has_value())
      cmds.push_back(cmd.value());
  }

  return cmds;
}

blocks::optional<blocks::command>
blocks::try_build_command_from_tokens(
  const blocks::vector<blocks::basic_token>& cmdtok)
{
  blocks::command cmd;
  blocks::vector<blocks::basic_token>::const_iterator begin = cmdtok.begin();
  blocks::vector<blocks::basic_token>::const_iterator end = cmdtok.end();
  blocks::vector<blocks::basic_token>::const_iterator cursor = begin;
  /* profondeur de la commande */
  blocks::integer depth = 0;
  while (cursor != end && (*cursor).type == "space") {
    cursor++;
    depth++;
  }

  /* nom de la commande */
  if (cursor != end && (*cursor).type == "name") {
    cmd.name = (*cursor).value;
    cursor++;

    if (cursor != end && (*cursor).type == "colon")
      cursor++;
    else
      return std::nullopt;
  } else
    return std::nullopt;

  /* arguments de la commande */
  while (cursor != end) {
    while (cursor != end && (*cursor).type == "space")
      cursor++;

    bool not_end = cursor != end;
    bool is_name = not_end && (*cursor).type == "name";
    bool is_integer = not_end && (*cursor).type == "integer";

    if (is_name or is_integer)
      cmd.args.push_back((*cursor).value);
    else if (not_end) {
      return std::nullopt;
    } else
      return cmd;

    cursor++;
  }

  return cmd;
}