#ifndef __blocks_command_builder_hpp__
#define __blocks_command_builder_hpp__

#include "command.hpp"
#include "scanner.hpp"
#include "token.hpp"
#include "std.hpp"
#include <optional>

namespace blocks {
/* Un command builder permet de creer une commande à partir d'une chaine token */
class command_builder
{
public:
  const std::optional<blocks::command> build() const;
};
}

#endif