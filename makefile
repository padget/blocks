all: blocks 

blocks: main.o 
	g++ -o blocks.exe main.o 

main.o: src/main.cpp
	gcc -o main.o -c src/main.cpp -W -Wall -ansi -pedantic -std=c++17

run: blocks
	./blocks.exe

clean:
	rm -rf *.o *.exe
