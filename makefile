CXX = g++
# c++17, c++14, c++11, c++2a
CXX_STANDARD = c++17
CXX_FLAGS = -std=${CXX_STANDARD} -Wall -Werror -pedantic -Wunused

.PHONY: build scratch 

scratch: clean build
build: blocks.exe

# LIBS

## BASE64

base64.o: libs/base64.cpp
	${CXX} ${CXX_FLAGS} -o base64.o -c libs/base64.cpp

## CMDL

cmdl.o: libs/cmdl/cmdl.cpp libs/cmdl/cmdl.hpp
	${CXX} ${CXX_FLAGS} -o cmdl.o -c libs/cmdl/cmdl.cpp


# APPS

## SEUR
.PHONY: seur
seur: seur.exe
	./seur.exe password jddjqklsdjlq
	
seur.o: apps/seur.cpp
	${CXX} ${CXX_FLAGS} -o seur.o -c apps/seur.cpp

seur.exe: seur.o base64.o
	${CXX} ${CXX_FLAGS} -o seur.exe seur.o base64.o

## BLOCKS

blocks.o:	apps/blocks.cpp
	${CXX} ${CXX_FLAGS} -o blocks.o -c apps/blocks.cpp

blocks.exe: blocks.o command_line.o
	${CXX} ${CXX_FLAGS} -o blocks.exe blocks.o command_line.o

## PROTO

.PHONY: proto
proto: proto.exe
	./proto.exe

proto.exe: proto.o	cmdl.o
	${CXX} ${CXX_FLAGS} -o proto.exe proto.o cmdl.o

proto.o: apps/proto.cpp
	${CXX} ${CXX_FLAGS} -o proto.o -c apps/proto.cpp

## BYLINE

byline.exe: apps/byline.cpp
	${CXX} ${CXX_FLAGS} -o byline.exe apps/byline.cpp


# GENERIC
.PHONY: clean
clean: 
	rm -rf *.o *.exe

