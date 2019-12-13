#include "parser.hpp"

#include <optional>
#include <variant>
#include <iostream>

struct error
{
  std::string message;
};

template<typename type>
using result = std::variant<error, std::optional<type>>;


struct argument_tracker
{
  std::optional<error> err;
  std::optional<blocks::argument> arg;
  std::optional<blocks::token_citerator> it;
};


struct command_tracker
{
  std::optional<error> err;
  std::optional<blocks::command> cmd;
};


argument_tracker
parse_argument(
               blocks::token_citerator begin,
               blocks::token_citerator eol)
{

  if (begin == eol)
  {
    return {};
  }

  auto&& tk = *begin;

  if (tk.type == blocks::token_type::ARGNAME
      or tk.type == blocks::token_type::ARGNUMBER
      or tk.type == blocks::token_type::ARGSTRING
      or tk.type == blocks::token_type::ARG$$)
  {
    blocks::argument arg;

    arg.value = std::string{tk.begin, tk.end};
    begin++;

    if (begin != eol)
    {
      auto&& tk2 = *begin;
      if (tk2.type == blocks::token_type::ARGTYPE)
      {
        begin++;
        arg.type = std::string{tk2.begin, tk2.end};
      }
    }

    return argument_tracker{std::nullopt, arg, begin};
  }

  return argument_tracker{
    error{"we must have an argument here"},
      std::nullopt,
      std::nullopt};
}


command_tracker
parse_command(
              blocks::token_citerator begin,
              blocks::token_citerator eol)
{

  if (begin == eol)
  {
    return {};
  }

  blocks::command cmd;

  if ((*begin).type == blocks::token_type::CMDNAME)
  {
    auto&& name = *begin;
    cmd.name = {name.begin, name.end};
    begin++;
  }
  else
  {
    return command_tracker {
      error{"we must have a command name here"},
        std::nullopt
    };
  }


  while (begin != eol)
  {
    blocks::argument arg;

    auto&& tk = *begin;
    if (tk.type == blocks::token_type::EOL)
    {
      break;
    }

    if (tk.type == blocks::token_type::BLANK)
    {
      begin++;
      continue;
    }

    auto&& argt = parse_argument(begin, eol);

    if (argt.err.has_value())
    {
      return command_tracker{
        error{"une erreur est survenu lors de l'inspection des arguments"},
          std::nullopt
      };
    }
    else
    {
      if (argt.arg.has_value())
      {
        cmd.args.push_back(argt.arg.value());
        begin = argt.it.value();
      }
    }
  }

  return {std::nullopt, cmd};
}

blocks::commands
blocks::parse_commands(
                       blocks::token_citerator begin,
                       blocks::token_citerator end)
{
  struct line
  {
    blocks::token_citerator begin;
    blocks::token_citerator eol;
  };

  using lines = std::vector<line>;

  lines ls;
  auto step = begin;

  while (begin != end)
  {
    if ((*begin).type == blocks::token_type::EOL)
    {
      begin++;
      ls.push_back({step, begin});
      step = begin;
    }
    else
    {
      begin++;
    }
  }

  blocks::commands cmds;
  std::vector<error> errors;

  for (auto&& l:ls)
  {
    auto lb = l.begin;
    auto le = l.eol;
    auto&& cmdt = parse_command(lb, le);

    if (cmdt.err.has_value())
    {
      errors.push_back(cmdt.err.value());
    }
    else if (cmdt.cmd.has_value())
    {
      cmds.push_back(cmdt.cmd.value());
    }
  }

  if (!errors.empty())
  {
    for (const error& err : errors)
    {
      std::cerr << "une erreur est survenue " << err.message << "\n";
    }

    std::exit(EXIT_FAILURE);
  }

  return cmds;
}
