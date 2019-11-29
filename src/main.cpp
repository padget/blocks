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



template<
  typename literal>
bool between(
    literal a, 
    literal min, 
    literal max)
{
  return min <= a and a <= max;
}

template<
typename object, 
         typename value, 
  typename ... values> 
bool eq_or(
    object&& o, 
    value&& v, 
    values&&... vs)
{
  return std::forward<object>(o) == std::forward<value>(v) 
    or eq_or(std::forward<object>(o), std::forward<values>(vs)...);
}

  template<typename object>
bool eq_or(object&&)
{
  return false; 
}

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

  std::vector<token> tokens = scan_source(source);
  std::vector<command> cmds = parse_tokens(tokens);

  /* now we have commands. We can check if each of 
   * them is known and correctly used */
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

  std::cout << "EXIT_SUCCESS";

  return EXIT_SUCCESS;
}

std::vector<token> scan_source(
    const std::string& source) 
{
  std::vector<token> tokens;
  token t;

  auto begin = source.begin();
  auto end   = source.end();
  auto step  = source.begin();

  while (begin != end) 
  {
    if (*begin == '#') 
    {
      t.type = "tag";
      t.value = "#";
      tokens.push_back(t);
      begin++;
      step = begin;
    } 
    else if (*begin == '$')
    {
      t.type = "dollard";
      t.value = "$";
      tokens.push_back(t);
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
      t.type = "eol"; 
      t.value = "\n";
      tokens.push_back(t);
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
        t.type = "string";
        t.value = {step, begin};
        tokens.push_back(t);
        begin++;
        step = begin; 
      } 
      else
      {
        begin = step;
      }
    }
    else if (between(*begin, 'a', 'z'))
    {
      begin++;

      while (begin != end 
          and 'a' <= *begin 
          and *begin <= 'z')
      {
        begin++;
      }

      t.type = "name"; 
      t.value = {step, begin};
      tokens.push_back(t);
      step = begin;
    }
    else if (between(*begin, '0', '9'))
    {
      begin++;

      while (begin != end 
          and between(*begin, '0', '9'))
      {
        begin++;
      }

      t.type = "int";
      t.value = {step, begin};
      tokens.push_back(t);
      step = begin;
    }
    else 
    {
      t.type = "error"; 
      t.value = {begin, begin+1};
      tokens.push_back(t);
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
  auto numline = 1;

  while (begin != end)
  {
    auto eol = begin;

    command cmd;
    argument arg;

    bool has_name = false;

    while (eol != end and (*eol).type != "eol")
    {
      eol++;
    }

    numline++;

    if (eol != begin) 
    {
      if ((*begin).type == "name")
      {
        has_name = true;
        cmd.name = (*begin).value;
        begin++;
      }
    }

    if (!has_name)
    {
      std::cerr << "syntax error : ";
      std::cerr << " (line " << numline << ") ";
      std::cerr << "a command must begin by a <cmd-name>";
      std::exit(EXIT_FAILURE);
    }

    while (begin != eol)
    {
      bool is_name = false;
      bool is_int = false;

      if ((*begin).type == "name")
      {
        is_name = true; 
        arg.value = (*begin).value;
        begin++;
      } 
      else if ((*begin).type == "int")
      {
        is_int = true;
        arg.value = (*begin).value;
        begin++;
      }

      bool can_have_tag = false;

      if (is_name or is_int)
      {
        if (begin != eol 
            and (*begin).type == "tag")
        {
          can_have_tag = true;
          begin++;
        }
      }

      if (can_have_tag)
      {
        if (begin != eol 
            and (*begin).type == "name")
        {
          arg.tag = (*begin).value;
          begin++;
        } 
        else
        {
          std::cerr << "syntax error : ";
          std::cerr << "a # must followed by a <tag-name>";
          std::exit(EXIT_FAILURE);
        } 
      }

      if (is_name or is_int)
      {
        cmd.args.push_back(arg);
        continue;
      }

      auto dollard1 = begin;
      auto dollard2 = begin + 1;

      if ((*dollard1).type == "dollard")
      {
        if ((*dollard2).type == "dollard")
        {
          begin+=2;
          arg.value = "$$";
          arg.tag   = "int";
          cmd.args.push_back(arg);
          continue;
        }
        else 
        {
          std::cerr << "syntax error : ";
          std::cerr << "a $ must be followed by $";
          std::exit(EXIT_FAILURE);
        }
      }

      if ((*begin).type == "error")
      {
        std::cerr << "token error : ";
        std::cerr << "the token " << (*begin).value;
        std::cerr << " isn't authorized !\n" ;
        std::exit(EXIT_FAILURE);
      }
    }

    begin++;
    commands.push_back(cmd);
  }

  return commands;
}
