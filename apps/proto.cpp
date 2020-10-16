#include <iostream>

#include "../libs/cmdl/cmdl.hpp"
#include "../libs/intrange.hpp"

using namespace libs::cmdl;
using namespace libs;

enum class verbosity
{
};

struct email
{
};

struct args
{
};

int main(int argc, char **argv)
{
  auto spec =
      specify(
          "log",
          flag("[graph]"),
          opt("[verbose=<v|vv|vvv|vvvv>]"),
          opt("[user=<email>]"));

  report rep = parse(spec, argc, argv);

  // get<bool>(rep, "graph");
  // get<verbosity>(rep, "verbose");
  // get<email>(rep, "email");

  // get_all<args>(rep);

  return EXIT_SUCCESS;
}