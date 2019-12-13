#ifndef __blocks_model_hpp__
#define __blocks_model_hpp__

#include <vector>
#include <string>
#include <map>

namespace blocks
{

using char_citerator = std::string::const_iterator;


enum class token_type: int
  {
    BLANK, // 0
    CMDNAME, // 1
    ARGNAME, // 2
    ARGTYPE, // 3
    ARGNUMBER, // 4
    ARGSTRING, // 5
    ARG$$, // 6
    EOL, // 7
    ERROR // 8
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


struct parameter
{
  std::string name;
  std::string type;
};


struct command_signature
{
  std::string name;
  std::vector<parameter> params;
};


struct dictonnary
{
  std::vector<command_signature> defs;
  std::map<std::size_t, command_signature*> indexes;
};


enum class report_status
{
  OK, KO, PROCESSING
};


enum class step_status
{
  OK, KO, PROCESSING
};


struct step
{
  struct step_error
  {
    std::string filename;
    std::size_t line, col;
    std::string message;
  };

  std::string name;
  std::string description;
  std::vector<step_error> errors;
  step_status status;
};


// TODO
struct report
{
  std::vector<step> steps;
  report_status status;
};

}


#endif
