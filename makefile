all: blocks

blocks.exe: main.o lexer.o parser.o semanticker.o
	g++ -o blocks.exe main.o lexer.o parser.o semanticker.o

lexer.o: src/lexer.cpp src/lexer.hpp
	gcc -o lexer.o -c src/lexer.cpp -W -Wall -ansi -pedantic -std=c++17

parser.o: src/parser.cpp src/parser.hpp
	gcc -o parser.o -c src/parser.cpp -W -Wall -ansi -pedantic -std=c++17

semanticker.o: src/semanticker.cpp src/semanticker.hpp
	gcc -o semanticker.o -c src/semanticker.cpp -W -Wall -ansi -pedantic -std=c++17


main.o: src/main.cpp
	gcc -o main.o -c src/main.cpp -W -Wall -ansi -pedantic -std=c++17 -fconcepts

run: blocks.exe
	./blocks.exe

clean:
	rm -rf *.o *.exe
