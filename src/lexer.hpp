#ifndef __blocks_lexer_hpp__
#define __blocks_lexer_hpp__


#include "model.hpp"

namespace blocks
{
  tokens lex_line(char_citerator begin, char_citerator eol)
  {
    if (
  }

  tokens lex(char_citerator begin, char_citerator end)
  {
    struct line 
    {
      char_citerator begin;
      char_citerator eol;
    };

    using lines = std::vector<line>;

    lines ls;     
    char_citerator step = begin;

    while (begin != end)
    {   
      if (*begin == '\n')
      {
        begin++;
        ls.push_back({step, begin});
        step = begin;
      }
      else 
      {
        begin++;
      }
    }

    tokens tks;

    for (auto&& l:ls)
    {
      auto lb = l.begin();
      auto le = l.end();
      auto&& ltks = lex_line(lb, le);
      auto ltksb = ltks.begin();
      auto ltkse = ltks.end();
      tks.insert(tks.end(), ltksb, ltkse);
    }

    return tks;
  }

}

#endif
