#ifndef __blocks_token_hpp__
#define __blocks_token_hpp__

#include <string>

namespace blocks {
class token {
private:
  std::string __value;
  std::string __type;

public:
  token(const std::string &value, const std::string& type);

  const std::string &value() const;
  const std::string &type() const;
};
} // namespace blocks

#endif