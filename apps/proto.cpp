#include <iostream>

#include "../libs/vector.hpp"
#include "../libs/string.hpp"
#include <vector>
using namespace libs;

int main(int argc, char **argv)
{
  vector<int> ints;

  std::cout << size(ints) << std::endl;

  vector<int> ints2(3);

  std::cout << size(ints2) << std::endl;
  push(ints2, 1);
  push(ints2, 3);
  push(ints2, 3);


  std::cout << size(ints2) << std::endl;

  auto b = begin(ints2);
  auto e = end(ints2);
  
  while (not equals(b, e))
  {
    std::cout << get(b) << std::endl;
    b = next(b);
  }

  return EXIT_SUCCESS;
}