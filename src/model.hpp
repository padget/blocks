#ifndef __blocks_model_hpp__
#define __blocks_model_hpp__

#include <vector>
#include <string>

namespace blocks
{
 
  using char_citerator = std::string::const_iterator;

  
  enum class token_type: int
  {
    BLANK,
    CMDNAME,
    ARGNAME,
    ARGTYPE,
    ARGNUMBER,
    ARGSTRING,
    ARG$$,
    EOL,
    ERROR
  };


  struct token 
  {
    char_citerator begin;
    char_citerator end;
    token_type     type;
  };


  using tokens = std::vector<token>;
  using token_citerator = tokens::const_iterator;


  struct argument
  {
    std::string value;
    std::string type;
  };


  using arguments = std::vector<argument>;
  using argument_citerator = arguments::const_iterator;


  struct command 
  {
    std::size_t line;
    std::string name;
    arguments args;
  };
  

  using commands = std::vector<command>;
  using command_citerator = commands::const_iterator;
  using command_iterator = commands::iterator;


  // TODO
  struct dictonnary {};
  

  // TODO
  struct command_signature {};

}


#endif
