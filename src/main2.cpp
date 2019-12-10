#include "lexer.hpp"
#include <iostream>

int main()
{
  std::string src = "main: arg#int argc#string\n";
  auto&& tks = blocks::lex(src.begin(), src.end());
  
  for (auto&& tk : tks)
  {
    if (tk.type == blocks::token_type::ERROR)
      std::cout << "error\n" << std::endl;
    else 
      std::cout << (int)tk.type << std::endl;
  }

  return EXIT_SUCCESS;
}
