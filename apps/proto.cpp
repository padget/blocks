#include <iostream>

#include "../libs/vector.hpp"
#include "../libs/string.hpp"
#include "../libs/list.hpp"
#include "../libs/algorithm.hpp"

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

  list<int> ints3;
  push(ints3, 2);
  push(ints3, 2);
  push(ints3, 4);
  push(ints3, 2);
  push(ints3, 2);

  std::cout << size(ints3) << std::endl;

  auto b3 = begin(ints3);
  auto e3 = end(ints3);

  while (not equals(b3, e3))
  {
    std::cout << get(b3) << std::endl;
    b3 = next(b3);
  }

  list<int> ints4;
  
  push(ints4, 2);
  push(ints4, 2);
  push(ints4, 4);
  push(ints4, 2);
  push(ints4, 2);

  std::cout << std::boolalpha << none(begin(ints4), end(ints4), [](const int &i) {
    return i == 3;
  }) << std::endl;

  return EXIT_SUCCESS;
}