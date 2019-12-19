#include <iostream>
#include <string>
#include "lexer.hpp"
#include "parser.hpp"
#include "semanticker.hpp"


int main()
{
  std::string src =
    "main: arg#int argc#int\n"
    "add: 12#int 23#int\n"
    "print: $$#int\n";



  return EXIT_SUCCESS;
}
