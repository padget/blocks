#ifndef __blocks_source_hpp__
#define __blocks_source_hpp__

#include "token.hpp"
#include "tokenizer.hpp"
#include <string>
#include <vector>

namespace blocks {
class source
{
private:
  std::string __content;
  std::vector<blocks::tokenizer*> __tokenizers;
  mutable std::string::const_iterator __current;
  std::string::const_iterator __end;

public:
  source();
  source(const std::string& content,
         const std::vector<blocks::tokenizer*>& tokenizers);
  source(const std::string& content,
         const std::initializer_list<blocks::tokenizer*>& tokenizers);

public:
  const blocks::token next() const;
};
} // namespace blocks
#endif