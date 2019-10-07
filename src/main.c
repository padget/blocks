#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define precond(cond) assert((cond))
#define notnull(ptr) precond((ptr != NULL))

/**
 * *** blocks character detection api ***
 */

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
  notnull(range);
  return range->begin != range->end;
}

char_range build_char_range(char *begin, char *end) {
  return (char_range){.begin = begin, .end = end};
}

void bypass_blank(char **source) {
  notnull(source);
  while (blocks_is_space(**source))
    ++(*source);
}

bool blocks_match_number(char **source, char_range *range) {
  notnull(source);
  notnull(*source);
  notnull(range);

  bypass_blank(source);
  char *cursor = *source;
  while (blocks_is_digit(*cursor))
    ++cursor;
  *range = build_char_range(*source, cursor);
  *source = cursor;
  return matched(range);
}

bool blocks_match_name(char **source, char_range *range) {
  notnull(source);
  notnull(*source);
  notnull(range);

  bypass_blank(source);
  char *cursor = *source;
  while (blocks_is_letter(*cursor))
    ++cursor;
  *range = build_char_range(*source, cursor);
  *source = cursor;
  return matched(range);
}

bool blocks_match_eol(char **source, char_range *range) {
  notnull(source);
  notnull(*source);
  notnull(range);

  bypass_blank(source);
  char *cursor = blocks_is_eol(**source) ? *source + 1 : *source;
  *range = build_char_range(*source, cursor);
  *source = cursor;
  return matched(range);
}

bool blocks_match_colon(char **source, char_range *range) {
  notnull(source);
  notnull(*source);
  notnull(range);

  bypass_blank(source);
  char *cursor = blocks_is_colon(**source) ? *source + 1 : *source;
  *range = build_char_range(*source, cursor);
  *source = cursor;
  return matched(range);
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
  notnull(c);
  notnull(source);

  char_range range;
  if (!blocks_match_name(&source, &range))
    return COMMAND_NAME_ERROR;
  (*c).name = range;
  if (!blocks_match_colon(&source, &range))
    return COMMAND_COLON_ERROR;
  unsigned int nargs = 0u;
  while (blocks_match_number(&source, &range)) {
    nargs++;
    if (nargs > COMMAND_MAX_NUMBER_OF_ARGUMENTS)
      return COMMAND_TOO_MANY_ARGS_ERROR;
    (*c).args.args[nargs - 1] = range;
    (*c).args.length += 1;
  }

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

enum file_error blocks_fsize(FILE *file, size_t *size) {
  notnull(size);

  *size = 0;
  if (file == NULL)
    return FILE_NO_ERROR;
  if (fseek(file, 0, SEEK_END) != FILE_NO_ERROR)
    return FILE_SEEK_ERROR;
  uint64_t len = (uint64_t)ftell(file);
  if (fseek(file, 0, SEEK_SET) != FILE_NO_ERROR)
    return FILE_SEEK_ERROR;
  *size = len;
  return FILE_NO_ERROR;
}

enum file_error blocks_fclose(FILE *file) {
  notnull(file);

  return fclose(file) ? FILE_CLOSE_ERROR : FILE_NO_ERROR;
}

enum file_error blocks_fopen(const char *filename, FILE **file) {
  notnull(file);

  *file = fopen(filename, "r");
  return *file == NULL ? FILE_OPEN_ERROR : FILE_NO_ERROR;
}

enum file_error blocks_freadall(FILE *file, char *buffer) {
  notnull(file);
  notnull(buffer);

  int c;
  while ((c = (char)fgetc(file)) != EOF) {
    *buffer = c;
    buffer++;
  }
  *buffer = '\0';
  return FILE_NO_ERROR;
}

enum file_error blocks_build_buffer(FILE *file, char **buffer) {
  notnull(file); 
  notnull(buffer);

  size_t fsize = 0;
  enum file_error err = FILE_NO_ERROR;
  if ((err = blocks_fsize(file, &fsize)) != FILE_NO_ERROR)
    return err;
  *buffer = malloc(fsize + 1);
  if (*buffer == NULL)
    return FILE_BUFFER_ALLOCATION_ERROR;
  return FILE_NO_ERROR;
}

/**
 * END FILE SECTION
 */

int main(int argc, char const *argv[]) {
  printf("Hello world\n");
  FILE *f = NULL;

  blocks_fopen("examples/main.blocks", &f);

  if (f == NULL) {
    printf("une erreur est suérvenu lors de l'ouverture du fichier\n");
    return EXIT_FAILURE;
  }

  char *text = NULL;
  blocks_build_buffer(f, &text);
  if (blocks_freadall(f, text) != FILE_NO_ERROR) {
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
