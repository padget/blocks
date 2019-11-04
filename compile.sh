g++ -c src2/main.cpp -std=c++17
g++ -c src2/command.cpp -std=c++17
g++ -c src2/source.cpp -std=c++17
g++ -c src2/token.cpp -std=c++17
g++ -c src2/tokenizer.cpp -std=c++17


g++ -o blocks.exe main.o \
                command.o \
                source.o \
                token.o \
                tokenizer.o