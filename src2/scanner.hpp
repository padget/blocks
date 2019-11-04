#ifndef __blocks_scanner_hpp__
#define __blocks_scanner_hpp__

#include "token.hpp"
#include "tokenizer.hpp"
#include <string>
#include <vector>

namespace blocks {
class scanner
{
private:
  std::string __content;
  std::vector<blocks::tokenizer*> __tokenizers;
  mutable std::string::const_iterator __current;
  std::string::const_iterator __end;

public:
  scanner();
  scanner(const std::string& content,
         const std::vector<blocks::tokenizer*>& tokenizers);
  scanner(const std::string& content,
         const std::initializer_list<blocks::tokenizer*>& tokenizers);

public:
  const blocks::token next() const;
};
} // namespace blocks
#endif