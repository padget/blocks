#include "file.h"
#include "macro.h"
#include <stdio.h>
#include <stdlib.h>

#define FILE_OPEN_ERROR "couldn't open the file"
#define BUFFER_ALLOCATION_ERROR "couldn't attribute memory space for buffer"
#define FILE_SEEK_ERROR "couldn't change file seek cursor"

void io_process_error(FILE *file, char *tmp, const char *message) {
  contract_notnull(message);

  if (errno != 0) {
    puts("an error occured");
    if (file != NULL)
      fclose(file);
    if (tmp != NULL)
      free(tmp);
    perror(message);
    exit(EXIT_FAILURE);
  }
}

void blocks_io_file_to_buffer(const char *filename, char **buffer) {
  contract_notnull(filename);
  contract_notnull(buffer);
  contract_null(*buffer);

  FILE *file = NULL;
  char *temp = NULL;

  // Open the file
  file = fopen(filename, "r");

  if (file == NULL)
    io_process_error(file, temp, FILE_OPEN_ERROR);

  // Process the buffer_size
  size_t buffer_size = 0;

  if (fseek(file, 0, SEEK_END) != 0)
    io_process_error(file, temp, FILE_SEEK_ERROR);

  buffer_size = ftell(file);

  if (fseek(file, 0, SEEK_SET) != 0)
    io_process_error(file, temp, FILE_SEEK_ERROR);

  // Create the buffer with buffer_size length
  temp = malloc(sizeof(char) * buffer_size + 1);

  if (temp == NULL)
    io_process_error(file, temp, BUFFER_ALLOCATION_ERROR);

  // Read all file into buffer
  int c;
  char *cursor = temp;

  while ((c = fgetc(file)) != EOF) {
    *cursor = (char)c;
    cursor += 1;
  }

  *cursor = '\0';

  // Return result;
  *buffer = temp;
}

#undef FILE_OPEN_ERROR 
#undef BUFFER_ALLOCATION_ERROR
#undef FILE_SEEK_ERROR

