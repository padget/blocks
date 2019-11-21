#include <iostream>
#include <vector>
#include <string> 

int main(int argc, char const *argv[])
{
  std::string source = "add a b#int\n"
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
 
  std::vector<command> cmds;

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
        t.value = "\n";
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


    command cmd;
    std::vector<token>::iterator tokens_begin = tokens.begin();
    std::vector<token>::iterator tokens_end = tokens.end();

    while (tokens_begin != tokens_end)
    {
      /* bypass space tokens */
      while (tokens_begin != tokens_end and (*tokens_begin).type == "space")
      {
        tokens_begin++;
      }

      /* if only an eol then by pass this */
      if (tokens_begin != tokens_end and (*tokens_begin).type == "eol") {
        tokens_begin++;
        continue;
      }

      /* detect name of the command */
      if (tokens_begin != tokens_end and (*tokens_begin).type == "name")
      {
        cmd.name = (*tokens_begin).value;

        /* now detect arguments of the current command */
        bool has_argument = true;
        while (tokens_begin != tokens_end and has_argument)
        {
          /* before each args we must bypass space tokens */
          while (tokens_begin != tokens_end and (*tokens_begin).type == "space")
          {
            tokens_begin++;
          }

          /* we can now detect each argument */
          if (tokens_begin != tokens_end)
          {
            auto &&type = (*tokens_begin).type;
            auto &&value = (*tokens_begin).value;

            if (type == "number")
            {
              cmd.args.push_back(argument{value, "number"});
              tokens_begin++;
              continue;
            }
            else if (type == "name")
            { /* here we can have just a name or a name with tag (<name>#<tag>)*/
              auto &&arg_name = (*tokens_begin).value;
              tokens_begin++;
              if (tokens_begin != tokens_end)
              {
                if ((*tokens_begin).type == "tag")
                {
                  tokens_begin++;
                  if (tokens_begin != tokens_end and (*tokens_begin).type == "name")
                  {
                    /* here we have a name and a tag */
                    auto &&arg_tag = (*tokens_begin).value;
                    cmd.args.push_back(argument{arg_name, arg_tag});
                    tokens_begin++;
                    continue;
                  }
                  else
                  {
                    /* here we have an error !! */
                    std::cerr << "erreur dans l'ecriture d'une commande\n";
                    std::exit(EXIT_FAILURE);
                  }
                }
                else
                {
                  /* here we have just a name with no tag */
                  cmd.args.push_back(argument{arg_name});
                  continue;
                }
              }
              else
              {
                /*we have just a name and after end of flow*/
                cmd.args.push_back(argument{arg_name});
              }
            }
            else if (type == "dollard")
            {
              /* we are in the case of '$$' */
              tokens_begin++;
              if (tokens_begin != tokens_end && (*tokens_begin).type == "dollard") 
              {
                cmd.args.push_back(argument{"$$"});
                tokens_begin++;
                continue;
              }
            }
            else
            {
              // nothing
              std::cout << "has no argument" << std::endl;
              has_argument = false;
            }
          }
        } // End while has_argument
      } // End if command has a name
      else
      {
        /* a line with no name but other type of token is an error */
        std::exit(EXIT_FAILURE);
      }
    }

    cmds.push_back(cmd);
  } // For each line

  return EXIT_SUCCESS;
}
