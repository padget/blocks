#include <iostream>
#include <vector>
#include <string> 
#include <map>
#include <functional>


int main(int argc, char const *argv[])
{
  std::string source = 
    "add 12 13#int\n"
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
  
  std::cout << "--- building of commands \n";

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
          t.type = "int";
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

    for (auto&& tk : tokens)
    {
      std::cout << tk.type << " " << tk.value << "\n";
    }

    /* Nous avons ici une liste de token pour une ligne en particulier
       Nous pouvons donc essayer de la convertir en commande */

    command cmd;
    std::vector<token>::iterator tokens_begin = tokens.begin();
    std::vector<token>::iterator tokens_end = tokens.end();

    /* bypass space tokens */
    while (tokens_begin != tokens_end and (*tokens_begin).type == "space")
    {
      tokens_begin++;
    }

    /* if only an eol then by pass this */
    if (tokens_begin != tokens_end and (*tokens_begin).type == "eol") 
    {
      tokens_begin++;
      continue;
    }

    /* detect name of the command */
    if (tokens_begin != tokens_end and (*tokens_begin).type == "name")
    {
      cmd.name = (*tokens_begin).value;
      tokens_begin++;

      /* now detect arguments of the current command */
      bool has_argument = true;

      while (tokens_begin != tokens_end and has_argument)
      {
        /* before each args we must bypass space tokens */
        while (tokens_begin != tokens_end and (*tokens_begin).type == "space")
        {
          tokens_begin++;
        }

        if (tokens_begin != tokens_end and (*tokens_begin).type == "eol")
        {
          /* we are a the end of the line so we can by pass */
          tokens_begin++;
          continue;
        }

        /* we can now detect each argument */
        if (tokens_begin != tokens_end)
        {
          auto &&type = (*tokens_begin).type;
          auto &&value = (*tokens_begin).value;

          if (type == "int")
          {
            cmd.args.push_back(argument{value, "int"});
            tokens_begin++;
            continue;
          }
          else if (type == "name")
          { 
            /* here we can have just a name or a name with tag (<name>#<tag>)*/
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
            has_argument = false;
          }
        }
      } // End while has_argument
    } // End if command has a name
    else
    {
      /* a line with no name but other type of token is an error */
      std::cerr << "la ligne présente des tokens qu'elle ne devrait pas avoir\n";
      std::exit(EXIT_FAILURE);
    }


    cmds.push_back(cmd);
  } // For each line

  std::cout << "#--- end of building of commands\n";

  /* now we have commands. We can check if each of 
   * them is known and correctly used */
  /**
    TODO nous devons construire un dictionnaire de commandes
    Pour cela je vais mettre en place une structure commande_definition
    qui contiendra le nom de la commande ainsi que les arguments et leur 
    type qu'elle peut prendre. 
    */
  struct parameter
  {
    /* nom du paramètre */
    std::string name;
    /* type du paramètre */
    std::string type;
  };

  struct command_definition 
  {
    /* nom de la commande */
    std::string name;

    /* type de retour de la commande */
    std::string rtype;

    /* ensemble des paramètres de la commande */
    /* l'ordre est important et est à respecter 
       lors de l'appel de la dite commande */
    std::vector<parameter> params;
  };

  std::cout << "---- building of commands dictonnary\n";

  std::map<std::string, command_definition> cmddefs;

  /* commencons par batir les definitions de commandes natives */

  cmddefs.insert({"add", {"add", "int", {{"a", "int"}, {"b", "int"}}}});

  cmddefs.insert({"minus", {"minus", "int", {{"a", "int"}, {"b", "int"}}}});

  cmddefs.insert({"divide", {"divide", "int", {{"a", "int"}, {"b", "int"}}}});

  cmddefs.insert({"multiply", {"multiply", "int", {{"a", "int"}, {"b", "int"}}}});

  cmddefs.insert({"mod", {"mod", "int", {{"a", "int"}, {"b", "int"}}}});

  cmddefs.insert({"neg", {"neg", "int", {{"a", "int"}}}});

  cmddefs.insert({"print", {"print", "void", {{"a", "int"}}}});

  /* Nous avons les definitions des commandes natives au langage blocks 
   * Nous pouvons maintenant vérifier que les commandes sont correctement utilisée. 
   * Pour cela nous commencerons par voir si les noms des commandes utilisé sont bien
   * présents dans le dictionaires de commandes */
  
  std::cout << "#--- end of building commands dictonnary\n";
  std::cout << "---- check if each command using exists in dictonnary\n";

  for (auto&& cmd : cmds) 
  {

    if (cmddefs.count(cmd.name) != 1)
    {
      std::cerr << "attention, commande non définie : " << cmd.name << "\n";
      std::exit(EXIT_FAILURE);
    } 
  }

  std::cout << "#--- end of using command existing\n";

  /* Maintenant que nous savons que chaque commande utilisée existe, nous allons
   * regardé si celle-ci est correctement utilisées en termes de typage des données. */

  /* Commençons donc par déterminé le type de chaque arguments par inférence sur la valeur
   * ou bien sur directement donnée par le tag de l'argument */
  
  std::cout << "---- check of arguments types\n";

  for (auto&& cmd : cmds) 
  {
    auto&& arguments = cmd.args;
    for (auto&& argument : arguments)
    {
      if (argument.tag.empty()) 
      {
        /* l'argument n'a pas de tag et donc le type est a devinée en fonction de sa valeur */
        if (!argument.value.empty()) 
        {
          auto first = argument.value[0];
          if ('a'<=first and first<='z') 
          {/* l'argument est un nom */
            /* pour l'instant on ne gère pas les variables intra programme */
            /* TODO ajouter la commande <let: var#type valeur> */
          }
          else if ('0'<=first and first<='9') 
          {/* l'argument est un nombre */
            /* pour l'instant nous ne gérons que les nombres entiers ! */
            /* TODO ajouter la possibilité de mettre des nombres floattant */
            argument.tag = "int"; /* j'ajoute le tag par inférence sur la valeur */
          }
          else if ('"' == first)
          { /* l'argument est une string */
            /* pour l'instant les tokens string ne sont pas reconnu */
            /* TODO reconnaitre les type string en tant que token */
            argument.tag = "string";
          }
          else if ('$' == first)
          {/* l'argument fait référence au type retour de la commande précédente */
            /* pour l'instant il s'agit que de type int */
            /* TODO faire l'inférence sur le type de la commande précédente */
            argument.tag = "int";
          }
          else 
          { /* si on arrive ici c'est que les tentatives d'inférence ont échoué ! */
            std::cerr << "le type ne peut être déterminé\n";
            std::exit(EXIT_FAILURE);
          }
        }
        else 
        {
          std::cout<<"un argument doit avoir une valeur\n";
          std::exit(EXIT_FAILURE);
        }
      }
    }
  }

  std::cout << "#--- end of check argument types\n";


  /* maintenant que le type de chaque argument est défini, 
   * nous pouvons commencer l'execution des commandes */
  
  /* commencons par regarder si chaque commande utilisée est correctement
   * utilisée du point de vue de sa signature : nombre d'arguments et 
   * leur type respectif ainsi que l'ordre des arguments */
  for (auto&& cmd: cmds)
  {
    auto&& def = cmddefs.at(cmd.name);
    
    if (def.params.size() != cmd.args.size())
    {
      std::cerr << "le nombre d'argument n'est pas identique au nombre de paramètres attendu \n";
      std::exit(EXIT_FAILURE);
    }

    for (int i=0; i<def.params.size(); ++i)
    {
      auto&& defarg = def.params[i];
      auto&& arg    = cmd.args[i];

      if (arg.tag != defarg.type)
      {
        std::cerr << "signature non correspondante \n";
        std::exit(EXIT_FAILURE);
      }
    }
  }

  /* chaque commande utilise le bon nombre d'argument et les bons types */
  /* nous pouvons maintenant mettre en place un mapping entre le nom de chaque commande et 
   * un fonction native C++ permettant l'interprétation de cette commande */

  std::map<std::string, std::function<int(int, int)>> fcmds;
  fcmds.insert({"add", [] (int a, int b) -> int {return a+b;}});

  std::cout << fcmds.at("add")(1, 2) << "\n";
  /* commencons par la commande add. elle prend en entrée deux int a et b 
   * on va donc enregistrer dans une map le nom de la commande ainsi que 
   * la fonction proprepement dite associée !*/

  return EXIT_SUCCESS;
}
