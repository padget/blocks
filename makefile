all: blc blexe blocks

# ===============================================
# blocks est le programme principale qui se
# chargera d'appeler les autres sous programmes
# en fonction des arguments passés
# > blocks --compile example/add.blocks
# ===============================================
blocks: blocks_main.o
	g++ -o blocks.exe blocks_main.o

blocks_main.o: blocks/src/main.cpp include/arguments.hpp
	g++ -o blocks_main.o -c blocks/src/main.cpp -W -Wall -ansi -pedantic -std=c++17 -fconcepts

# ===============================================
# blc est le compilateur de blocks invocable par
# > blocks compile main.blocks
# ===============================================

blc: blc_main.o command_builder.o
	g++ -o blocks-compile.exe blc_main.o command_builder.o

blc_main.o: blc/src/main.cpp include/arguments.hpp
	g++ -o blc_main.o -c blc/src/main.cpp -W -Wall -ansi -pedantic -std=c++17 -fconcepts

command_builder.o: blc/src/command_builder.hpp blc/src/command_builder.cpp
	g++ -o command_builder.o -c blc/src/command_builder.cpp -W -Wall -ansi -pedantic -std=c++17 -fconcepts

# ===============================================
# blexe est l'interpreteur de blocks invoocable par
# > blocks compile main.blocks
# ===============================================

blexe: blexe_main.o
	g++ -o blocks-execute.exe blexe_main.o

blexe_main.o: blexe/src/main.cpp include/arguments.hpp
	g++ -o blexe_main.o -c blexe/src/main.cpp -W -Wall -ansi -pedantic -std=c++17 -fconcepts

# ==============================================
# le goal clean permet de nettoyer le projet
# des fichiers qui ont ete generes par la
# compilation du projet.
# ==============================================

clean:
	rm -rf *.o *.exe
