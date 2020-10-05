CXX = g++
# c++17, c++14, c++11, c++2a
CXX_STANDARD = c++17
CXX_FLAGS = -std=${CXX_STANDARD} -Wall -Werror -pedantic -Wunused

.PHONY: build scratch clean proto

scratch: clean build
build: blocks.exe


command_line.o: libs/include/cmdl/command_line.cpp libs/include/cmdl/command_line.hpp
	${CXX} ${CXX_FLAGS} -o command_line.o -c libs/include/cmdl/command_line.cpp

blocks.o:	apps/blocks.cpp
	${CXX} ${CXX_FLAGS} -o blocks.o -c apps/blocks.cpp

blocks.exe: blocks.o command_line.o
	${CXX} ${CXX_FLAGS} -o blocks.exe blocks.o command_line.o



proto: proto.exe
	./proto.exe

proto.exe: proto.o	
	${CXX} ${CXX_FLAGS} -o proto.exe proto.o

proto.o: apps/proto.cpp
	${CXX} ${CXX_FLAGS} -o proto.o -c apps/proto.cpp


seur: seur.exe
	./seur.exe password jemappellebenjamin

seur.o: apps/seur.cpp
	${CXX} ${CXX_FLAGS} -o seur.o -c apps/seur.cpp

base64.o: libs/base64.cpp
	${CXX} ${CXX_FLAGS} -o base64.o -c libs/base64.cpp

seur.exe: seur.o base64.o
	${CXX} ${CXX_FLAGS} -o seur.exe seur.o base64.o



clean: 
	rm -rf *.o *.exe

byline.exe: apps/byline.cpp
	${CXX} ${CXX_FLAGS} -o byline.exe apps/byline.cpp