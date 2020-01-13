#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "../../include/arguments.hpp"

struct command
{
	int cmdid; 
	int nbargs;
};


int main(int argc, char** argv)
{
	auto && args = cxx::from_args(argc, argv);

	if(args.count("--file") == 0)
		return EXIT_FAILURE;

	auto&& filename = args.at("--file").value;
	
	std::ifstream is(filename+".blb");
	
	std::istreambuf_iterator<char> endfile;
	std::istreambuf_iterator<char> beginfile(is);

	std::string bytescode(beginfile, endfile);
		
	std::cout << bytescode << std::endl;

	for (auto&& c:bytescode)
	{
		std::cout << c ;
	}

	bool finish = false;
	
	auto begin = bytescode.begin();
	auto end   = bytescode.end();

	while (!finish)
	{
		std::vector<int> ints;
		auto eol = std::find_if(begin, end, [](auto c){return c=='\n';});
		std::stringstream ss(std::string(begin, eol));
		int read = 0;
		
		while (ss >> read) 
			ints.push_back(read);
		std::cout << "===== "  << ints.size() << "\n";
		for (auto i: ints)
			std::cout << i << std::endl;
		begin = eol + 1;
	}
}
