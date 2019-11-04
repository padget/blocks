#include "tokenizer.hpp"

const std::optional<const blocks::token>
blocks::command_tokenizer::try_tokenize(
  const std::string::const_iterator& begin,
  const std::string::const_iterator& end) const
{
  std::string::const_iterator cursor = begin;

  while (cursor != end) {
    cursor++;

    if (*cursor == '\n')
      break;
  }

  if (cursor != begin)
    if (cursor == begin + 1)
      return token(std::string(begin, cursor), "emptyline");
    else
      return token(std::string(begin, cursor), "command");
  else
    return std::nullopt;
}

const std::optional<const blocks::token>
blocks::name_tokenizer::try_tokenize(
  const std::string::const_iterator& begin,
  const std::string::const_iterator& end) const
{
  std::string::const_iterator cursor = begin;

  while (cursor != end && 'a' <= *cursor && *cursor <= 'z')
    cursor++;

  if (cursor != begin)
    return token(std::string(begin, cursor), "name");
  else
    return std::nullopt;
}

const std::optional<const blocks::token>
blocks::integer_tokenizer::try_tokenize(
  const std::string::const_iterator& begin,
  const std::string::const_iterator& end) const
{
  std::string::const_iterator cursor = begin;

  while (cursor != end && '0' <= *cursor && *cursor <= '9')
    cursor++;

  if (cursor != begin)
    return token(std::string(begin, cursor), "integer");
  else
    return std::nullopt;
}