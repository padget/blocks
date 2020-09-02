#include <iostream>
#include <string>

#include "../include/blocks/command_line.hpp"

namespace cmdl = blocks::cmdl;

int main2(int argc, char **argv)
{
  namespace cmdl2 = blocks::cmdl2;

  auto spec =
      cmdl2::specify(
          cmdl2::arg<bool>(
              cmdl2::longname_t("version"),
              cmdl2::shortname_t("v"),
              cmdl2::doc_t("display version"),
              cmdl2::required_t(false),
              cmdl2::default_val_t<bool>(true)),
          cmdl2::arg<bool>(
              cmdl2::longname_t("version"),
              cmdl2::shortname_t("v"),
              cmdl2::doc_t("display version"),
              cmdl2::required_t(false),
              cmdl2::default_val_t<bool>(true)));

  std::cout << spec.arguments.size() << std::endl;
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