CXX = g++
# c++17, c++14, c++11, c++2a
CXX_STANDARD = c++17
CXX_FLAGS = -std=${CXX_STANDARD} -Wall -Werror -pedantic -Wunused

build: blocks.exe

scratch: clean build


command_line.o: src/command_line.cpp include/blocks/command_line.hpp
	${CXX} ${CXX_FLAGS} -o command_line.o -c src/command_line.cpp

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



clean: 
	rm -rf *.o *.exe