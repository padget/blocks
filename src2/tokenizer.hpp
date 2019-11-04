#ifndef __blocks_tokenizer_hpp__
#define __blocks_tokenizer_hpp__

#include "token.hpp"
#include <optional>

namespace blocks {
class tokenizer
{
public:
  virtual const std::optional<const blocks::token> try_tokenize(
    const std::string::const_iterator& begin,
    const std::string::const_iterator& end) const = 0;
};

class command_tokenizer : public tokenizer
{
public:
  virtual const std::optional<const blocks::token> try_tokenize(
    const std::string::const_iterator& begin,
    const std::string::const_iterator& end) const;
};

class name_tokenizer : public tokenizer
{
public:
  virtual const std::optional<const blocks::token> try_tokenize(
    const std::string::const_iterator& begin,
    const std::string::const_iterator& end) const;
};

class integer_tokenizer : public tokenizer
{
public:
  virtual const std::optional<const blocks::token> try_tokenize(
    const std::string::const_iterator& begin,
    const std::string::const_iterator& end) const;
};
} // namespace blocks
#endif