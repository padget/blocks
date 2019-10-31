#include <iostream>
#include <string>
#include <vector>

#include "command.hpp"


int main(int argc, char const *argv[]) {
  blocks::command c("coucou", {});
  blocks::commands cs = {c};
  

  std::cout << cs[0].name() << "\n";

  std::cout << "coucou" << std::endl;
  return 0;
}
