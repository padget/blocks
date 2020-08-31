#include <iostream>
#include <string>

#include "../include/blocks/command_line.hpp"

namespace cmdl = blocks::cmdl;

int main(int argc, char **argv)
{
  try
  {

    cmdl::specification spec =
        cmdl::specify()
            .arg(cmdl::abool("execute", "e")
                     .documentation("run compilation command")
                     .required(true)
                     .build())
            .arg(cmdl::astring("file", "f")
                     .documentation("file to execute")
                     .build())
            .build();

    cmdl::command_line_params toto;
    cmdl::from(spec).parse(argc, argv).fill(toto);

    cmdl::parser_results().extract<bool>("version");
  }
  catch (std::exception &err)
  {
    std::cout << "erreur arguments : " << err.what() << std::endl;
  }

  return EXIT_SUCCESS;
}