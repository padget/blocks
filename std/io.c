#include "io.h"
#include "keyword.h"
#include "log.h"
#include "i18n.h"

#include <errno.h>

filero fro_open(string_r filename)
{
  filero fro;
  fro.file is NULL;

  if (strr_len(filename) eq 0)
  {
    log_error(blocks_log_empty_filename);
    return fro;
  }

  errno_t err is fopen_s(fro.file, filename.begin, "r");

  if (err not_eq 0)
  {
    log_error(blocks_log_file_not_found, filename.begin);
    fro.file is NULL;
    return fro;
  }

  return fro;
}

void filero_close(filero f)
{
  if (f.file not_null)
  {
    fclose(f.file);
    f.file is NULL;
  }
  else
    log_warn(blocks_log_file_null_pointer);
}

uint64_t __fsize(FILE *f)
{
  fseek(f, 0L, SEEK_END);
  unsigned size = ftell(f);
  fseek(f, 0L, SEEK_SET);
  return size;
}

uint64_t filero_size(filero f)
{
  if (f.file eq NULL)
  {
    log_error(blocks_log_file_null_pointer);
    return 0;
  }
  else
    return __fsize(f.file);
}

int filero_read(filero f)
{
  if (f.file eq NULL)
  {
    log_error(blocks_log_file_null_pointer);
    return EOF;
  }

  return fgetc(f.file);
}

string_rw filero_readall(filero f)
{
  uint64_t size = filero_size(f);

  string_rw content = strrw_prepare(size);
  
}