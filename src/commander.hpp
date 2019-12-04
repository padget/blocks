#ifndef __blocks_commander_hpp__
#define __blocks_commander_hpp__

#include <optional>

template<typename iterator>
struct token_line 
{
  iterator begin;
  iterator eol;
};

namespace std
{
  template<typename iterator>
    iterator begin(
        const token_line<iterator>& tl) 
    {
      return tl.begin;
    }

  template<typename iterator>
    iterator end(
        const token_line<iterator>& tl)
    {
      return tl.eol;
    }
}


struct liner
{
  template<typename iterator>
    std::vector<token_line<iterator>>
    from_tokens(iterator begin, iterator end)
    {
      std::vector<token_line<iterator>> lines;

      auto step = begin;

      while (begin != end)
      {
        bool is_eol = false;  

        if ((*begin).type == "eol")
        {
          is_eol = true;
        }

        begin++;

        if (is_eol)
        {
          lines.push_back({step, begin});
          step = begin;
        } 
      }

      return lines;
    }
};

struct namer
{
  template<typename iterator>
  std::optional<std::string> 
  from_tokens(const token_line<iterator>& line)
  {
    if (line.begin == line.eol)
      return std::nullopt;
    
    if ((*line.begin).type == "name")
      return (*line.begin).value;

    return std::nullopt;
  }
};

struct argumenter
{
  template<typename iterator>
    std::optional<argument>
    from_tokens(const token_line<iterator>& line)
    {
      auto begin = line.begin;
      auto eol   = line.eol;

      if (begin == eol)
        return std::nullopt;

      argument arg;
      bool has_value = false;
      
      if ((*begin).type == "name")
      {
        has_value = true;
        arg.value = (*begin).value;
        begin++;
      }
      else if ((*begin).type == "int")
      {
        has_value = true;
        arg.value = (*begin).value;
        begin++;
      }
      else if ((*begin).type == "$$")
      {
        has_value = true;
        arg.value = "$$";
        begin++;
      }

      if (has_value)
      {
        if (begin == eol)
        {
          return arg;
        }

        bool can_have_type = false;

        if ((*begin).type == "tag")
        {
          begin++;
          can_have_type = true;
        }
        
        if (begin == eol)
        {
          // TODO we have a problem (name|number|$$)#-O-
          return std::nullopt;OB
        }

        if (can_have_type)
        {
          if ((*begin).type == "name")
          {
            arg.type = (*begin).value;
          }
        }
      }

      return arg;
    }
};

struct commander
{
  namer n;
  argumenter a;
  template<typename iterator>
    std::optional<command> 
    from_tokens(const token_line<iterator>& line)
    {
      if (line.begin == line.eol)
        return std::nullopt;

      auto&& name = n.from_tokens(line);
      auto&& args = a.from_tokens(line);

    }
};

#endif
