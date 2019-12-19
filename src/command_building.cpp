#include "command_building.hpp"
#include "model.hpp"
#include <iterator>
#include <string>


template <typename char_t>
bool is_letter(char_t c)
{
  return 'a' <= c and c <= 'z';
}


using string_citerator = std::string::const_iterator;


std::string
expect_cname(
             string_citerator begin,
             string_citerator end)
{
  auto step = begin;

  while (begin != end)
    if (is_letter(*begin))
      std::advance(begin, 1);
    else break;

  if (begin != end)
    if (*begin == ':')
      std::advance(begin, 1);

  return std::string(step, begin);
}


blocks::step::step_error
on_cname_error(const blocks::coordinates& coord)
{
  return blocks::step::step_error{
    "filename",
      coord.line,
      coord.column,
      "no command name found : '<name>:' ... "
  };
}

std::string
try_name(string_citerator begin,
         string_citerator end)
{
  auto step = begin;

  while (begin != end)
  {
    auto&& c = *begin;
    if (is_letter(c))
      std::advance(begin, 1);
    else
      break;
  }

  return std::string(step, begin);
}


template<typename char_t>
bool is_digit(char_t c)
{
  return '1'<=c and c<='9';
}


std::string
try_number(string_citerator begin,
           string_citerator end)
{
  auto step = begin;

  while (begin != end)
  {
    auto&& c = *begin;

    if (is_digit(c))
      std::advance(begin, 1);
    else
      break;
  }

  return std::string(step, begin);
}


std::string
try_lastresult(string_citerator begin,
               string_citerator end)
{
  auto step = begin;

  if (begin != end and *begin=='$')
  {
    std::advance(begin, 1);
    if (begin!=end and *begin=='$')
      std::advance(begin, 1);
    else
      begin = step;
  }

  return std::string(step, begin);
}

std::string
try_type(string_citerator begin,
         string_citerator end)
{
  auto step = begin;

  if (begin!=end and *begin=='#')
  {
    std::advance(begin, 1);
    auto&& tname  = try_name(begin, end);
    auto&& tnsize = tname.size();

    if (tnsize==0)
      begin = step;
    else
      std::advance(begin, tnsize);
  }

  return std::string(step, begin);
}

blocks::argument
expect_argument(string_citerator begin,
                string_citerator end)
{
  std::string value;
  std::string type ;

  /* try detect name */
  auto&& argname = try_name(begin, end);
  auto&& anasize = argname.size();

  if (anasize==0)
  {
    /* try detect number */
    auto&& argnumber = try_number(begin, end);
    auto&& anusize   = argnumber.size();

    if (anusize==0)
    {
      /* try detect lastresult */
      auto&& arglastres = try_lastresult(begin, end);
      auto&& arglrize   = arglastres.size();

      if (arglrize!=0)
        value = arglastres;
    }
    else
      value = argnumber;
  }
  else
    value = argname;

  auto&& vsize = value.size();

  if (vsize==0)
    return {};

  std::advance(begin, vsize);

  /* try detect type */
  auto&& argtype  = try_type(begin, end);
  auto&& argtsize = argtype.size();

  if (argtsize!=0)
    type = argtype;

  return blocks::argument {
    value,
      type
  };
}


void
advance_after_blank(string_citerator& begin,
                    string_citerator end)
{
  while (begin!=end and *begin==' ')
    std::advance(begin, 1);
}


std::vector<blocks::argument>
expect_arguments(string_citerator begin,
                 string_citerator end)
{
  std::vector<blocks::argument> args;

  while (begin!=end)
  {
    advance_after_blank(begin, end);

    if (begin != end)
    {
      auto&& arg    = expect_argument(begin, end);
      auto&& avalue = arg.value;
      auto&& atype  = arg.type;
      auto&& asize  = avalue.size() + atype.size();

      if (asize==0)
        break;

      args.push_back(arg);
      std::advance(begin, asize);
    }
    else
      break;
  }

  if (begin != end)
    return std::vector<blocks::argument>{};
  else
    return args;
}



struct error
{
  std::string message;
  std::size_t line, col;
  std::string filename;
};



template<typename type_t>
struct result
{
  type_t res;
  error err;
};



blocks::command
blocks::build_command(
                      const std::string& line,
                      const blocks::coordinates& coord)
{
  auto begin = line.begin();
  auto end = line.end();
  auto column = coord.column;

  /* try detect command name */
  auto && cname = expect_cname(begin, end);
  auto && cnsize = cname.size();

  if (cnsize == 0)
  {
    auto&& err = on_cname_error(coord);
    stp.errors.push_back(err);
    return; // TODO ici nous devons retourner 
    // autre chose qu'une simple commande qui 
    // ne contient pas d'information d'erreur.
  }

  column += cnsize;
  std::advance(begin, cnsize);

  /* try detect command arguments */
  auto&& args = expect_arguments(begin, end);
  auto&& arsize = args.size();

  if (arsize==0 and begin != end)
    return; // TODO ici nous devons retourner 
  // autre chose qu'une simple commande qui
  // ne contient pas d'information d'erreur.


  return blocks::command {
    coord.line,
      cname,
      args
  };
}
