#include "semanticker.hpp"

namespace std
{
template<>
  struct hash<blocks::command_signature>
{
  std::size_t operator()(const blocks::command_signature& sig)
  {
    std::hash<string> hash_me;
    std::size_t hash = hash_me(sig.name);
    for (auto&& param : sig.params)
      hash ^= hash_me(param.type) << 1;
    return hash;
  }
};

template<>
struct hash<blocks::command>
{
  std::size_t operator()(const blocks::command& cmd)
  {
    std::hash<string> hash_me;
    std::size_t hash = hash_me(cmd.name);
    for (auto&& arg : cmd.args)
      hash ^= hash_me(arg.type) << 1;
    return hash;
  }
};
}


std::vector<blocks::command_signature>
build_native_commands_definitions()
{
  std::vector<blocks::command_signature> signatures;

  signatures.push_back({"add:",      {{"a", "#int"}, {"b", "#int"}}});
  signatures.push_back({"minus:",    {{"a", "#int"}, {"b", "#int"}}});
  signatures.push_back({"multiply:", {{"a", "#int"}, {"b", "#int"}}});
  signatures.push_back({"divide:",   {{"a", "#int"}, {"b", "#int"}}});
  signatures.push_back({"print:",    {{"a", "#int"}}});
  signatures.push_back({"read:",     {{"a", "#int"}}});

  return signatures;
}


blocks::dictonnary build_native_commands_index()
{
  blocks::dictonnary dict;

  auto && sigs = build_native_commands_definitions();
  std::hash<blocks::command_signature> hash_me;

  for (auto&& sig : sigs)
  {
    dict.defs.push_back(sig);
    std::size_t hash = hash_me(sig);
    dict.indexes.insert({hash, &dict.defs.back()});
  }

  return dict;
}


void infer_arguments_type_for_this_command(blocks::command& cmd)
{
  for (auto& arg:cmd.args)
  {
    if (arg.type.empty())
    {
      // TODO inference, pour l'instant nous allons ajouter simplement les
      // types à la main dans le code de tests. Nous y reviendrons plus tard.
    }
  }
}

void infer_arguments_type_for_each_command(blocks::commands& cmds)
{
  for (auto& cmd:cmds)
  {
    infer_arguments_type_for_this_command(cmd);
  }
}

blocks::step
check_commands_well_used(
                         const blocks::commands& cmds,
                         const blocks::dictonnary& ndict)
{
  blocks::step step{"check all commands well-used",
    "check if all writen commands are well-used in function of their signature (name of the command and type of the argument)",
    {},
    blocks::step_status::PROCESSING};

  std::hash<blocks::command> hash_me;

  for (auto&& cmd:cmds)
  {
    std::size_t cmdhash = hash_me(cmd);

    if (ndict.indexes.count(cmdhash)==0)
    {
      // FIXME il y a une erreur, il faut donc que le programmeur la corrige
      // avant de poursuivre la compilation.
      // TODO il faut donc mettre en place un rapport d'erreur permettant de
      // regrouper l'ensemble des erreurs qui se sont passé à une certaine
      // étape de la compiltation
      // TODO il faut mettre en place une structure report qui regroupera
      // l'ensemble des données nécessaires à l'établissement d'un rapport
      // d'erreur lisible et compréhensible pour le développeur en cours de
      // programmation.
      // TODO il faut d'abord que je détermine le type de chaque argument des
      // commandes si ceux-ci ne sont pas explicite dans le code.
      blocks::step::step_error error;
      error.filename = "";
      error.line = 0;
      error.col = 0;
      error.message = "la signature de la commande n'est pas reconnu par le compilateur";
      step.errors.push_back(error);
    }
  }

  return step;
}


blocks::report blocks::semantic_check(blocks::commands& cmds)
{
  blocks::report report;
  report.status = blocks::report_status::PROCESSING;

  infer_arguments_type_for_each_command(cmds);

  blocks::dictonnary &&ndict = build_native_commands_index();
  // TODO pour l'instant nous n'avons que les signatures de commande natives
  // qui sont indexées. Nous verrons plus tard pour mettre en place les
  // définitions de commandes non natives. Il faudra mettre en place à ce
  // moment là, la notion de scope... (gros sujet en soit).
  report.steps.push_back(check_commands_well_used(cmds, ndict));
  report.status = blocks::report_status::OK;
  // TODO mettre en place le calcul 
  // exact du statut du rapport
  // OK : Toutes les steps sont OK
  // KO : Une step ou plus est KO
  return report;

}
