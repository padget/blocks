# ===============================================
# blc est le compilateur de blocks invocable par
# > blocks compile main.blocks
# ===============================================

blc: blc_main.o
	g++ -o blocks-compile.exe blc_main.o

blc_main.o: blc/src/main.cpp include/arguments.hpp
	g++ -o blc_main.o -c blc/src/main.cpp -W -Wall -ansi -pedantic -std=c++17 -fconcepts



# ===============================================
# blexe est l'interpreteur de blocks invoocable par
# > blocks compile main.blocks
# ===============================================

blexe: blexe_main.o
	g++ -o blexe_main.o -c blexe/src/main.cpp -W -Wall -ansi -pedantic -std=c++17 -fconcepts

blexe_main.o: blexe/src/main.o include/arguments,hpp






# ==============================================
# le goal clean permet de nettoyer le projet
# des fichiers qui ont ete generes par la
# compilation du projet.
# ==============================================

clean:
	rm -rf *.o *.exe
