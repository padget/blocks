#ifndef __blocks_parser_hpp__
#define __blocks_parser_hpp__

#include "model.hpp"
#include <optional>

namespace blocks
{

  template<typename iterator>
    std::optional<argument> 
    parse_argument(
        iterator begin, 
        iterator eol)
    {
      if (begin == eol)
      {
        return std::nullopt;
      }

      auto&& tk = *begin;

      if (tk.type == token_type::ARGNAME 
          or tk.type == token_type::ARGNUMBER
          or tk.type == token_type::ARGSTRING)
      {
        argument arg;

        arg.value = {tk.begin, tk.end};
        begin++;

        if (begin != eol)
        {
          auto&& tk2 = *begin;
          if (tk2.type == token_type::ARGTYPE)
          {
            arg.type = {tk2.begin, tk2.end};
          }
        }

        return arg;
      }

      return std::nullopt;
    }

  template<typename iterator>
    command parse_command(
        iterator begin,
        iterator eol)
    {
      command cmd; 

      if (begin == eol)
      {
        return cmd;
      }

      if ((*begin).type == token_type::CMDNAME) 
      {
        auto&& name = *begin;
        cmd.name = {name.begin, name.end};
        begin++;
      }
      else
      {
        return cmd;
      }

      while (begin != eol)
      {
        argument arg;

        auto&& tk = *begin;
        if (tk.type == token_type::BLANK)
        {
          begin++; 
          continue;
        }

        auto&& opta = parse_argument(begin, eol);
        if (opta.has_value())
        {
          cmd.args.push_back(opta.value());
          begin++;
          continue;
        }

        // TODO que faire si on a rien detecter du tout !


        return cmd;
      }
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

      return cmds;
    }
}


#endif
