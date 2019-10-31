#include "token.hpp"

blocks::token::token(const std::string &value, const std::string &type)
    : __value{value}, __type{type} {}
const std::string &blocks::token::value() const { return __value; }
const std::string &blocks::token::type() const { return __type; }