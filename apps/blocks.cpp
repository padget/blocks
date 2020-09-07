#include <iostream>
#include <string>

#include "../include/blocks/command_line.hpp"

int main2(int argc, char **argv)
{
  namespace cmdl = blocks::cmdl;
  namespace raw = cmdl::raw;
  namespace spec = cmdl::specification;
  namespace parsed = cmdl::parsed;

  auto specs =
      spec::specify(
          "--",
          spec::optional_arg<bool>("version", "display version", false),
          spec::optional_arg<bool>("help", "display help page", false));

  auto &&report =
      parsed::parse_command_line(
          specs, raw::from_cmdl(argc, argv));

  std::cout << report.not_presents.empty() << std::endl;
  std::cout << specs.arguments.size() << std::endl;

  return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
  try
  {
    return main2(argc, argv);
  }
  catch (std::exception &err)
  {
    std::cout << "erreur arguments : " << err.what() << std::endl;
  }

  return EXIT_SUCCESS;
}