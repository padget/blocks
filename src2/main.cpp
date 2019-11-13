#include "types.hpp"
#include <iostream>

namespace blocks {

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

blocks::vector<blocks::command>
build_hierarchical_commands(const blocks::vector<blocks::command>& cmds);

int
execute(const blocks::vector<command>& commands);
}

namespace blocks::check {
blocks::vector<const blocks::command*>
find_duplicated_command_names(const blocks::vector<blocks::command>& cmds);

blocks::vector<const blocks::command*>
find_undefined_commands(const blocks::vector<blocks::command>& cmds);

bool
check_all(const blocks::vector<command>& cmds);
}

namespace blocks::context {
struct global_context
{
  blocks::vector<blocks::command> commands;
};

struct main_context
{
  blocks::vector<command_definition> cdefs;
};

blocks::context::global_context
build_global_context();

int
add(int a, int b);

int
minus(int a, int b);

int
multiply(int a, int b);

int
divide(int a, int b);

bool
print(const std::string& str);
}

int
main(int argc, char const* argv[])
{
  auto&& cmdstok =
    blocks::tokenizes_source_to_lines("main: a#int b#int\n  add: a b\n");
  auto&& cmds2d = blocks::tokenizes_lines_to_tokens(cmdstok);
  auto&& cmds = blocks::build_commands_from_tokens(cmds2d);

  bool checked = blocks::check::check_all(cmds);

  if (!checked) {
    std::cout << "there is/are some error(s)\n";
    return EXIT_FAILURE;
  }

  blocks::execute(cmds);

  return 0;
}

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

blocks::optional<blocks::basic_token>
try_tokenize_dieze(blocks::string::const_iterator begin,
                   blocks::string::const_iterator end);

} // namespace blocks

blocks::vector2d<blocks::basic_token>
blocks::tokenizes_lines_to_tokens(
  const blocks::vector<blocks::line_token>& linestok)
{
  blocks::vector2d<blocks::basic_token> lines;

  for (auto&& linetok : linestok)
    lines.push_back(blocks::tokenizes_line_to_tokens(linetok));

  return lines;
}

blocks::vector<blocks::basic_token>
blocks::tokenizes_line_to_tokens(const blocks::line_token& line)
{
  blocks::vector<blocks::basic_token> tokens;
  blocks::string::const_iterator begin = line.line.begin();
  blocks::string::const_iterator end = line.line.end();
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
      auto&& dieze = blocks::try_tokenize_dieze(cursor, end);
      if (dieze.has_value()) {
        tokens.push_back(dieze.value());
        cursor = std::next(cursor, dieze.value().value.size());
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

blocks::optional<blocks::basic_token>
blocks::try_tokenize_dieze(blocks::string::const_iterator begin,
                           blocks::string::const_iterator end)
{
  if (begin != end && *begin == '#')
    return blocks::basic_token{ "dieze", blocks::string{ begin, begin + 1 } };
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

  cmd.depth = depth;

  /* nom de la commande suivi d'un colon */
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

blocks::vector<blocks::command>
build_hierarchical_commands(const blocks::vector<blocks::command>& cmds)
{
  blocks::vector<blocks::command> hcmds;
  auto begin = cmds.begin();
  auto end = cmds.end();
  size_t depth = 0;
  const blocks::command* current = nullptr;

  while (begin != end) {
    current = &*begin;
    if (current->depth == 0) {
      hcmds.push_back(*current);
    } else {
      hcmds.back().cmds.push_back(*current);
    }
  }
}

namespace blocks::check {
constexpr bool no_problem = true;
constexpr bool with_error = false;
}

bool
blocks::check::check_all(const blocks::vector<blocks::command>& cmds)
{
  auto&& duplicated = blocks::check::find_duplicated_command_names(cmds);
  auto&& undefined = blocks::check::find_undefined_commands(cmds);

  if (duplicated.size() == 0 && undefined.size() == 0)
    return blocks::check::no_problem;
  else
    return blocks::check::with_error;
}

blocks::vector<const blocks::command*>
blocks::check::find_duplicated_command_names(
  const blocks::vector<blocks::command>& cmds)
{
  blocks::vector<const blocks::command*> duplications;

  for (auto&& cmd : cmds)
    for (auto&& cmd2 : cmds)
      if (cmd.depth == 0 and cmd2.depth == 0 and &cmd != &cmd2 and
          cmd.name == cmd2.name)
        duplications.push_back(&cmd);

  return duplications;
}

blocks::vector<const blocks::command*>
blocks::check::find_undefined_commands(
  const blocks::vector<blocks::command>& cmds)
{
  blocks::vector<const blocks::command*> undefined;
  blocks::vector<const blocks::command*> defined;

  auto&& gctx = blocks::context::build_global_context();

  for (auto&& cmd : cmds)
    if (cmd.depth == 0)
      defined.push_back(&cmd);

  for (auto&& cmd : gctx.commands)
    defined.push_back(&cmd);

  for (auto&& cmd : cmds)
    if (cmd.depth > 0) {
      bool found = false;

      for (auto&& definition : defined)
        if (definition->name == cmd.name)
          found = true;

      if (!found)
        undefined.push_back(&cmd);
    }

  return undefined;
}

blocks::context::global_context
blocks::context::build_global_context()
{
  blocks::context::global_context gctx;
  gctx.commands.push_back(command{ 0, "add", { "a", "b" } });
  gctx.commands.push_back(command{ 0, "minus", { "a", "b" } });
  gctx.commands.push_back(command{ 0, "multiply", { "a", "b" } });
  gctx.commands.push_back(command{ 0, "divide", { "a", "b" } });
  return gctx;
}

int
blocks::context::add(int a, int b)
{
  return a + b;
}

int
blocks::context::minus(int a, int b)
{
  return a - b;
}

int
blocks::context::multiply(int a, int b)
{
  return a * b;
}

int
blocks::context::divide(int a, int b)
{
  return a / b;
}

namespace blocks {
const blocks::command&
main_command(const blocks::vector<blocks::command>& cmds);

void
print_main_arguments(const blocks::vector<blocks::string>& args);

blocks::vector<blocks::command>
subcommands(const blocks::command& cmain);
}

int
blocks::execute(const blocks::vector<blocks::command>& cmds)
{
  const blocks::command& cmain = blocks::main_command(cmds);
  // const blocks::vector<command> cmaincmds = blocks::subcommands(cmain);

  blocks::print_main_arguments(cmain.args);
  // for (auto&& cmd : cmaincmds)
  ;

  return EXIT_SUCCESS;
}

const blocks::command&
blocks::main_command(const blocks::vector<blocks::command>& cmds)
{
  // le vecteur donné à cette fonction doit forcément contenir la commande main.
  const blocks::command* cmain;
  for (auto&& cmd : cmds)
    if (cmd.name == "main" && cmd.depth == 0)
      cmain = &cmd;
  return *cmain;
}

void
blocks::print_main_arguments(const blocks::vector<blocks::string>& args)
{
  for (auto&& arg : args)
    std::cout << arg << " ";
  std::cout << "\n";
}