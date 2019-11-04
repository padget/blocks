#ifndef __blocks_command_hpp__
#define __blocks_command_hpp__

#include <string>
#include <vector>

namespace blocks {
class command
{
private:
  std::string __name;
  std::vector<std::string> __args;
  int __depth;

public:
  command(const int depth,
          const std::string& name,
          const std::vector<std::string> args);
  command(const int depth,
          const std::string& name,
          const std::initializer_list<std::string> args);

  const std::string& name() const;
  const std::vector<std::string>& args() const;
  const int depth() const;
};

using commands = std::vector<command>;
} // namespace blocks

#endif