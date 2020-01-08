#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <fstream>
#include "../../include/cxx.hpp"
#include "../../include/arguments.hpp"


int main(int argc, char** argv)
{
  std::cout << "blocks-ccompile" << std::endl;
  auto&& args = cxx::from_args(argc, argv);

  for (auto && arg: args) 
    std::cout << arg.first << " " << arg.second.value << std::endl;
  // une fois quon a lesenble des arguments, on doit verifier et prendre 
  // largument qui mindique quel fichier blc doit compiler et transformer 
  // en bytecode. le bytecode pourra ensuite etre serialiser dans un fichier
  // <name>.blby


  // ici on va s'assurer que l'argument <file> est bien présent dans la ligne
  // da commande. Une fois que l'argument est bien détecté, on va pouvoir lire
  // le fichier et le transformer en std::string et lancer le processus de
  // transoformation en un ensemble de commandes et ensuite en l'écriture d'un
  // fichier bytecode simple uniquement avec les ordres des commandes.
  // Nous verrons plus tard pour ajouter les arguments et la construction du
  // de la mémoire des variables et des constantes.


  if (args.count("--file") == 1)
  {
    auto filename = args.at("--file").value;
    std::cout << "fichier à compiler " << filename << std::endl; 
    std::ifstream is(args.at("--file").value);
    std::istreambuf_iterator<char> endfile;
    std::istreambuf_iterator<char> beginfile(is);
    auto src = std::string(beginfile, endfile);

    std::cout << src << std::endl;
  }

  return 0;
}
