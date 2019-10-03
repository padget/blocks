#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define precond(cond) assert((cond))

/**
 * *** blocks character detection api ***
 */
bool blocks_is_letter(char);
bool blocks_is_digit(char);
bool blocks_is_colon(char);
bool blocks_is_eol(char);

bool blocks_is_letter(char c) { return 'a' <= c && c <= 'z'; }
bool blocks_is_digit(char c) { return '0' <= c && c <= '9'; }
bool blocks_is_colon(char c) { return c == ':'; }
bool blocks_is_eol(char c) { return c == '\n'; }
bool blocks_is_space(char c) { return c == ' ' || c == '\t'; }

/**
 * *** Blocks token api ***
 */

typedef struct {
  char *begin;
  char *end;
} char_range;

bool matched(char_range *range) {
  precond(range != NULL);
  return range->begin != range->end;
}

char_range blocks_match_number(char *);
char_range blocks_match_name(char *);
char_range blocks_match_eol(char *);
char_range blocks_match_colon(char *);

char_range build_char_range(char *begin, char *end) {
  return (char_range){.begin = begin, .end = end};
}

char_range blocks_match_number(char *source) {
  char *cursor = source;
  while (blocks_is_digit(*cursor))
    ++cursor;
  return build_char_range(source, cursor);
}

char_range blocks_match_name(char *source) {
  char *cursor = source;
  while (blocks_is_letter(*cursor))
    ++cursor;
  return build_char_range(source, cursor);
}

char_range blocks_match_eol(char *source) {
  char *cursor = blocks_is_eol(*source) ? source + 1 : source;
  return build_char_range(source, cursor);
}

char_range blocks_match_colon(char *source) {
  char *cursor = blocks_is_colon(*source) ? source + 1 : source;
  return build_char_range(source, cursor);
}

#define COMMAND_MAX_NUMBER_OF_ARGUMENTS 10

typedef struct {
  size_t length;
  char_range args[COMMAND_MAX_NUMBER_OF_ARGUMENTS];
} arguments;

typedef struct {
  uint8_t depth;
  char_range name;
  arguments args;
} command;

typedef enum {
  COMMAND_NO_ERROR = 0,
  COMMAND_NAME_ERROR,
  COMMAND_ARGS_ERROR,
  COMMAND_TOO_MANY_ARGS_ERROR,
  COMMAND_COLON_ERROR,
} command_error;

command_error blocks_detect_command(char *source, command *c) {
  precond(c != NULL);
  precond(source != NULL);

  char_range range;

  range = blocks_match_name(source);
  if (!matched(&range))
    return COMMAND_NAME_ERROR;
  (*c).name = range;

  range = blocks_match_colon(range.end);
  if (!matched(&range))
    return COMMAND_COLON_ERROR;

  unsigned int nargs = 0u;

  do {
    range = blocks_match_number(range.end);

    if (matched(&range)) {
      nargs++;
      if (nargs > COMMAND_MAX_NUMBER_OF_ARGUMENTS)
        return COMMAND_TOO_MANY_ARGS_ERROR;
      (*c).args.args[nargs - 1] = range;
      (*c).args.length += 1;
    }
  } while (matched(&range));

  return COMMAND_NO_ERROR;
}

/**
 *   BEGIN FILE SECTION
 */

enum file_error {
  FILE_NO_ERROR = 0,
  FILE_READ_ERROR,
  FILE_SEEK_ERROR,
  FILE_CLOSE_ERROR,
  FILE_OPEN_ERROR,
  FILE_BUFFER_ALLOCATION_ERROR
};

enum file_error blocks_fsize(FILE *f, size_t *size) {
  precond(size != NULL);
  *size = 0;
  if (f == NULL)
    return FILE_NO_ERROR;
  if (fseek(f, 0, SEEK_END) != FILE_NO_ERROR)
    return FILE_SEEK_ERROR;
  uint64_t len = (uint64_t)ftell(f);
  if (fseek(f, 0, SEEK_SET) != FILE_NO_ERROR)
    return FILE_SEEK_ERROR;
  *size = len;
  return FILE_NO_ERROR;
}

enum file_error blocks_freadall(FILE *file, char **buffer) {
  size_t fsize = 0;
  enum file_error err = FILE_NO_ERROR;

  if ((err = blocks_fsize(file, &fsize)) != FILE_NO_ERROR)
    return err;

  if (buffer == NULL)
    return FILE_BUFFER_ALLOCATION_ERROR;

  *buffer = malloc(fsize + 1);

  if (*buffer == NULL)
    return FILE_BUFFER_ALLOCATION_ERROR;

  for (uint64_t i = 0u; i < fsize; ++i)
    (*buffer)[i] = (char)fgetc(file);

  (*buffer)[fsize] = '\0';
  return FILE_NO_ERROR;
}

enum file_error blocks_fclose(FILE *file) {
  return fclose(file) ? FILE_CLOSE_ERROR : FILE_NO_ERROR;
}

enum file_error blocks_fopen(const char *filename, FILE **file) {
  precond(file != NULL);

  *file = fopen(filename, "r");
  return *file == NULL ? FILE_OPEN_ERROR : FILE_NO_ERROR;
}

/**
 * END FILE SECTION
 */

void print_all(enum file_error err, const char *text) {
  if (err == FILE_NO_ERROR)
    if (text != NULL)
      printf("%s", text);
}

int main(int argc, char const *argv[]) {
  printf("Hello world\n");
  FILE *f = NULL;

  blocks_fopen("examples/main.blocks", &f);

  if (f == NULL) {
    printf("une erreur est suérvenu lors de l'ouverture du fichier\n");
    return EXIT_FAILURE;
  }

  char *text = NULL;
  if (blocks_freadall(f, &text) != FILE_NO_ERROR) {
    printf("un soucis dans la lecture du fichier\n");
    free(text);
    blocks_fclose(f);
    return EXIT_FAILURE;
  }

  printf("%s", text);
  free(text);
  blocks_fclose(f);

  return EXIT_SUCCESS;
}
