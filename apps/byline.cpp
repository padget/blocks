#include <iostream>
#include <fstream>
#include <string>

void replaceAll(
    std::string &subject,
    const std::string &search,
    const std::string &replace)
{
  size_t pos = 0;

  while ((pos = subject.find(search, pos)) != std::string::npos)
  {
    subject.replace(pos, search.length(), replace);
    pos += replace.length();
  }
}

int main(int argc, char **argv)
{
  std::string str;

  {
    std::ifstream ifs(argv[1]);
    auto begin = std::istreambuf_iterator<char>(ifs);
    auto end = std::istreambuf_iterator<char>();
    str = std::string(begin, end);
  }

  replaceAll(str, "\\n", "\n");

  std::ofstream ofs(argv[1]);

  ofs << str;

  std::cout << str;
}