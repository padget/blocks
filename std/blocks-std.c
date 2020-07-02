#include "blocks-std.h"
#include "log.h"
#include "i18n.h"

char* freadall(const char *fname)
{
  char* content=NULL;

  FILE *file = NULL;

  if (fname == NULL)
  {
    log_error(blocks_log_empty_filename);
    goto finally;
  }

  file = fopen(fname, "r");

  if (file == NULL)
  {
    log_error(blocks_log_file_not_found, fname);
    goto finally;
  }

  size_t s = fsize(file);

  if (s == 0)
  {
    log_error(blocks_log_no_content_in_file, fname);
    goto finally;
  }

  size_t schar = sizeof(char);
  char *buf = malloc(s * schar + 1);

  if (buf == NULL)
  {
    log_error(blocks_log_memory_allocation);
    goto finally;
  }

  char *buft = buf;
  int c;
  size_t cnt = 0;

  while ((c = fgetc(file)) != EOF && cnt < s)
  {
    *buft = c;
    ++buft;
    ++cnt;
  }

  if (cnt < s)
    *buft = '\0';
content = buft;
  
finally:

  if (file != NULL)
    fclose(file);

  return content;
}

size_t __fsize(FILE *f)
{
  fseek(f, 0L, SEEK_END);
  unsigned size = ftell(f);
  fseek(f, 0L, SEEK_SET);
  return size;
}

size_t fsize(FILE *f)
{
  if (f == NULL)
  {
    log_error(blocks_log_file_null_pointer);
    return 0;
  }
  else
    return __fsize(f);
}