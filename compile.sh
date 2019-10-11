gcc -c src/srange.c
gcc -c src/file.c
gcc -c src/impl/bypass_blank.c
gcc -c src/impl/blocks_is.c
gcc -c src/impl/match_number.c
gcc -c src/impl/match_name.c
gcc -c src/impl/match_eol.c
gcc -c src/impl/match_colon.c
gcc -c src/impl/match_string.c
gcc -c src/impl/match_parameter.c
gcc -c src/impl/match_arg.c
gcc -c src/impl/detect_command.c
gcc -c src/impl/detect_commands.c

gcc -o main.exe \
  src/main.c \
  file.o \
  srange.o \
  bypass_blank.o \
  blocks_is.o \
  match_number.o \
  match_name.o \
  match_eol.o \
  match_colon.o \
  match_string.o \
  match_parameter.o \
  match_arg.o \
  detect_command.o \
  detect_commands.o \

