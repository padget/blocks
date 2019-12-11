#ifndef __blocks_parser_hpp__
#define __blocks_parser_hpp__

#include "model.hpp"

namespace blocks
{
  template<typename iterator>
  command parse_command(
      iterator begin,
      iterator eol)
  {
    command cmd; 

    return cmd;
  }

  template<typename iterator>
  commands parse_commands(
      iterator begin, 
      iterator end)
  {
    struct line 
    {
      iterator begin; 
      iterator eol;
    };

    using lines = std::vector<line>;

    lines ls;
    auto step = begin;
    
    while (begin != end)
    {
      if ((*begin).type == token_type::EOL)
      {
        begin++;
        ls.push_back({step, begin});
        step = begin;
      }
      else 
      {
        begin++;
      }
    }
    
    commands cmds;

    for (auto&& l:ls)
    {
      auto lb = l.begin;
      auto le = l.eol;
      auto&& cmd = parse_command(lb, le);
      cmds.push_back(cmd);
    }
    
    return cmds
  }
}


#endif
