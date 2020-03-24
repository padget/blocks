#include "blocks-std.h"

char *freadall(const char *fname)
{
    FILE *file = fopen(fname, "r");

    if (!file)
    {
        perror("oops");
        exit(EXIT_FAILURE);
    }

    size_t s = fsize(file);
    size_t schar = sizeof(char);
    char *cstr = malloc(s * schar + 1);
    char *cursor = cstr;
    int c;

    while ((c = fgetc(file)) != EOF)
    {
        *cursor = c;
        ++cursor;
    }

    *cursor = '\0';

    return cstr;
}

size_t fsize(FILE *f)
{
    fseek(f, 0L, SEEK_END);
    unsigned size = ftell(f);
    fseek(f, 0L, SEEK_SET);
    return size;
}