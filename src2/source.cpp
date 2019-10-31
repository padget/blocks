#include "source.hpp"
#include <optional>

blocks::source::source() {}

blocks::source::source(const std::string &content,
                       const std::vector<blocks::tokenizer *> &tokenizers)
    : __content{content}, __tokenizers{tokenizers} {}

blocks::source::source(
    const std::string &content,
    const std::initializer_list<blocks::tokenizer *> &tokenizers)
    : __content{content}, __tokenizers{tokenizers} {}

const blocks::token blocks::source::next() const {
 
  for(auto* tkzer: __tokenizers) {
    auto && tk = tkzer->try_tokenize(__content);   
    if (tk.has_value())
      return tk.value();
  }

  return token("", "error");
}