#include "types.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
  std::string source = "let a#int 12\n"
                       "let b#int 12\n"
                       "add a b\n"
                       "print $$\n";
  std::cout << source << "\n";

  std::vector<std::string> lines;
  std::string::iterator source_begin = source.begin();
  std::string::iterator source_end = source.end();
  std::string::iterator source_cursor = source.begin();

  while (source_cursor != source_end)
  {
    if (*source_cursor == '\n')
    {
      std::string line{source_begin, source_cursor + 1};
      lines.push_back(std::move(line));
      source_begin = source_cursor + 1;
    }
    source_cursor++;
  }

  struct token
  {
    std::string type;
    std::string value;
  };

  for (const std::string &line : lines)
  {
    std::vector<token> tokens;
    std::string::const_iterator line_begin = line.begin();
    std::string::const_iterator line_end = line.end();
    std::string::const_iterator line_cursor = line.begin();

    while (line_cursor != line_end)
    {
      token t;
      if (*line_cursor == '#')
      {
        t.type = "tag";
        t.value = "#";
        line_cursor++;
      }
      else if (*line_cursor == '$')
      {
        t.type = "dollard";
        t.value = "$";
        line_cursor++;
      }
      else if (*line_cursor == ' ')
      {
        t.type = "space";
        t.value = " ";
        line_cursor++;
      }
      else if (*line_cursor == '\n')
      {
        t.type = "eol";
        t.type = "\n";
        line_cursor++;
      }
      else
      {
        while (line_cursor != line_end and '0' <= *line_cursor and *line_cursor <= '9')
        {
          line_cursor++;
        }
        if (line_cursor != line_begin)
        {
          t.type = "number";
          t.value = std::string(line_begin, line_cursor);
        }
        else
        {
          while (line_cursor != line_end and 'a' <= *line_cursor and *line_cursor <= 'z')
          {
            line_cursor++;
          }
          if (line_cursor != line_begin)
          {
            t.type = "name";
            t.value = std::string(line_begin, line_cursor);
          }
          else
          {
            t.type = "error";
            t.value = *line_cursor;
            line_cursor++;
          }
        }
      }
      line_begin = line_cursor;
      tokens.push_back(std::move(t));
    }

    /* Nous avons ici une liste de token pour une ligne en particulier
       Nous pouvons donc essayer de la convertir en commande */

    struct argument
    {
      std::string value;
      std::string tag;
    };

    struct command
    {
      std::string name;
      std::vector<argument> args;
    };

    command cmd;
    std::vector<token>::iterator tokens_begin = tokens.begin();
    std::vector<token>::iterator tokens_end = tokens.end();
    std::vector<token>::iterator tokens_cursor = tokens.begin();
    
    while (tokens_begin != tokens_end) 
    {
      
    }
  } // For each line

  return EXIT_SUCCESS;
}