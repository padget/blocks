#include "source.hpp"
#include <optional>

blocks::source::source() {}

blocks::source::source(const std::string& content,
                       const std::vector<blocks::tokenizer*>& tokenizers)
  : __content{ content }
  , __tokenizers{ tokenizers }
  , __current{ __content.begin() }
  , __end{ __content.end() }
{}

blocks::source::source(
  const std::string& content,
  const std::initializer_list<blocks::tokenizer*>& tokenizers)
  : __content{ content }
  , __tokenizers{ tokenizers }
  , __current{ __content.begin() }
  , __end{ __content.end() }
{}

const blocks::token
blocks::source::next() const
{
  for (auto* tkzer : __tokenizers) {
    auto&& tk = tkzer->try_tokenize(__current, __end);
    if (tk.has_value()) {
      __current = std::next(__current, tk.value().value().size());
      return tk.value();
    }
  }
  if (__current != __end) {
    auto temp = __current;
    __current = std::next(temp);
    return token(std::string(temp, __current), "error");
  }
  else return token("", "eos");
}