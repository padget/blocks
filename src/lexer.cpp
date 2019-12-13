#include "lexer.hpp"

std::optional<blocks::token>
lex_command_name(
                 blocks::char_citerator begin,
                 blocks::char_citerator eol)
{
  constexpr auto type = blocks::token_type::CMDNAME;
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
      return blocks::token{step, begin, type};
    }
  }

  return std::nullopt;
}

std::optional<blocks::token>
lex_eol(
        blocks::char_citerator begin,
        blocks::char_citerator eol)
{
  if (begin != eol)
  {
    auto c = *begin;
    if (c == '\n')
    {
      return blocks::token{begin, std::next(begin), blocks::token_type::EOL};
    }
  }

  return std::nullopt;
}

std::optional<blocks::token>
lex_blank(blocks::char_citerator begin, blocks::char_citerator eol)
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
    return blocks::token{step, begin, blocks::token_type::BLANK};
  }

  return std::nullopt;
}

std::optional<blocks::token>
lex_argument_name(
                  blocks::char_citerator begin,
                  blocks::char_citerator eol)
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
    return blocks::token{step, begin, blocks::token_type::ARGNAME};
  }

  return std::nullopt;
}

std::optional<blocks::token>
lex_argument_type(
                  blocks::char_citerator begin,
                  blocks::char_citerator eol)
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
        return blocks::token{step, name.value().end, blocks::token_type::ARGTYPE};
      }
    }
  }

  return std::nullopt;
}

std::optional<blocks::token>
lex_argument_number(
                    blocks::char_citerator begin,
                    blocks::char_citerator eol)
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
    return blocks::token{step, begin, blocks::token_type::ARGNUMBER};
  }

  return std::nullopt;
}

std::optional<blocks::token>
lex_argument_$$(
                blocks::char_citerator begin,
                blocks::char_citerator eol)
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
          return blocks::token{step, begin, blocks::token_type::ARG$$};
        }
      }
    }
  }

  return std::nullopt;
}

std::optional<blocks::token>
lex_command_argument(
                     blocks::char_citerator begin,
                     blocks::char_citerator eol)
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


blocks::tokens lex_line(
                        blocks::char_citerator begin,
                        blocks::char_citerator eol)
{
  using opttoken = std::optional<blocks::token>;

  blocks::tokens tks;
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

    tks.push_back(blocks::token{begin, std::next(begin), blocks::token_type::ERROR});
    begin++;
  }

  return tks;
}


blocks::tokens blocks::lex(
                   blocks::char_citerator begin,
                   blocks::char_citerator end)
{
  struct line
  {
    blocks::char_citerator begin;
    blocks::char_citerator eol;
  };

  using lines = std::vector<line>;

  lines ls;
  blocks::char_citerator step = begin;

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

  blocks::tokens tks;

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
