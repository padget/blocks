#include <iostream>
#include <vector>
#include <string> 
#include <map>

struct token
{
  std::string type;
  std::string value;
};

struct argument
{ 
  std::string value;
  std::string type;
};

struct command
{
  std::string name;
  std::vector<argument> args;
};

struct check_command_error 
{
  size_t line;
  std::string name;
};

struct parameter
{
  std::string name;
  std::string type;
};

struct check_param_error 
{ // TODO rajouter une référence 
  // vers la commande pour avoir
  // plus d'information sur la
  // localisation de l'erreur.
  size_t line;
  std::string param;
  std::string expected;
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
  std::string $$;
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

std::vector<token> 
scan_source(
    const std::string& src);

std::vector<command> 
parse_tokens(
    const std::vector<token>& tokens);

void 
infer_args_type(
    std::vector<command>& commands);

context build_context();

std::vector<check_command_error> 
check_commands_name (
    const std::vector<command> & commands, 
    const context & ctx);

void treat_check_command_errors(
    const std::vector<check_command_error> & errors);

std::vector<check_param_error> 
check_commands_params(
    const std::vector<command> & commands,
    const context& ctx);

void treat_check_param_errors(
    const std::vector<check_param_error>& errors);

void interpret_commands(
    const std::vector<command>& commands);


int main(int argc, char const *argv[])
{
  std::string source =
    // TODO prendre en compte le type file 
    // pour pouvoir interagir avec le monde 
    // exterieur !
    // "let c#file 0\n"
    // "fopen c 'main.cpp' 'r'\n"
    "let a#int 12\n"
    "let b#int a#int\n"
    "add b#int 13\n"
    "add $$ 12\n"
    "minus $$ 1\n"
    "print $$\n";

  std::cout << source << "\n";

  std::vector<token> tokens = scan_source(source);

  liner l;
  auto&& lines = l.from_tokens(tokens.begin(), tokens.end());

  for (auto&& line:lines)
  {
    for (auto&& token:line)
    {
      std::cout << token.type << " " << token.value << "\n";
    }
  }

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
      t.type = "type";
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
    else if (*begin == '\'')
    {
      begin++;

      while (begin != end 
          and *begin != '\'')
      {
        begin++;
      }

      if (begin != end and *begin == '\'')
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
            and (*begin).type == "type")
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
          arg.type= (*begin).value;
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
          arg.type  = "int";
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
      if (!arg.type.empty())
      {
        continue;
      }

      auto && value = arg.value;

      if (!value.empty() and 
          '0' <= value[0] and 
          value[0] <= '9')
      {
        arg.type = "int";
      } 
      else if (!value.empty() and
          'a' <= value[0] and 
          value[0] <= 'z')
      {
        arg.type = "int"; // TODO pour l'instant 
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
        arg.type = "int"; 
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

auto add(auto a, auto b) 
{
  return a+b;
}

auto minus(auto a, auto b) 
{
  return a-b;
}

auto multiply(auto a, auto b) 
{
  return a*b;
}

auto divide(auto a, auto b) 
{
  return a/b;
}

auto modulo(auto a, auto b) 
{
  return a%b;
}

void print(auto a) 
{
  std::cout << a;
}

void let(
    const std::string& name, 
    const std::string& value, 
    auto& lets) 
{
  lets.insert({name, value});
}

void type(
    const std::string& name, 
    auto argsbegin, 
    auto argsend)
{
  std::cout << "new type " ;
  std::cout << name ;

  while (argsbegin != argsend)
  {
    std::cout << " " << (*argsbegin).value ;
    std::cout << "#" << (*argsbegin).type ;
    argsbegin++;
  }
}

context build_context()
{
  std::map<std::string, command_definition> cmddefs;
  cmddefs.insert({"add",      {"add",      "int",  {{"a", "int"},    {"b", "int"}}}});
  cmddefs.insert({"minus",    {"minus",    "int",  {{"a", "int"},    {"b", "int"}}}});
  cmddefs.insert({"divide",   {"divide",   "int",  {{"a", "int"},    {"b", "int"}}}});
  cmddefs.insert({"multiply", {"multiply", "int",  {{"a", "int"},    {"b", "int"}}}});
  cmddefs.insert({"mod",      {"mod",      "int",  {{"a", "int"},    {"b", "int"}}}});
  cmddefs.insert({"neg",      {"neg",      "int",  {{"a", "int"}}}});
  cmddefs.insert({"print",    {"print",    "void", {{"a", "any"}}}});
  cmddefs.insert({"let",      {"let",      "void", {{"name", "any"}, {"value", "int"}}}});
  context ctx {cmddefs};

  return ctx;
}


  std::vector<check_command_error> 
check_commands_name (
    const std::vector<command> & commands, 
    const context & ctx)
{
  std::vector<check_command_error> errors;
  check_command_error error;

  for(auto&& cmd : commands)
  {
    auto&& name = cmd.name;

    if (ctx.definitions.count(name)==0) 
    {
      error.name = name;
      error.line = 0;
      errors.push_back(error);
    }
  }

  return errors;
}

  std::vector<check_param_error> 
check_commands_params(
    const std::vector<command> & commands, 
    const context & ctx)
{
  std::vector<check_param_error> errors;
  check_param_error error;

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
      error.line     = 0;
      error.param    = "all";
      error.expected = "size !=";
      errors.push_back(error);
    }
    else 
    {
      for (unsigned i=0u; i<paramssize; ++i)
      {
        auto&& paramtype = params[i].type;
        auto&& argtype = args[i].type;

        if (paramtype == "any")
        {
          continue;
        }

        if (paramtype != argtype)
        {
          error.line     = 0;
          error.expected = params[i].name+"#"+paramtype;
          error.param    = args[i].value+"#"+argtype;
          errors.push_back(error);
        }
      }
    }
  }

  return errors;
}

  void
treat_check_command_errors(
    const std::vector<check_command_error>& errors)
{
  for (auto&& error:errors)
  {
    std::cerr << "semantic error : ";
    std::cerr << error.name ;
    std::cerr << " not found in the context\n";
  }

  if (!errors.empty())
  {
    std::exit(EXIT_FAILURE);
  }
}

  void
treat_check_param_errors(
    const std::vector<check_param_error>& errors)
{
  for (auto&& error:errors)
  {
    std::cerr << "semantic error : ";
    std::cerr << error.param ;
    std::cerr << " instead of " ;
    std::cerr << error.expected;
    std::cerr << "\n";
  }

  if (!errors.empty())
  {
    std::exit(EXIT_FAILURE);
  }
}

int resolve_name(
    const std::string& name, 
    const std::map<std::string, std::string>& lets)
{
  auto&& resolved = lets.at(name);
  auto&& firstc = *resolved.begin();

  if (between(firstc, 'a', 'z'))
  {
    return resolve_name(resolved, lets);
  } 
  else
  {
    return std::stoi(resolved);
  }
}

// TODO introduire les string...
void interpret_commands(
    const std::vector<command>& commands)
{
  int $$ = 0;
  std::map<std::string, std::string> lets;

  for (auto&& cmd:commands)
  {
    auto&& name = cmd.name;
    auto&& args = cmd.args;

    std::vector<int> ints;

    for (auto&& arg:args)
    {
      auto&& value = arg.value;

      if (value == "$$")
      {
        ints.push_back($$);
        continue;
      }

      auto firstc = *value.begin();

      if (between(firstc, 'a', 'z'))
      {
        if (name != "let")
        {
          auto&& i = resolve_name(value, lets);
          ints.push_back(i);
          continue;
        }
      }

      if (between(firstc, '0', '9'))
      {
        ints.push_back(std::stoi(value));
        continue;
      }
    }

    if (name == "add") 
    {
      auto&& arg1 = ints[0];
      auto&& arg2 = ints[1];
      $$ = add(arg1, arg2);
    }
    else if (name == "minus")
    {
      auto&& arg1 = ints[0];
      auto&& arg2 = ints[1];
      $$ = minus(arg1, arg2);
    }
    else if (name == "multiply")
    {
      auto&& arg1 = ints[0];
      auto&& arg2 = ints[1];
      $$ = multiply(arg1, arg2);
    }
    else if (name == "divide")
    {
      auto&& arg1 = ints[0];
      auto&& arg2 = ints[1];
      $$ = divide(arg1, arg2);
    } 
    else if (name == "print")
    {
      auto&& arg = ints[0];
      print(arg);
    }
    else if (name == "let")
    {
      auto&& name = args[0].value; 
      auto&& value = args[1].value;
      let(name, value, lets);
    } 
    else if (name == "type")
    {
      auto&& name = args[0].value;
      auto&& begin = args.begin()+1;
      auto&& end = args.end();
      type(name, begin, end);
    }
  }

}
