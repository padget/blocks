#ifndef __blocks_tokens_accumulator_hpp__
#define __blocks_tokens_accumulator_hpp__

#include "scanner.hpp"
#include "std.hpp"
#include "token.hpp"

namespace blocks {
class token_accumulator
{
private:
  mutable blocks::vector<blocks::tokenizer*> __tokenizers;

public:
  token_accumulator(const blocks::native_list<blocks::tokenizer*>& tokenizers);

  const blocks::vector<blocks::token> accumulate(
    const blocks::string& content) const;
};
}
#endif