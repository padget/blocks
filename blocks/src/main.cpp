#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

#include "../../include/arguments.hpp"

int main(int argc, char** argv)
{
	auto&& args = cxx::from_args(argc, argv);
	std::string subprocess;
	std::string filename;
	bool should_compile = args.count("--compile") == 1;
	bool should_execute = args.count("--execute") == 1;

	if (should_compile)
	{
		subprocess = "blocks-compile.exe";
		filename = args.at("--compile").value;
	}
	else if (should_execute)
	{
		subprocess = "blocks-execute.exe";
		filename = args.at("--execute").value;
	}
	
	std::stringstream ss;
	ss << "./" << subprocess << " --file " << filename;
	auto cmd = ss.str();
	auto res = std::system(cmd.c_str());
	std::cout << res << std::endl;
	return 0;
}
