gcc -c src/file.c
gcc -c src/blocks_algorithm.c

gcc -o main.exe \
  file.o \
  src/main.c \
  blocks_algorithm.o \
