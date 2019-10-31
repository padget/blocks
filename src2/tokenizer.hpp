#ifndef __blocks_tokenizer_hpp__
#define __blocks_tokenizer_hpp__

#include "token.hpp"
#include <optional>

namespace blocks {
class tokenizer {
  public: 
    const std::optional<const blocks::token> try_tokenize(const std::string&) const;
};
} // namespace blocks
#endif