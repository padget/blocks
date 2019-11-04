#ifndef __blocks_tokenizer_hpp__
#define __blocks_tokenizer_hpp__

#include "token.hpp"
#include <optional>

namespace blocks {

using csiterator = const std::string::const_iterator;
using copttoken = const std::optional<const blocks::token>;

class tokenizer
{
public:
  virtual copttoken try_tokenize(csiterator& begin, csiterator& end) const = 0;
};

class eos_tokenizer : public tokenizer
{
public:
  virtual copttoken try_tokenize(csiterator& begin, csiterator& end) const;
};

class eol_tokenizer : public tokenizer
{
public:
  virtual copttoken try_tokenize(csiterator& begin, csiterator& end) const;
};


class command_tokenizer : public tokenizer
{
public:
  virtual copttoken try_tokenize(csiterator& begin, csiterator& end) const;
};

class name_tokenizer : public tokenizer
{
public:
  virtual copttoken try_tokenize(csiterator& begin, csiterator& end) const;
};

class integer_tokenizer : public tokenizer
{
public:
  virtual copttoken try_tokenize(csiterator& begin, csiterator& end) const;
};

class colon_tokenizer : public tokenizer
{
public:
  virtual copttoken try_tokenize(csiterator& begin, csiterator& end) const;
};

class blank_tokenizer : public tokenizer
{
public:
  virtual copttoken try_tokenize(csiterator& begin, csiterator& end) const;
};
} // namespace blocks
#endif