#include "blocks-std.h"
#include "log.h"

char *freadall(const char *fname)
{
  if (fname == NULL)
  {
    log_error("filename could not be NULL to read its content !");
    return NULL;
  }
  FILE *file = fopen(fname, "r");

  if (file == NULL)
  {
    log_error("file not found");
    return NULL;
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
  if (f == NULL)
    return 0;

  fseek(f, 0L, SEEK_END);
  unsigned size = ftell(f);
  fseek(f, 0L, SEEK_SET);
  return size;
}

size_t strcount(const char *s, char c)
{
  size_t count = 0;

  if (s != NULL)
    while (*s != '\0')
    {
      if (*s == c)
        ++count;
      ++s;
    }
  
  return count;
}