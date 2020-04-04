#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../experimental/argument.h"
#include "../experimental/blocks-std.h"


unsigned countlines(char *src);


/**
 * Main function.
 * Print the number of 
 * lines inside the file.
 */ 
int main(int argc, char **argv)
{
  if (args_has_value(argc, argv, "--file"))
  {
    char* filename = args_value(argc, argv, "--file");
    char* src = freadall(filename);
    unsigned count = countlines(src);
    size_t fnamelen = strlen(filename);
    
    FILE* prepared = fopen();
    fprintf(stdout, "%u", count);
    return EXIT_SUCCESS;
  }
  else 
  {
    fprintf(stderr, "--file parameter not found\n");
    fprintf(stdout, "%d\n", -1);
    return EXIT_FAILURE;
  }
}


/**
 * Advance c until an eol is encountered 
 */
char *untileol(char *c)
{
  while (c != NULL && *c != EOL && *c != EOS)
    c++;
  return c;
}


/**
 * Returns true if there are only
 * blank characters between b and eol 
 */
bool isblankline(char *b, char *eol)
{
  while (b != eol)
    if (b != NULL && *b != ' ' && *b != '\t')
      b++;
    else
      break;
  return b == eol;
}


/**
 * Count the number of line in the 
 * string src. A line is ended by EOL
 */
unsigned countlines(char *src)
{
  unsigned nblines = 0;

  while (*src != EOS)
  {
    char *eol = untileol(src);
  
    if (isblankline(src, eol))
      nblines++;
  
    src = eol + 1;
  }

  return nblines;
}