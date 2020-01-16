#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <fstream>

#include "../../include/cxx.hpp"
#include "../../include/arguments.hpp"
#include "command_builder.hpp"
#include "serializer.hpp"

std::string readfile(const std::string& filename);
using scformat = blocks::simple_command_format<blocks::command>;
using miwriter = blocks::multi_inplace_writer<scformat>; 

int main(int argc, char** argv)
{
	std::cout << "coucou" << std::endl;
	auto&& args = cxx::from_args(argc, argv);
	// une fois quon a lesenble des arguments, on doit verifier et prendre 
	// largument qui mindique quel fichier blc doit compiler et transformer 
	// en bytecode. le bytecode pourra ensuite etre serialiser dans un fichier
	// <name>.blb
	// ici on va s'assurer que l'argument <file> est bien présent dans la ligne
	// da commande. Une fois que l'argument est bien détecté, on va pouvoir lire
	// le fichier et le transformer en std::string et lancer le processus de
	// transoformation en un ensemble de commandes et ensuite en l'écriture d'un
	// fichier bytecode simple uniquement avec les ordres des commandes.
	// Nous verrons plus tard pour ajouter les arguments et la construction du
	// de la mémoire des variables et des constantes.
	if (args.count("--file") == 0)
		return EXIT_FAILURE;

	auto&& filename = args.at("--file").value;
	auto&& src = readfile(filename);	

	blocks::coordinates coord;
	
	auto cmds = blocks::build_commands(src, coord);
	miwriter{}.write(cmds, filename);
	return 0;
}

std::string readfile(const std::string& filename)
{
	std::ifstream is(filename);

	std::istreambuf_iterator<char> endfile;
	std::istreambuf_iterator<char> beginfile(is);
	
	return std::string(beginfile, endfile);
}
