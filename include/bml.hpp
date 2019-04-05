#ifndef __BLOCKS_BML_HPP__
#define __BLOCKS_BML_HPP__


#include <string>
#include <type_traits>
#include <variant>
#include <optional>
#include <algorithm>
#include <vector>
#include <list>
#include <sstream>

#include <result.hpp>

namespace mystd
{
  template<class InputIt,
           class UnaryPredicate>
  constexpr InputIt find_if (InputIt first, InputIt last, UnaryPredicate p)
  {
    while (first!=last)
    {
      if (p(*first))
        return first;

      ++first;
    }

    return last;
  }
}


template<typename iterator, auto type>
std::optional<std::pair<iterator, decltype(type)>>
detect_colon (iterator begin,
              iterator end)
{
  return (begin!=end&&*begin==':') ?
         std::optional(std::pair(std::next(begin), type)) :
         std::nullopt;
}


template<typename iterator, auto type>
std::optional<std::pair<iterator, decltype(type)>>
detect_indent (iterator begin,
               iterator end)
{
  return (begin!=end&&*begin=='\t') ?
         std::optional(std::pair(std::next(begin), type)) :
         std::nullopt;
}


template<typename iterator, auto type>
std::optional<std::pair<iterator, decltype(type)>>
detect_space (iterator begin,
              iterator end)
{
  return (begin!=end&&*begin==' ') ?
         std::optional(std::pair(std::next(begin), type)) :
         std::nullopt;
}


template<typename iterator, auto type>
std::optional<std::pair<iterator, decltype(type)>>
detect_eol (iterator begin,
            iterator end)
{
  return (begin!=end&&*begin=='\n') ?
         std::optional(std::pair(std::next(begin), type)) :
         std::nullopt;
}


template<typename iterator, auto type>
std::optional<std::pair<iterator, decltype(type)>>
detect_label (iterator begin,
              iterator end)
{
  auto cursor = begin;

  while (cursor!=end&&(
    ('a'<=*cursor&&*cursor<='z')||
    *cursor=='$'))
  {
    ++cursor;
  }

  return (cursor!=begin) ?
         std::optional(std::pair(cursor, type)) :
         std::nullopt;
}


template<typename iterator, auto type>
std::optional<std::pair<iterator, decltype(type)>>
detect_tabitem (iterator begin,
                iterator end)
{
  return (begin!=end&&*begin=='[') ?
         std::optional(std::pair(std::next(begin), type)) :
         std::nullopt;
}


template<typename iterator, auto type>
std::optional<std::pair<iterator, decltype(type)>>
detect_number (iterator begin,
               iterator end)
{
  auto cursor = begin;

  while (cursor!=end&&
         '0'<=*cursor&&
         *cursor<='9')
  {
    ++cursor;
  }

  return (cursor!=begin) ?
         std::optional(std::pair(cursor, type)) :
         std::nullopt;
}


template<typename iterator,
         typename detector,
         typename ... detectors>
auto detect (iterator begin, iterator end,
             detector d, detectors ... ds)
-> decltype(d(begin, end))
{
  auto results = std::array{d(begin, end), ds(begin, end)...};
  auto has_value = [] (auto const &opt)
  { return opt.has_value(); };
  auto found = mystd::find_if(std::begin(results),
                              std::end(results),
                              has_value);

  if (found!=std::end(results))
    return *found;
  else
    return std::nullopt;
}


enum class bml : int
{
  unknown, label, indent, space, number, colon, eol, tabitem, string /* TODO faire la fonction pour string */
  // 0   , 1    , 2     , 3    , 4     , 5    , 6  , 7      , 8
};


template<typename str_t = std::string>
class lexer
{
private:
  using iterator = typename str_t::const_iterator;

  iterator __cursor;
  iterator __end;
  unsigned __line = 1;

public:
  explicit lexer (const str_t &input)
    : __cursor(std::begin(input)),
      __end(std::end(input))
  {}


  struct token
  {
    bml type;
    str_t value;
  };


public:
  token next ()
  {
    auto res = detect(
      __cursor, __end,
      &detect_tabitem<iterator, bml::tabitem>,
      &detect_colon<iterator, bml::colon>,
      &detect_eol<iterator, bml::eol>,
      &detect_number<iterator, bml::number>,
      &detect_label<iterator, bml::label>,
      &detect_indent<iterator, bml::indent>,
      &detect_space<iterator, bml::space>);

    bool valued = res.has_value();

    auto &&type = valued ? std::get<1>(res.value()) : bml::unknown;
    auto &&iter = valued ? std::get<0>(res.value()) : std::next(__cursor);
    auto &&value = str_t(__cursor, iter);

    auto tk = token{type, value};

    __cursor = valued ? std::get<0>(res.value()) : std::next(__cursor);
    return tk;
  }


  bool has_next () const
  {
    return __cursor not_eq __end;
  }


  std::vector<token> tokens ()
  {
    std::list<token> tks;

    while (has_next())
      tks.push_back(next());

    auto begin = std::begin(tks);
    auto end = std::end(tks);

    std::list<token> tks2;
    auto end2 = std::remove_if(
      std::begin(tks), std::end(tks),
      [] (const auto &tk)
      { return tk.type==bml::space; });

    std::vector<token> res(
      std::make_move_iterator(std::begin(tks)),
      std::make_move_iterator(end2));
    return res;
  }
};


template<typename iterator>
bool is_not_end (const iterator &begin,
                 const iterator &end)
{
  return begin!=end;
}


template<typename iterator>
bool is_not_eol (const iterator &begin)
{
  return (*begin).type!=bml::eol;
}


template<typename iterator>
bool is_indent (const iterator &begin)
{
  return (*begin).type==bml::indent;
}


template<typename iterator>
bool is_arg (const iterator &begin)
{
  const auto &type = (*begin).type;

  switch (type)
  {
    case bml::label:
    case bml::number:
    case bml::tabitem:
    case bml::string:
      return true;
    default:
      return false;
  }
}


template<typename iterator>
bool is_command_name (const iterator &begin)
{
  return (*begin).type==bml::label;
}


template<typename iterator>
bool is_colon (const iterator &begin)
{
  return (*begin).type==bml::colon;
}


template<typename iterator>
bool has_lexical_error (const iterator &begin,
                        const iterator &end)
{
  return std::find_if(begin, end, [] (auto &&tk)
  { return tk.type==bml::unknown; })!=end;
}


template<typename iterator>
std::string lexical_error (iterator begin, unsigned line)
{
  const auto &tk = *begin;
  std::stringstream ss;

  if (tk.type==bml::unknown)
  {
    ss<<"unexpected character "<<tk.value<<" at l."<<line<<'\n';
  }

  return ss.str();
}


template<typename iterator>
std::string lexical_errors (iterator begin,
                            iterator end,
                            unsigned line)
{
  std::stringstream ss;

  while (is_not_end(begin, end))
  {
    ss<<lexical_error(begin, line);
    begin++;
  }

  return ss.str();
}


struct command
{
  unsigned context;
  std::string name;
  std::vector<std::string> args;
};


struct command_error
{
  unsigned line;
  std::string error;
};


template<typename iterator>
result<command, command_error>
parse_line (iterator begin,
            iterator end,
            unsigned line)
{
  if (is_not_end(begin, end)&&
      is_not_eol(begin))
  {
    if (has_lexical_error(begin, end))
    {
      const auto &tk = *begin;

      return command_error{
        .line = line,
        .error = lexical_errors(begin, end, line)};
    }
    else
    {
      unsigned context = 0;

      while (is_not_end(begin, end)&&
             is_indent(begin))
      {
        begin++;
        context++;
      }

      std::string name;

      if (is_not_end(begin, end)&&
          is_command_name(begin)&&
          is_not_end(std::next(begin), end)&&
          is_colon(std::next(begin)))
      {
        name = (*begin).value;

        begin++;
        begin++;
      }
      else
      {
        const auto &tk = *begin;

        return command_error{
          .line = line,
          .error = "a label is expected a the beginning of the command"};
      }

      std::vector<std::string> args;

      while (is_not_end(begin, end)&&
             is_arg(begin))
      {
        args.push_back((*begin).value);
        begin++;
      }

      if (is_not_eol(begin))
      {
        const auto &tk = *begin;
        return command_error{
          .line = line,
          .error = "there are unexcepted element a the end of the command line"};
      }

      return command{
        .context=context,
        .name=name,
        .args=args};
    }
  }
  else
  {
    const auto &tk = *begin;
    return command_error{
      .line = line,
      .error = "there is lexical errors in the command line"};
  }
}


template<typename str_t=std::string>
std::vector<result<command, command_error>>
parse (lexer<str_t> &lex)
{
  auto &&tokens = lex.tokens();
  auto begin = std::begin(tokens), eol = begin;
  auto end = std::end(tokens);
  unsigned line = 1;
  std::vector<result<command, command_error>> commands;

  while (is_not_end(begin, end))
  {
    while (is_not_end(eol, end)&&
           is_not_eol(eol))
      ++eol;

    // between begin and eol we have a line
    auto &&cmd = parse_line(begin, eol, line);

    commands.push_back(cmd);

    if (is_not_end(eol, end))
      ++eol;

    begin = eol;
    ++line;
  }

  return commands;
}


#endif