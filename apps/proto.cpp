#include <iostream>

#include "../libs/cmdl/cmdl.hpp"
#include "../libs/containers.hpp"
#include <bitset>
#include <cstdint>
#include <array>

using namespace libs;
using namespace libs::cmdl;

template <std::size_t nb>
constexpr std::uint8_t first_mask =
    ~((std::uint8_t)0b11111111 >> nb);

template <std::size_t nb>
constexpr std::uint8_t last_mask =
    (std::uint8_t)~first_mask<8 - nb>;

std::uint8_t
mask(
    const std::uint8_t u8,
    const std::uint8_t m)
{
  return u8 & m;
}

int main(int argc, char **argv)
{
  // specify("log",
  //         flag("[graph]"),
  //         opt("[verbose=<v|vv|vvv|vvvv>]"),
  //         opt("[user=<email>]"));

  return EXIT_SUCCESS;
}