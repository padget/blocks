#ifndef __blocks_native_hpp__
#define __blocks_native_hpp__
#include <vector>

namespace blocks
{
	using memory_case        = std::vector<int>;
	using memory             = std::vector<memory_case>;
	using command_definition = void(std::vector<int> const&, memory&);
	using type_definition    = std::tuple<int, string>;

	constexpr int $$int = 0;

	void add (std::vector<int> const& args, memory& mem) 
	{
		int arg1=args[0];
		int arg2=args[1];
		mem[$$int][0]=arg1+arg2;
	}

	void print(std::vector<int> const& args, memory& mem)
	{
		for(const int&arg:args)
			std::cout<<arg;
	}

	std::vector<type_definition> tn()
	{
		std::vector<type_definition> defs;
		defs.push_back({1, "int"});
		return defs;
	}

	std::vector<command_definition> ci() 
	{
		std::vector<command_definition> defs;
		defs.push_back(&add);
		defs.push_back(&print);
		return defs;
	}
}

#endif
