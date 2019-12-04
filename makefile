all: blocks 

blocks: main.o 
	g++ -o blocks.exe main.o 

main.o: src/main.cpp commander.hpp
	gcc -o main.o -c src/main.cpp -W -Wall -ansi -pedantic -std=c++17 -fconcepts

run: blocks
	./blocks.exe

clean:
	rm -rf *.o *.exe
