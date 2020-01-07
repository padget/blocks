#ifndef __blocks_command_building_hpp__
#define __blocks_command_building_hpp__

#include "model.hpp"

namespace blocks
{


struct coordinates
{
  std::size_t line;
  std::size_t column;
};


/* FIXME NOT IMPLEMENTED */
command build_command(const std::string& line,
                      const coordinates& coord);
/* FIXME NOT IMPLEMENTED */
commands build_commands(const std::string& src,
                        const coordinates& coord);

}

#endif

