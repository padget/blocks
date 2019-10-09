gcc -c src/srange.c
gcc -c src/file.c
gcc -c src/command.c


gcc -o main.exe src/main.c file.o srange.o command.o