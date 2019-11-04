#include "command.hpp"

blocks::command::command(const int depth,
                         const std::string& name,
                         const std::vector<std::string> args)
  : __depth{ depth }
  , __name{ name }
  , __args{ args }
{}

blocks::command::command(const int depth,
                         const std::string& name,
                         const std::initializer_list<std::string> args)
  : __depth{ depth }
  , __name{ name }
  , __args{ args }
{}

const std::string&
blocks::command::name() const
{
  return __name;
}

const std::vector<std::string>&
blocks::command::args() const
{
  return __args;
}

const int
blocks::command::depth() const
{
  return __depth;
}