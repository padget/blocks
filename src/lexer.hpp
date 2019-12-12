#ifndef __blocks_lexer_hpp__
#define __blocks_lexer_hpp__


#include "model.hpp"
#include <optional>

namespace blocks
{
  template<typename iterator>
  std::optional<token> 
  lex_command_name(
    iterator begin, 
    iterator eol)
  {
    constexpr auto type = token_type::CMDNAME;
    auto step = begin;

    while (begin != eol)
    {
      auto c = *begin;

      if ('a' <= c and c <= 'z')
      {
        begin++;
      }
      else 
      {
        break;
      }
    }
      
    if (begin != eol and begin != step)
    {
      auto c = *begin;
      
      if (c == ':')
      {
        begin++;
        return token{step, begin, type};
      }
    }

    return std::nullopt;
  }

  template<typename iterator>
  std::optional<token>
  lex_eol(
      iterator begin, 
      iterator eol)
  {
    if (begin != eol)
    {
      auto c = *begin;
      if (c == '\n')
      {
        return token{begin, std::next(begin), token_type::EOL};
      }
    }

    return std::nullopt;
  }

  template<typename iterator>
  std::optional<token>
  lex_blank(iterator begin, iterator eol)
  {
    auto step = begin;

    while (begin != eol)
    {
      auto c = *begin;
    
      if (c == ' ')
      {
        begin++;
      }
      else 
      {
        break;
      }
    }

    if (begin != step)
    {
      return token{step, begin, token_type::BLANK};
    }

    return std::nullopt;
  }

  template<typename iterator>
  std::optional<token>
  lex_argument_name(iterator begin, iterator eol)
  {
    auto step = begin;

    while (begin != eol)
    {
      auto c = *begin;

      if ('a' <= c and c <= 'z')
      {
        begin++;
      }
      else 
      {
        break;
      }
    }

    if (begin != step)
    {
      return token{step, begin, token_type::ARGNAME};
    }

    return std::nullopt;
  }

  template<typename iterator>
  std::optional<token>
  lex_argument_type(
      iterator begin, 
      iterator eol)
  {
    auto step = begin;

    if (begin != eol)
    {
      auto c = *begin;
      
      if (c == '#')
      {
        begin++;
        auto&& name = lex_argument_name(begin, eol);
      
        if (name.has_value())
        {
          return token{step, begin, token_type::ARGTYPE}; 
        }
      }
    }

    return std::nullopt;
  }

  template<typename iterator>
  std::optional<token>
  lex_argument_number(
      iterator begin, 
      iterator eol)
  {
    auto step = begin;

    while (begin != eol)
    {
      auto c = *begin;

      if ('0' <= c and c <= '9')
      {
        begin++;
      }
      else 
      {
        break;
      }
    }

    if (begin != step)
    {
      return token{step, begin, token_type::ARGNUMBER};
    }

    return std::nullopt;
  }

  template<typename iterator>
  std::optional<token>
  lex_argument_$$(
      iterator begin, 
      iterator eol)
  {
    auto step = begin;

    if (begin != eol)
    {
      auto c = *begin;
    
      if (c == '$')
      {
        begin++;
      
        if (begin != eol)
        {
          auto c2 = *begin;
        
          if (c2 == '$')
          {
            begin++;
            return token{step, begin, token_type::ARG$$};
          }
        }
      }
    }

    return std::nullopt;
  }

  template<typename iterator>
  std::optional<token>
  lex_command_argument(
      iterator begin, 
      iterator eol)
  {
    // argname
    auto &&argname = lex_argument_name(begin, eol);
    if (argname.has_value())
    {
      return argname;
    }

    auto &&argtype = lex_argument_type(begin, eol);
    if (argtype.has_value())
    {
      return argtype;
    }

    auto &&argnum = lex_argument_number(begin, eol);
    if (argnum.has_value())
    {
      return argnum;
    }

    auto &&arg$$ = lex_argument_$$(begin, eol);
    if (arg$$.has_value())
    {
      return arg$$;
    }

    return std::nullopt;
  }

  tokens lex_line(char_citerator begin, char_citerator eol)
  {
    using opttoken = std::optional<token>;

    tokens tks;
    opttoken o;

    while (begin != eol)
    {
      auto&& obl = lex_blank(begin, eol);
      if (obl.has_value())
      {
        begin = obl.value().end;
        continue;
      }

      auto&& otk = lex_command_name(begin, eol);
      if (otk.has_value())
      {
        tks.push_back(otk.value());
        begin = otk.value().end;
        continue;
      }

      auto&& otk2 = lex_command_argument(begin, eol);
      if (otk2.has_value())
      {
        tks.push_back(otk2.value());
        begin = otk2.value().end;
        continue;
      }

      auto&& otk3 = lex_eol(begin, eol);
      if (otk3.has_value())
      {
        tks.push_back(otk3.value());
        begin = otk3.value().end;
        continue;
      }

      tks.push_back(token{begin, std::next(begin), token_type::ERROR});
      begin++;
    }

    return tks;
  }

  template<typename iterator>
  tokens lex(
    iterator begin, 
    iterator end)
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
      auto lb = l.begin;
      auto le = l.eol;
      auto&& ltks = lex_line(lb, le);
      auto ltksb = ltks.begin();
      auto ltkse = ltks.end();
      tks.insert(tks.end(), ltksb, ltkse);
    }

    return tks;
  }
}

#endif
