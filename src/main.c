#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * BEGIN TOKEN SECTION  
 */

enum token_type
{
    IDENT,
    NUMBER,
    STRING,
    LPAR,
    RPAR,
    COLON
};

typedef struct
{
    char *value;
    int type;
} token;

typedef struct tokens
{
    token *t;
    struct tokens *ts;
} tokens;

void blocks_foreach_token(tokens *ts, void(f)(token *))
{
    tokens *temp = ts;

    while (temp != NULL)
    {
        f(temp->t);
        temp = temp->ts;
    }
}

token *blocks_create_token(const char *src, int size, int type)
{
    token *t = malloc(sizeof(token));

    char *value = malloc(size * sizeof(char) + 1);
    strncpy(value, src, size);
    value[size] = '\0';

    t->value = value;
    t->type = type;

    return t;
}

void blocks_free_token_value(token *t)
{
    if (t != NULL)
        free(t->value);
}

void blocks_free_token(token *t)
{
    if (t != NULL)
    {
        blocks_free_token_value(t);
        free(t);
    }
}

bool blocks_is_ident(char c)
{
    return 'a' <= c && c <= 'z';
}

token *blocks_match_ident(const char *src)
{
    const char *cursor = src;

    while (blocks_is_ident(*cursor))
        ++cursor;

    return blocks_create_token(src, cursor - src, IDENT);
}

/**
 *   BEGIN FILE SECTION
 */

int blocks_fclose(FILE *file)
{
    return fclose(file);
}

FILE *blocks_openf(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (!file)
    {
        puts("le fichier n'a pas pu etre ouvert");
        return NULL;
    }
    else
        return file;
}

/**
 * END FILE SECTION
 */

void printtoken(token *t)
{
    if (t != NULL)
        puts(t->value);
}

int main(int argc, char const *argv[])
{
    printf("Hello world\n");
    FILE *file = blocks_openf("src/main.c");
    int c;

    tokens ts;
    token *t = blocks_create_token("coucou", 2, IDENT);
    ts.t = t;
    blocks_foreach_token(&ts, &printtoken);
    blocks_free_token(ts.t);
    while ((c = getc(file)) != EOF)
        putc(c, stdout);

    blocks_fclose(file);

    return 0;
}
