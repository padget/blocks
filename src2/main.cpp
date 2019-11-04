#include <iostream>
#include <string>
#include <vector>

#include "command.hpp"
#include "source.hpp"

int
main(int argc, char const* argv[])
{
  blocks::command c("coucou", {});
  blocks::commands cs = { c };
  blocks::name_tokenizer ntkzer;
  blocks::integer_tokenizer inttkzer;
  blocks::command_tokenizer cmdtkzer;
  blocks::source src{ "coucou12\n\nlqdj", { &cmdtkzer } };

  std::cout << cs[0].name() << "\n";
  
  while (true) {
    auto&& tko = src.next();
    if (tko.type() != "eos")
      std::cout << "value " << tko.value() << " type " << tko.type() << "\n";
    else
      break;
  }

  return 0;
}
