#include <iostream>
#include "lexer.hpp"
#include "parser.hpp"
int main()
{
  std::string src = 
    "main: arg#int argc#int\n"
    "add: 12#int 23#int\n"
    "print: $$#int\n";

  auto&& tks = blocks::lex(src.begin(), src.end());

  for (auto&& tk : tks)
  {
    if (tk.type == blocks::token_type::ERROR)
    {
      std::cout << "error : ";
      std::cout << *tk.begin << "\n";
    }
    else
    {
      std::cout << (int)tk.type << ":";
      auto begin = tk.begin;
      auto end   = tk.end;
      while (begin != end)
        std::cout << *(begin++);
      std::cout << "\n";
    }
  }

  auto&& cmds = blocks::parse_commands(tks.cbegin(), tks.cend());

  for (auto&& cmd : cmds)
  {
    std::cout << cmd.name << "\n";
    for (auto&& arg : cmd.args)
    {
      std::cout << "  - "<< arg.value << arg.type << "\n";
    }
  }

  return EXIT_SUCCESS;
}
