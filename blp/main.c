#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define EOS '\0'
#define EOL '\n'

char* freadall(const char*);
size_t fsize(FILE* file);
unsigned countlines(char* src);

int main(/*int argc, char **argv*/)
{   
  char* src = freadall("examples/add.blocks");

  countlines(src);

  return EXIT_SUCCESS;
}

char* untileol(char* c)
{
  while (c!=NULL && *c!=EOL && *c!=EOS)
    c++;
  return c;
}

bool isblankline(char* b, char* eol)
{
  while (b!=eol)
    if (b!=NULL && *b!=' ' && *b!='\t')
      b++;
    else 
    break;
  return b==eol;
}

unsigned countlines(char* src)
{
  unsigned nblines = 0;
  
  while (*src!=EOS)
  {
    char* eol = untileol(src);
    if (isblankline(src, eol))
      nblines++;
    src = eol+1;
  }
  return nblines;
}




// TODO factoriser freadall
char* freadall(const char* fname)
{
  FILE* file = fopen(fname, "r");

  if (!file)
  {
    perror("oops");
    exit(EXIT_FAILURE);
  }

  size_t s     = fsize(file);
  size_t schar = sizeof(char);
  char* cstr   = malloc(s*schar+1);
  char* cursor = cstr;
  int c;

  while ((c=fgetc(file))!=EOF)
  {
    *cursor = c;
    ++cursor; 
  }

  *cursor = '\0';

  return cstr;
}

// TODO factoriser fsize
size_t fsize(FILE* f)
{
  fseek(f, 0L, SEEK_END);
  unsigned size = ftell(f);
  fseek(f, 0L, SEEK_SET);  
  return size;
}