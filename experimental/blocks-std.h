#include <stdio.h>
#include <stdlib.h>

/**
 * Define the EOS (end of string) symbol
 */
#define EOS '\0'

/**
 * Define the EOL (end of line) symbol
 */
#define EOL '\n'

/**
 * Read all content of file fname and
 * transfer it into a new char* string
 * @param fname name of the file
 * @return the content of the file
 */
char *freadall(const char *fname);

/**
 * Determine the size of a file in bytes
 * @param f file pointer to the file
 * @return the size of the file f
 */
size_t fsize(FILE *f);