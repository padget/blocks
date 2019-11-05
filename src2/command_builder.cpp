#include "command_builder.hpp"

template<typename iterator>
const int
depth_of_command(iterator begin, iterator end)
{
  blocks::integer depth = 0;
  while (begin != end && (*begin).type() == "blank") {
    depth++;
    begin++;
  }
  return depth;
}

const blocks::optional<blocks::command>
blocks::command_builder::build() const
{
  blocks::vector<blocks::token> tokens;
  blocks::integer depth = depth_of_command(tokens.begin(), tokens.end());
  
  

  blocks::string name;
  blocks::vector<blocks::string> args;

  return blocks::optional<blocks::command>{ { depth, name, args } };
}