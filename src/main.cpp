#include <iostream>
#include "lexer.hpp"
#include "parser.hpp"
int main()
{
  std::string src = "main: arg argc\n";
  auto&& tks = blocks::lex(src.begin(), src.end());
  
  for (auto&& tk : tks)
  {
    if (tk.type == blocks::token_type::ERROR)
    {
      std::cout << "error : ";
      std::cout << *tk.begin << "\n";
    }
    else 
      std::cout << (int)tk.type << std::endl;
  }

  auto&& cmds = blocks::parse_commands(tks.begin(), tks.end());
  

  return EXIT_SUCCESS;
}
