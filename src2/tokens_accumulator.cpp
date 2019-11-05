#include "tokens_accumulator.hpp"
#include "std.hpp"

blocks::token_accumulator::token_accumulator(
  const blocks::native_list<blocks::tokenizer*>& tokenizers)
  : __tokenizers{ tokenizers }
{}

const blocks::vector<blocks::token>
blocks::token_accumulator::accumulate(const blocks::string& content) const
{
  blocks::eos_tokenizer eostkzer;
  __tokenizers.push_back(&eostkzer);

  blocks::scanner scan{ content, __tokenizers };
  blocks::vector<blocks::token> tokens;
  bool has_token = true;

  while (has_token) {
    tokens.push_back(std::move(scan.next()));

    if (tokens.back().type() == "eos")
      has_token = false;
  }

  __tokenizers.pop_back();
  return tokens;
}