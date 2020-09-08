#include <iostream>
#include <string>

#include "../include/blocks/command_line.hpp"
namespace cmdl = blocks::cmdl;
namespace raw = cmdl::raw;
namespace spec = cmdl::specification;
namespace parsed = cmdl::parsed;

void print_report(const parsed::report &rep)
{
  std::cout << "print report\n";
  for (auto &&[name, arg] : rep.avs)
  {
    std::cout << name << ' ' << arg.value << '\n';
  }

  std::cout << "not presents\n";
  for (auto &&name : rep.not_presents)
  {
    std::cout << name << '\n';
  }
}

int main2(int argc, char **argv)
{

  auto specs =
      spec::specify(
          "--",
          spec::required_arg<bool>("version", "display version", false),
          spec::required_arg<bool>("help", "display help page"));

  auto &&report =
      parsed::parse_command_line(
          specs, raw::from_cmdl(argc, argv));

  print_report(report);

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