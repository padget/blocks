#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "typearray.h"

/**
 * Define the EOS (end of string) symbol
 */
#define EOS '\0'

/**
 * Define the EOL (end of line) symbol
 */
#define EOL '\n'


typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;


typeref(short)
typeref(ushort)
typeref(char)
typeref(uchar)
typeref(int)
typeref(uint)
typeref(ulong)
typeref(ulonglong)


typearray(short)
typearray(ushort)
typearray(char)
typearray(uchar)
typearray(int)
typearray(uint)
typearray(ulong)
typearray(ulonglong)

/**
 * Read all content of file fname and
 * transfer it into a new char* string
 * 
 * @param fname name of the file
 * @return the content of the file or NULL
 * if the content could not be reached
 */
char *freadall(const char *fname);

/**
 * Determine the size of a file in bytes
 * @param f file pointer to the file
 * @return the size of the file f
 */
size_t fsize(FILE *f);

/**
 * Count the occurences of c inside
 * the string s
 * 
 * @param s the string to explore
 * @param c the character to find
 * @return the number of occurences
 * of c inside s. If s is NULL or empty
 * then returns 0.
 */
size_t strcount(const char *s, char c);

/**
 * Tell if s is an empty string or not
 * 
 * @param s string that can be empty
 * @return true if s is empty or NULL, 
 * else false
 */
bool strempty(const char *s);

/**
 * Process the hash value of a string 
 * (null-terminating string).
 * 
 * @param str string to hash
 * @return hash value of str
 */
size_t hash(const char *str);
