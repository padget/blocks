cc        = gcc
ccflags = -Wall -W -pedantic -Werror -std=c11

# ===============================================
# Goal: all
# 
# Description: all goal that build all project
# ===============================================

all: clean blp blc blexe blocks

# ===============================================
# Goal: blocks
# 
# Description: blocks est le programme principale 
#              qui se chargera d'appeler les 
#    					 autres sous programmes en fonction 
#              des arguments passés
# ===============================================

BLOCKS_LIB=largument
blocks: blocks_main.o largument
	gcc -o blocks.exe blocks_main.o argument.o

blocks_main.o: blocks/src/main.c
	gcc -o blocks_main.o -c blocks/src/main.c ${ccflags}

# ===============================================
# Goal: blp
#
# Description: blp est le programme permettant de 
#              preparer un ensemble de métrique
#              sur le fichier que l'on va compiler
#              Par exemple, on veut connaitre le 
#              nombre de commandes potentielles
#              à analyser.
# ===============================================
blpo=blp_main.o
blpsrc=blp/src
blpmain=${blpsrc}/main.c
blpexe=blocks-prepare.exe

blp: ${blpo}
	${cc} -o ${blpexe} ${blpo} ${ccflags}

${blpo}: ${blpmain} 
	${cc} -o ${blpo} -c ${blpmain} ${ccflags}

# ===============================================
# blc est le compilateur de blocks invocable par
# > blocks compile main.blocks
# ===============================================
BLC_DEPS=blc_main.o lstring largument command_builder.o 
BLC_OBJS=blc_main.o string.o argument.o command_builder.o
BLC_EXE =blocks-compile.exe

blc: ${BLC_DEPS}
	${cc} -o ${BLC_EXE} ${BLC_OBJS} ${ccflags}

blc_main.o: blc/src/main.c experimental/memory.h 
	${cc} -o blc_main.o -c blc/src/main.c ${ccflags} 

command_builder.o: blc/src/command_builder.c blc/src/command_builder.h
	${cc} -o command_builder.o -c blc/src/command_builder.c ${ccflags}

# ===============================================
# blexe est l'interpreteur de blocks invoocable par
# > blocks compile main.blocks
# ===============================================

blexe: blexe_main.o
	${cc} -o blocks-execute.exe blexe_main.o

blexe_main.o: blexe/src/main.c
	${cc} -o blexe_main.o -c blexe/src/main.c ${ccflags}

# ==============================================
# La section experimental contient l'ensemble 
# des petites librairie en conception experimentale
# pour les programmes de la suite blocks.
# ==============================================

lmemory: experimental/memory.c experimental/memory.h
	${cc} -o memory.o -c experimental/memory.c ${ccflags}

lstring: experimental/string.c experimental/string.h
	${cc} -o string.o -c experimental/string.c ${ccflags}

lvstring: experimental/vstring.c experimental/vstring.h
	${cc} -o vstring.o -c experimental/vstring.c ${ccflags}

largument: experimental/argument.c experimental/argument.h experimental/vstring.h
	${cc} -o argument.o -c experimental/argument.c ${ccflags}

ltest: experimental/test.c experimental/test.h
	${cc} -o test.o -c experimental/test.c ${ccflags}


# ==============================================
# le goal clean permet de nettoyer le projet
# des fichiers qui ont ete generes par la
# compilation du projet.
# ==============================================

clean:
	rm -rf *.o *.exe
