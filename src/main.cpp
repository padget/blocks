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
  std::string name;
  std::string type;
};

struct command_definition 
{
  std::string name;
  std::string rtype;
  std::vector<parameter> params;
};

struct context
{
  std::map<std::string, command_definition> definitions;
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

std::vector<token> scan_source(const std::string& src);
std::vector<command> parse_tokens(const std::vector<token>& tokens);
void infer_args_type(std::vector<command>& commands);

bool check_commands_name (
    const std::vector<command> & commands, 
    const context & ctx);

bool check_commands_params(
    const std::vector<command> & commands,
    const context& ctx);


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

  context ctx {cmddefs};

  bool all_names_are_good = check_commands_name(cmds, ctx);

  if (!all_names_are_good)
  {
    std::cerr << "semantic error : ";
    std::cerr << "some commands don't exists\n";
    std::exit(EXIT_FAILURE);
  }
  
  infer_args_type(cmds);
  
  bool all_args_are_good = check_commands_params(cmds, ctx);

  if (!all_args_are_good)
  {
    std::cerr << "semantic error : ";
    std::cerr << "some commands are malformed\n";
    std::exit(EXIT_FAILURE);
  }

 /* maintenant que le type de chaque argument est défini, 
  * nous pouvons commencer l'execution des commandes */

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


std::vector<command> parse_tokens(
    const std::vector<token>& tokens) 
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

// TODO à voir si on devrait pas intégrer ceci directement à la 
// construction de la commande plutôt que de le faire de manière 
// séparée dans le processus de compilation.
void infer_args_type(std::vector<command>& commands)
{
  for (auto && cmd : commands)
  {
    for (auto && arg : cmd.args)
    {
      if (!arg.tag.empty())
      {
        continue;
      }
      
      auto && value = arg.value;
      
      if (!value.empty() and 
          '0' <= value[0] and 
          value[0] <= '9')
      {
        arg.tag = "int";
      } 
      else if (!value.empty() and
          'a' <= value[0] and 
          value[0] 'z')
      {
        arg.tag = "int"; // TODO pour l'instant 
        // les name sont forcément des int. On verra ensuite 
        // pour mettre en place un systeme de variable
        // avec espace de nom et portée des variables !
      } 
      else if (!value.empty() and 
          '$' == value[0])
      {
        // TODO voir pour introspecter la commande précedente 
        // si elle renvoi quelque chose et ainsi de suite 
        // jusqu'à trouver autre chose que void
        arg.tag = "int"; 
      }
      else 
      {
        // TODO voir s'il ne faudrait pas mettre en place un système
        // d'accumulation des erreurs comme pour les autres cas déjà
        // évoqués.
        std::cerr << "semantic error : ";
        std::cerr << "cannot infer type of the argument\n";
        std::exit(EXIT_FAILURE);
      }
    }
  }
}



// TODO a voir pour faire une accumulation des erreurs pour 
// laisser la main au code client de gérer lui même l'erreur.
// On peut envisager la production d'un rapport par le code 
// client. Il lui faudra alors la liste des commandes qui 
// ne passe pas le check plutot qu'un simple boolean qui dit
// "quelque chose ne va pas" !
bool check_commands_name (
    const std::vector<command> & commands, 
    const context & ctx)
{
  bool res = true;

  for(auto&& cmd : commands)
  {
    auto&& name = cmd.name;

    if (context.definitions.count(name)==0) 
    {
      res = false;
    }
  }

  return res;
}

// TODO mettre en place un système de gestion d'erreur 
// cumulative afin d'envisager la création de rapport
// d'erreur par le code client de cette fonction.
bool check_commands_params(
    const std::vector<command> & commands, 
    const context & ctx)
{
  bool res = true;

  for (auto&& cmd : commands)
  {
    auto&& name = cmd.name;
    auto&& def = ctx.definitions.at(name);

    auto&& params = def.params;
    auto&& args = cmd.args;

    auto&& paramssize = params.size();
    auto&& argssize = args.size();

    if (paramssize != argssize)
    {
      res = false;
    }
    else 
    {
      for (unsigned i=0u; i<paramssize; ++i)
      {
        auto&& paramtype = params[i].type;
        auto&& argtype = args[i].type;

        if (paramtype != argtype)
        {
          res = false;
        }
      }
    }
  }

  return res;
}


