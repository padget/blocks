#ifndef __arguments_hpp__
#define __arguments_hpp__

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

#define let(name, type, value) #type #name=#value

namespace cxx
{
	struct argument 
	{
		std::string name;
		std::string value;
		//		TODO pour l'instant nous ne g√rerons pas les 
		//		description dans le module de gestion des 
		//		arguments du programme. Donc pas de page help.
		//		std::string description;
	};

	std::pair<std::string, std::string> 
		split_eq(const std::string& str)
		{
			auto begin = str.begin();
			auto end   = str.end();
			auto iseq  = [](auto c){return c=='=';};
			auto equal = std::find_if(begin, end, iseq);
			auto name  = std::string(str.begin(), equal);
			auto value = std::string{equal+1, str.end()};

			return {name, value};
		}

	std::map<std::string, argument> 
		from_args(int argc, char** argv)
		{
			std::map<std::string, argument> args;;
			std::vector<std::string> sargs;

			for (int i=1; i<argc; i++)
				sargs.push_back(argv[i]);
				
			auto barg = sargs.begin();
			auto earg = sargs.end();

			while (barg != earg)
			{
				auto name = *barg;
				barg++;

				if (barg != earg)
				{
					auto value = *barg;
					barg++;
					args.insert({name, {name, value}});
				}
			}


			return args;
		}
}

#endif
