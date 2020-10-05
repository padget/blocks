#include <iostream>
#include <string>
#include "../libs/base64.h"
#include <string_view>

std::string
crypt(
    std::string_view txt,
    std::string_view pwd)
{

  std::string trs(txt.size(), '\0');

  for (std::size_t i = 0; i < txt.size(); ++i)
    for (const char &p : pwd)
      trs[i] = txt[i] + p;

  return trs;
}

std::string decrypt(
    std::string_view txt,
    std::string_view pwd)
{
  std::string trs(txt.size(), '\0');
  for (std::size_t i = 0; i < txt.size(); ++i)
    for (const char &p : pwd)
      trs[i] = txt[i] - p;
  return trs;
}

int main(int argc, char **argv)
{
  if (argc == 3)
  {
    std::string pwd = argv[1];
    std::string txt = argv[2];

    std::string trs = crypt(txt, pwd);

    std::cout << trs << '\n';
    std::cout << base64_encode(trs, true) << '\n';
    std::cout << base64_decode(base64_encode(trs, true)) << '\n';

    std::cout << decrypt(trs, pwd);

    return EXIT_SUCCESS;
  }

  return EXIT_FAILURE;
}