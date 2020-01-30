COMPILER=gcc

all: blc blexe blocks

# ===============================================
# blocks est le programme principale qui se
# chargera d'appeler les autres sous programmes
# en fonction des arguments passés
# > blocks --compile example/add.blocks
# ===============================================
blocks: blocks_main.o
	gcc -o blocks.exe blocks_main.o

blocks_main.o: blocks/src/main.c
	gcc -o blocks_main.o -c blocks/src/main.c -Wall -W -pedantic

# ===============================================
# blc est le compilateur de blocks invocable par
# > blocks compile main.blocks
# ===============================================
BLC_DEPS=blc_main.o lmemory lstring lvstring largument
BLC_OBJS=blc_main.o memory.o string.o vstring.o argument.o
BLC_EXE =blocks-compile.exe

blc: ${BLC_DEPS}
	${COMPILER} -o ${BLC_EXE} ${BLC_OBJS}

blc_main.o: blc/src/main.c experimental/memory.h
	gcc -o blc_main.o -c blc/src/main.c -W -Wall -pedantic 

command_builder.o: blc/src/command_builder.c blc/src/command_builder.h
	gcc -o command_builder.o -c blc/src/command_builder.c -Wall -W -pedantic

# ===============================================
# blexe est l'interpreteur de blocks invoocable par
# > blocks compile main.blocks
# ===============================================

blexe: blexe_main.o
	gcc -o blocks-execute.exe blexe_main.o

blexe_main.o: blexe/src/main.c
	gcc -o blexe_main.o -c blexe/src/main.c -W -Wall -pedantic

# ==============================================
# La section experimental contient l'ensemble 
# des petites librairie en conception experimentale
# pour les programmes de la suite blocks.
# ==============================================

lmemory: experimental/memory.c experimental/memory.h
	gcc -o memory.o -c experimental/memory.c

lstring: experimental/string.c experimental/string.h
	gcc -o string.o -c experimental/string.c

lvstring: experimental/vstring.c experimental/vstring.h
	gcc -o vstring.o -c experimental/vstring.c

largument: experimental/argument.c experimental/argument.h experimental/vstring.h
	gcc -o argument.o -c experimental/argument.c


# ==============================================
# le goal clean permet de nettoyer le projet
# des fichiers qui ont ete generes par la
# compilation du projet.
# ==============================================

clean:
	rm -rf *.o *.exe
