echo compilation main.cpp
g++ -c src/main.cpp -std=c++17 -Wall -pedantic
echo construction blocks.exe
g++ -o blocks.exe main.o
