#ifndef __blocks_types_hpp__
#define __blocks_types_hpp__

#include <optional>
#include <string>
#include <vector>

namespace blocks {
template<typename type_t>
using vector = std::vector<type_t>;

template<typename type_t>
using vector2d = blocks::vector<blocks::vector<type_t>>;

template<typename type_t>
using optional = std::optional<type_t>;

using string = std::string;
using integer = int;
}

namespace blocks {

struct line_token
{
  blocks::string line;
};

struct basic_token
{
  blocks::string type;
  blocks::string value;
};

struct command
{
  blocks::integer depth;
  blocks::string name;
  blocks::vector<blocks::string> args;
  blocks::vector<blocks::command> subcmds;
};

struct command_argument
{
  blocks::string name;
  blocks::string type;
};

struct command_definition
{
  blocks::string name;
  blocks::vector<blocks::command_argument> args;
  blocks::vector<blocks::command> cmds;
};
}

#endif