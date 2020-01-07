#include <iostream>
#include <vector>
#include <string>
#include "../../include/cxx.hpp"
#include "arguments.hpp"


int main(int argc, char** argv)
{
  auto&& args=cxx::from_args(argc, argv);
  for (auto && arg: args) 
    std::cout << arg.first << " " << arg.second.value << std::endl;
	std::cout << "coucou " << std::endl;
	for (int i=0; i<argc; ++i)
		std::cout << argv[i] << "\n";
	return 0;
 }
