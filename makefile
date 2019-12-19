all: blocks.exe

blocks.exe: main.o command_building.o
	g++ -o blocks.exe main.o command_building.o

command_building.o: src/command_building.cpp src/command_building.hpp
	gcc -o command_building.o -c src/command_building.cpp -W -Wall -ansi -pedantic -std=c++17

main.o: src/main.cpp src/command_building.hpp
	gcc -o main.o -c src/main.cpp -W -Wall -ansi -pedantic -std=c++17

run: blocks.exe
	./blocks.exe

clean:
	rm -rf *.o *.exe
