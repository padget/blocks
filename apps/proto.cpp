#include <iostream>

#include "../libs/vector.hpp"
#include "../libs/string.hpp"

using namespace libs;

int main(int argc, char **argv)
{
  vector<int> ints;

  std::cout << size(ints) << std::endl;

  vector<int> ints2(3);

  std::cout << size(ints2) << std::endl;

  set(ints2, 0, 1);

  std::cout << get(get(ints2, 0)) << std::endl;

  vector<int> ints3 = static_cast<vector<int> &&>(ints2);

  std::cout << size(ints2) << std::endl;
  std::cout << get(get(ints3, 0)) << std::endl;

  vector<int> ints4({1, 2, 3, 4});

  std::cout << size(ints4) << std::endl;
  std::cout << get(get(ints4, 2)) << std::endl;

  std::cout << "coucou" << std::endl;

  string str = nullterm("hello");

  std::cout << std::boolalpha << starts_with(str, nullterm("he")) << std::endl;
  std::cout << std::boolalpha << ends_with(str, nullterm("he")) << std::endl;
  std::cout << std::boolalpha << ends_with(str, nullterm("lo")) << std::endl;
  
  return EXIT_SUCCESS;
}