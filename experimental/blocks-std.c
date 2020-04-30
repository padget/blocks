#include "blocks-std.h"
#include "log.h"
#include "i18n.h"

typearrayimpl(short)
typearrayimpl(ushort)
typearrayimpl(char)
typearrayimpl(uchar)
typearrayimpl(int)
typearrayimpl(uint)
typearrayimpl(ulong)
typearrayimpl(ulonglong)

chararray freadall(const char *fname)
{
  chararray content;
  content.data = NULL;
  content.len = 0;
  FILE *file = NULL;

  if (fname == NULL)
  {
    log_error(blocks_log_null_filename);
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

  content.data = buf;
  content.len = s;
  
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

bool strempty(const char *s)
{
  return s == NULL || s[0] == '\0';
}

/**
 * Hash function from : 
 * https://stackoverflow.com/questions/29403343/
 * how-to-check-if-the-machine-running-on-is-32-or-64-bit-in-c 
 */
typedef __int32 uint32_t;
typedef __int64 uint64_t;

uint32_t __MurmurOAAT32(const char *key)
{
  uint32_t h = 3323198485ul;
  for (; *key; ++key)
  {
    h ^= *key;
    h *= 0x5bd1e995;
    h ^= h >> 15;
  }
  return h;
}

uint64_t __MurmurOAAT64(const char *key)
{
  uint64_t h = 525201411107845655ull;
  for (; *key; ++key)
  {
    h ^= *key;
    h *= 0x5bd1e9955bd1e995;
    h ^= h >> 47;
  }
  return h;
}

size_t hash(const char *str)
{
  if (str == NULL)
    return 0;
  else
#if __x86_64
    return __MurmurOAAT64(str);
#else
    return __MurmurOAAT32(str);
#endif
}
