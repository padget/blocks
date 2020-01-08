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
  auto end = str.end();
  auto iseq = [](auto c){return c=='=';};
  auto equal = std::find_if(begin, end, iseq);
  auto value = std::string(str.begin(), equal);
  auto arg =  std::string{equal+1, str.end()};
  return {value, arg};
}

std::map<std::string, argument> 
from_args(int argc, char** argv)
{
  std::cout << "from args" << std::endl;
  std::map<std::string, argument> args;;
  std::vector<std::string> sargs;
  int i = argc-1;

  std::cout << argc << std::endl;
  
  while (i>=1) 
  {
    sargs.push_back(argv[i]);
    i--;
  }
  
  std::cout << "coucou1" << std::endl;

  for (std::string& arg:sargs)
  {
    std::cout << arg << std::endl;
    auto&& pair = split_eq(arg);
    auto&& name = pair.first;
    auto&& value = pair.second;
    args.insert({name, {name, value}});
  }

  std::cout << "coucou 2" << std::endl;

  return args;
}
}

#endif
