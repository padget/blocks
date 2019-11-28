#include <iostream>
#include <vector>
#include <string> 
#include <map>
#include <functional>


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


std::vector<token> scan_source(const std::string& src);
std::vector<command> parse_tokens(const std::vector<token>& tokens);

int main(int argc, char const *argv[])
{
  std::string source = 
    "let a#int 12\n"
    "add a 13#int\n"
    "add $$ 12\n"
    "minus $$ 1\n"
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

  std::vector<command> cmds;

  for (const std::string &line : lines)
  {
    std::vector<token> tokens = scan_source(line); 

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
                cmd.args.push_back(argument{arg_name, ""});
                continue;
              }
            }
            else
            {
              /*we have just a name and after end of flow*/
              cmd.args.push_back(argument{arg_name, ""});
            }
          }
          else if (type == "dollard")
          {
            /* we are in the case of '$$' */
            tokens_begin++;
            if (tokens_begin != tokens_end && (*tokens_begin).type == "dollard") 
            {
              cmd.args.push_back(argument{"$$", ""});
              tokens_begin++;
              continue;
            }
          } 
          else if (type == "string") 
          {
            cmd.args.push_back(argument{value, "string"});
            tokens_begin++; 
            continue;
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

  /* now we have commands. We can check if each of 
   * them is known and correctly used */
  std::cout << "coucou1" << std::endl;
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

  std::map<std::string, command_definition> cmddefs;

  /* commencons par batir les definitions de commandes natives */

  cmddefs.insert({"add", {"add", "int", {{"a", "int"}, {"b", "int"}}}});
  cmddefs.insert({"minus", {"minus", "int", {{"a", "int"}, {"b", "int"}}}});
  cmddefs.insert({"divide", {"divide", "int", {{"a", "int"}, {"b", "int"}}}});
  cmddefs.insert({"multiply", {"multiply", "int", {{"a", "int"}, {"b", "int"}}}});
  cmddefs.insert({"mod", {"mod", "int", {{"a", "int"}, {"b", "int"}}}});
  cmddefs.insert({"neg", {"neg", "int", {{"a", "int"}}}});
  cmddefs.insert({"print", {"print", "void", {{"a", "any"}}}});
  cmddefs.insert({"let", {"let", "void", {{"name", "any"}, {"value", "int"}}}}); // TODO take any as any-type in inference process

  /* Nous avons les definitions des commandes natives au langage blocks 
   * Nous pouvons maintenant vérifier que les commandes sont correctement utilisée. 
   * Pour cela nous commencerons par voir si les noms des commandes utilisé sont bien
   * présents dans le dictionaires de commandes */

  for (auto&& cmd : cmds) 
  {
    if (cmddefs.count(cmd.name) != 1)
    {
      std::cerr << "attention, commande non définie : " << cmd.name << "\n";
      std::exit(EXIT_FAILURE);
    } 
  }
  std::cout << "coucou2\n";
  /* Maintenant que nous savons que chaque commande utilisée existe, nous allons
   * regardé si celle-ci est correctement utilisées en termes de typage des données. */

  /* Commençons donc par déterminé le type de chaque arguments par inférence sur la valeur
   * ou bien sur directement donnée par le tag de l'argument */

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
            argument.tag = "int";
          }
          else if ('0'<=first and first<='9') 
          {/* l'argument est un nombre */
            argument.tag = "int"; /* j'ajoute le tag par inférence sur la valeur */
          }
          else if ('"' == first)
          { /* l'argument est une string */
            argument.tag = "string";
          }
          else if ('$' == first)
          {/* l'argument fait référence au type retour de la commande précédente */
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

  std::cout << "coucou3\n";

  /* maintenant que le type de chaque argument est défini, 
   * nous pouvons commencer l'execution des commandes */

  /* commencons par regarder si chaque commande utilisée est correctement
   * utilisée du point de vue de sa signature : nombre d'arguments et 
   * leur type respectif ainsi que l'ordre des arguments */


  for (auto&& cmd : cmds)
  {
    auto&& def = cmddefs.at(cmd.name);

    if (def.params.size() != cmd.args.size())
    {
      std::cerr << "sur la commande " << cmd.name << " : \n";
      std::cerr << "nb args "<< cmd.args.size() << " def " << def.params.size() << "\n";
      std::cerr << "le nombre d'argument n'est pas";
      std::cerr << " identique au nombre de paramètres attendu \n";
      std::exit(EXIT_FAILURE);
    }
  }

  for (auto&& cmd: cmds)
  {
    auto&& def = cmddefs.at(cmd.name);

    for (unsigned i=0; i<def.params.size(); ++i)
    {
      auto&& defarg = def.params[i];
      auto&& arg    = cmd.args[i];

      if (defarg.type != "any" and arg.tag != defarg.type)
      {
        std::cerr << cmd.name << "\n";
        std::cerr << "signature non correspondante \n";
        std::exit(EXIT_FAILURE);
      }
    }
  }

  /* chaque commande utilise le bon nombre d'argument et les bons types */
  /* nous pouvons maintenant mettre en place un mapping entre le nom de chaque commande et 
   * un fonction native C++ permettant l'interprétation de cette commande */

  std::map<std::string, int> lets; 

  auto add = [] (int a, int b) -> int {return a+b;};
  auto minus = [] (int a, int b) -> int {return a-b;};
  auto multiply = [] (int a, int b) -> int {return a*b;};
  auto divide = [] (int a, int b) -> int {return a/b;};
  auto mod = [] (int a, int b) -> int {return a%b;};
  auto print = [] (int a) -> void {std::cout << a;};
  auto let = [&lets] (const std::string& name, int value) {lets[name] = value;};

  /* commencons par la commande add. elle prend en entrée deux int a et b 
   * on va donc enregistrer dans une map le nom de la commande ainsi que 
   * la fonction proprepement dite associée !*/
  int $$ = 0;

  for (auto &&cmd : cmds)
  {
    auto const &name = cmd.name;
    std::vector<int> ints;

    for (auto&& arg : cmd.args)
    {
      if (arg.value == "$$")
      {
        ints.push_back($$);
      }
      else  
      {
        auto first = *arg.value.begin();

        if ('a' <= first and first <= 'z') 
        {
          if (cmd.name != "let") 
          {
            ints.push_back(lets.at(arg.value)); 
          }
        }
        else 
        {
          ints.push_back(std::stoi(arg.value));
        }
      }
    }

    if (name=="add") 
    {
      $$ = add(ints[0], ints[1]);
    } 
    else if (name == "print")
    {
      print(ints[0]);
    }
    else if (name == "minus")
    {
      $$ = minus(ints[0], ints[1]);
    }
    else if (name == "multiply")
    {
      $$ = multiply(ints[0], ints[1]);
    }
    else if (name == "divide")
    {
      $$ = divide(ints[0], ints[1]);
    }
    else if (name == "mod")
    {
      $$ = mod(ints[0], ints[1]);
    }
    else if (name == "let") 
    {
      auto varname=cmd.args[0].value;
      auto varvalue=std::stoi(cmd.args[1].value);
      let(varname, varvalue);
    }
  }

  std::cout << "coucou4\n";
  std::cout << "EXIT_SUCCESS";

  return EXIT_SUCCESS;
}

std::vector<token> scan_source(const std::string& source) 
{
  std::vector<token> tokens;

  auto begin = source.begin();
  auto end   = source.end();
  auto step  = source.begin();

  while (begin != end) 
  {
    if (*begin == '#') 
    {
      tokens.push_back({"tag", "#"});
      begin++;
      step = begin;
    } 
    else if (*begin == '$')
    {
      tokens.push_back({"dollard", "$"});
      begin++;
      step = begin;
    }
    else if (*begin == ' ') 
    {
      /* FIXME pour l'instant nous ne 
       * prenons pas en compte l'indentation 
       * de début de ligne */
      begin++;
      step = begin;
    }
    else if (*begin == '\n') 
    {
      tokens.push_back({"eol", "\n"});
      begin++;
      step = begin;
    } 
    else if (*begin == '"')
    {
      begin++;

      while (begin != end 
          and *begin != '"')
      {
        begin++;
      }

      if (begin != end and *begin == '"')
      {
        tokens.push_back({"string", {step, begin}});
        begin++;
        step = begin; 
      } 
      else
      {
        begin = step;
      }
    }
    else if ('a' <= *begin and *begin <= 'z')
    {
      begin++;

      while (begin != end 
          and 'a' <= *begin 
          and *begin <= 'z')
      {
        begin++;
      }

      tokens.push_back({"name", {step, begin}});
      step = begin;
    }
    else if ('0' <= *begin and *begin <= '9')
    {
      begin++;

      while (begin != end 
          and '0' <= *begin 
          and *begin <= '9')
      {
        begin++;
      }

      tokens.push_back({"int", {step, begin}});
      step = begin;
    }
    else 
    {
      tokens.push_back({"error", {begin, begin + 1}});
      begin++;
      step = begin;
    }
  }

  return tokens;
}


std::vector<command> parse_tokens(const std::vector<token>& tokens) 
{
  std::vector<command> commands;

  auto begin = tokens.begin();
  auto end   = tokens.end();
  auto step  = tokens.begin();

  while (begin != end)
  {
    command cmd;

    while (begin != end and (*begin).type != "eol")
    {
      begin++;
    }

    while (step != begin)
    {
      if ((*step).type == "eol")
      {
        step = begin;
      } 
      else if ((*step).type == "name")
      {
        cmd.name = (*step).value;
        step++;

        while (step != begin)
        {
          if ((*step).type == "eol")
          {
            step = begin;
            continue;
          } 
          else if ((*step).type == "int" or (*step).type == "name")
          {
            if ((step+1) != begin and (step+2) != begin) 
            {
              auto tag     = *(step+1);
              auto tagname = *(step+2);

              if (tag.type == "tag")
              {
                if (tagname.type == "name")
                {
                  cmd.args.push_back({(*step).value, tagname.value});
                  step+=3;
                } 
                else
                {
                  std::cerr << "un tag doit être suivi d'un nom\n";
                  std::exit(EXIT_FAILURE);
                }
              } 
              else
              {
                cmd.args.push_back({(*step).value, "int"});
                step++;
              }
            }
          }
          else if ((*step).type == "dollard") 
          {
            auto dollard2 = step+1;

            if (dollard2 != begin and (*dollard2).type == "dollard")
            {
              cmd.args.push_back({"$$", "int"});
              step+=2;
            }
            else 
            {
              std::cerr << "un premier dollard est suivi d'un second dollard\n";
              std::exit(EXIT_FAILURE);
            }
          }
          else if ((*step).type == "string")
          {
            cmd.args.push_back({(*step).value, "string"});
            step++;
          }
          else if ((*step).type == "error") 
          {
            std::cerr << "le token courant n'est pas reconnu par le parsing\n";
            std::exit(EXIT_FAILURE);
          }
          else 
          {
            std::cerr << "oops\n";
            std::exit(EXIT_FAILURE);
          }
        }
      }
    }
    
    commands.push_back(cmd);
    step = begin;
  }


  return commands;
}
