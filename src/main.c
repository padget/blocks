#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>

#define precond(cond) assert((cond))

/**
 * *** blocks character detection api ***
 */
bool blocks_is_letter(char);
bool blocks_is_digit(char);
bool blocks_is_colon(char);
bool blocks_is_eol(char);

bool blocks_is_letter(char c)
{
    return 'a' <= c && c <= 'z';
}

bool blocks_is_digit(char c)
{
    return '0' <= c && c <= '9';
}

bool blocks_is_colon(char c)
{
    return c == ':';
}

bool blocks_is_eol(char c)
{
    return c == '\n';
}

bool blocks_is_space(char c)
{
    return c == ' ' || c == '\t';
}

/**
 * *** Blocks token api ***
 */

typedef struct
{
    char *begin;
    char *end;
} char_range;

bool matched(char_range *range)
{
    precond(range != NULL);
    return range->begin != range->end;
}

char_range blocks_match_number(char *);
char_range blocks_match_name(char *);
char_range blocks_match_eol(char *);
char_range blocks_match_colon(char *);

char_range build_char_range(char *begin, char *end)
{
    return (char_range){
        .begin = begin,
        .end = end};
}

char_range blocks_match_number(char *source)
{
    char *cursor = source;
    while (blocks_is_digit(*cursor))
        ++cursor;
    return build_char_range(source, cursor);
}

char_range blocks_match_name(char *source)
{
    char *cursor = source;
    while (blocks_is_letter(*cursor))
        ++cursor;
    return build_char_range(source, cursor);
}

char_range blocks_match_eol(char *source)
{
    char *cursor = blocks_is_eol(*source) ? source + 1 : source;
    return build_char_range(source, cursor);
}

char_range blocks_match_colon(char *source)
{
    char *cursor = blocks_is_colon(*source) ? source + 1 : source;
    return build_char_range(source, cursor);
}

#define COMMAND_MAX_NUMBER_OF_ARGUMENTS 10

typedef struct
{
    size_t length;
    char_range args[COMMAND_MAX_NUMBER_OF_ARGUMENTS];
} arguments;

typedef struct
{
    uint8_t depth;
    char_range name;
    arguments args;
} command;

typedef enum
{
    COMMAND_NO_ERROR = 0,
    COMMAND_NAME_ERROR,
    COMMAND_ARGS_ERROR,
    COMMAND_TOO_MANY_ARGS_ERROR,
    COMMAND_COLON_ERROR,
} command_error;

command_error blocks_detect_command(char *source, command *c)
{
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

    do
    {
        range = blocks_match_number(range.end);

        if (matched(&range))
        {
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

uint64_t blocks_fsize(FILE *f)
{
    if (f == NULL)
        return 0;

    fseek(f, 0, SEEK_END);
    uint64_t len = (uint64_t)ftell(f);
    fseek(f, 0, 0);
    return len;
}

int blocks_fclose(FILE *file)
{
    return fclose(file);
}

FILE *blocks_openf(const char *filename)
{
    return fopen(filename, "r");
}

char *block_freadall(FILE *f)
{
    uint64_t size = blocks_fsize(f);
    char *buffer = malloc(size + 1);
    for (uint64_t i = 0u; i < size; ++i)
    {
        buffer[i] = (char)fgetc(f);
    }
    buffer[size] = '\0';
    return buffer;
}

/**
 * END FILE SECTION
 */

int main(int argc, char const *argv[])
{
    printf("Hello world\n");
    FILE *file = blocks_openf("examples/main.blocks");
    if (!file)
    {
        printf("une erreur est suérvenu lors de l'ouverture du fichier");
        return EXIT_FAILURE;
    }
    char *text = block_freadall(file);
    command c;
    command_error error = blocks_detect_command(text, &c);
    printf("%d", error);
    printf("%s", text);
    printf("%c - %c", *c.name.begin, *(c.name.end-1));
    blocks_fclose(file);

    return EXIT_SUCCESS;
}
