#ifndef __blocks_lexer_hpp__
#define __blocks_lexer_hpp__


#include "model.hpp"
#include <optional>

namespace blocks
{
tokens lex(
           char_citerator begin,
           char_citerator end);
}

#endif
