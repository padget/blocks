#include <iostream>
#include <string>
#include <vector>

#include "command.hpp"
#include "scanner.hpp"

namespace blocks {
class command_builder
{
private:
  blocks::scanner __cmd_scan;

public:
  command_builder(const blocks::token& cmd_tko);

public:
  const std::optional<const blocks::command> build() const;

private:
  const std::vector<blocks::token> tokens() const;
  const int depth(const std::vector<blocks::token>& cmd_tks) const;
};
}

blocks::command_builder::command_builder(const blocks::token& cmd_tko)
{
  blocks::name_tokenizer ntkzer;
  blocks::integer_tokenizer inttkzer;
  blocks::colon_tokenizer coltkzer;
  blocks::blank_tokenizer blktkzer;
  blocks::eos_tokenizer eostkzer;
  blocks::eol_tokenizer eoltkzer;
  blocks::scanner scan{
    cmd_tko.value(),
    { &eostkzer, &eoltkzer, &ntkzer, &inttkzer, &coltkzer, &blktkzer }
  };
  __cmd_scan = std::move(scan);
}

const std::vector<blocks::token>
blocks::command_builder::tokens() const
{
  std::vector<blocks::token> cmd_tokens;
  bool has_token = true;

  while (has_token) {
    cmd_tokens.push_back(__cmd_scan.next());

    if (cmd_tokens.back().type() == "eos")
      has_token = false;
  }

  return cmd_tokens;
}

const int
blocks::command_builder::depth(const std::vector<blocks::token>& cmd_tks) const
{
  int cmd_depth = 0;
  while (cmd_tks[cmd_depth].type() == "blank")
    cmd_depth++;

  return cmd_depth;
}

const std::optional<const blocks::command>
blocks::command_builder::build() const
{

  auto&& tks = tokens();
  auto&& cmd_depth = depth(tks);
  std::cout << "depth " << cmd_depth << "\n";

  return std::nullopt;
}

int
main(int argc, char const* argv[])
{
  blocks::eos_tokenizer eostkzer;
  blocks::eol_tokenizer eoltkzer;
  blocks::command_tokenizer cmdtkzer;
  blocks::scanner src{ "main: \n add: 1 2\n print: res",
                       { &eostkzer, &cmdtkzer } };

  bool has_token = true;

  while (has_token) {
    auto&& tko = src.next();

    if (tko.type() == "command") {
      blocks::name_tokenizer ntkzer;
      blocks::integer_tokenizer inttkzer;
      blocks::colon_tokenizer coltkzer;
      blocks::blank_tokenizer blktkzer;
      blocks::scanner line{
        tko.value(),
        { &eostkzer, &ntkzer, &inttkzer, &coltkzer, &blktkzer, &eoltkzer }
      };

      bool command_has_token = true;
      std::cout << " -- command --\n";
      while (command_has_token) {
        auto&& cmd_tko = line.next();
        std::cout << " -> token {value : '" << cmd_tko.value() << "', type: '"
                  << cmd_tko.type() << "'}\n";

        if (cmd_tko.type() == "eos")
          command_has_token = false;
      }
    }

    if (tko.type() == "eos") {
      has_token = false;
    }
  }

  return 0;
}
