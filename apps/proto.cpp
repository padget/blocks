#include <iostream>

#include "../libs/cmdl/cmdl.hpp"

using namespace libs::cmdl;

int main(int argc, char **argv)
{
  specify("log",
          flag("[graph]") /*,
          opt("[verbose=<v|vv|vvv|vvvv>]"),
          opt("[user=<email>]")*/
  );

  return EXIT_SUCCESS;
}