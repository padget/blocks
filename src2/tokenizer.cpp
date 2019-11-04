#include "tokenizer.hpp"

blocks::copttoken
blocks::eos_tokenizer::try_tokenize(blocks::csiterator& begin,
                                    blocks::csiterator& end) const
{
  if (begin == end)
    return token("", "eos");
  else
    return std::nullopt;
}

blocks::copttoken
blocks::eol_tokenizer::try_tokenize(blocks::csiterator& begin,
                                    blocks::csiterator& end) const
{
  if (begin != end && *begin == '\n')
    return token("\n", "eol");
  else
    return std::nullopt;
}

blocks::copttoken
blocks::command_tokenizer::try_tokenize(blocks::csiterator& begin,
                                        blocks::csiterator& end) const
{
  std::string::const_iterator cursor = begin;

  while (cursor != end) {
    cursor++;

    if (*cursor == '\n') {
      cursor++;
      break;
    }
  }

  if (cursor != begin)
    if (cursor == begin + 1)
      return token(std::string(begin, cursor), "emptyline");
    else
      return token(std::string(begin, cursor), "command");
  else
    return std::nullopt;
}

blocks::copttoken
blocks::name_tokenizer::try_tokenize(blocks::csiterator& begin,
                                     blocks::csiterator& end) const
{
  std::string::const_iterator cursor = begin;

  while (cursor != end && 'a' <= *cursor && *cursor <= 'z')
    cursor++;

  if (cursor != begin)
    return token(std::string(begin, cursor), "name");
  else
    return std::nullopt;
}

blocks::copttoken
blocks::integer_tokenizer::try_tokenize(blocks::csiterator& begin,
                                        blocks::csiterator& end) const
{
  std::string::const_iterator cursor = begin;

  while (cursor != end && '0' <= *cursor && *cursor <= '9')
    cursor++;

  if (cursor != begin)
    return token(std::string(begin, cursor), "integer");
  else
    return std::nullopt;
}

blocks::copttoken
blocks::colon_tokenizer::try_tokenize(blocks::csiterator& begin,
                                      blocks::csiterator& end) const
{
  if (begin != end && *begin == ':')
    return token(std::string(begin, begin + 1), "colon");
  else
    return std::nullopt;
}

blocks::copttoken
blocks::blank_tokenizer::try_tokenize(blocks::csiterator& begin,
                                      blocks::csiterator& end) const
{
  if (begin != end && *begin == ' ')
    return token(std::string(begin, begin + 1), "blank");
  else
    return std::nullopt;
}