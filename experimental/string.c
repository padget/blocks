
#include "string.h"
#include <string.h>

#define LET(name, type, value) type name = value;
#define RESULT(expr) return (expr);
#define IF(expr) if (expr)
#define BEGIN() {
#define END() }
#define EQUAL(l1, l2) (l1) == (l2)
#define NOTEQUALS(l1, l2) (l1) != (l2)
#define DEFAULT(name, type) type name;
#define ASSIGN(name, value) ((name) = (value));
#define MALLOC(target, type, size) ASSIGN(target, malloc(sizeof(type)*(size)))
#define STRCPY(source, target) strcpy((source), (target));
#define WHILE(expr) while (expr)
#define INCREMENT(expr) (expr)++;
#define FREE(expr) free(expr);

string s_default()
BEGIN()
  DEFAULT(s, string)
  ASSIGN(s.data, NULL)
  ASSIGN(s.size, 0)
  RESULT(s)
END()

string s_copy(const string str)
BEGIN()
  IF(EQUAL(s_size(str), 0))
  BEGIN()
    RESULT(s_default())
  END()
  LET(size , size_t, str.size)
  LET(begin, char* , str.data)
  LET(end  , char* , begin+size)
  RESULT(s_from_bounds(begin, end))
END()

string s_from_cstring(const char* cstr)
BEGIN()
  DEFAULT(s, string)
  LET(size, size_t, strlen(cstr))
  MALLOC(s.data, char, size+1)
  STRCPY(s.data, cstr)
  RESULT(s)
END()

string s_from_bounds(
  const char* b, 
  const char* e)
BEGIN()
  LET(size, size_t, e-b)
  IF(EQUAL(size, 0))
  BEGIN()
    RESULT(s_default())
  END()
  DEFAULT(s, string)
  MALLOC(s.data, char, size+1)
  ASSIGN(s.size, size)
  LET(bdata, char*, s.data)
  WHILE(NOTEQUALS(b, e))
  BEGIN()
    ASSIGN(*bdata, *b)
    INCREMENT(bdata)
    INCREMENT(b)
  END()
  ASSIGN(*bdata, '\0')
  RESULT(s)
END()

size_t s_size(const string s)
BEGIN()
  RESULT(s.size)
END()

void s_free(string s)
BEGIN()
  LET(size, size_t, s_size(s))
  IF(NOTEQUALS(size, 0))
  BEGIN()
    FREE(s.data)
  END()
END()

string s_from_file(FILE* f)
BEGIN()
  if (f == NULL)
    return s_default();
    
  fseek(f, 0L, SEEK_END);
  unsigned size = ftell(f);
  fseek(f, 0L, SEEK_SET);    

  DEFAULT(str, string)
  MALLOC(str.data, char, size+1)
  IF(EQUAL(s_size(str), 0))
  BEGIN()
    RESULT(str)
  END()
  LET(begin, char*, str.data)
  DEFAULT(c, int)
  WHILE((c=getc(f))!=EOF)
  BEGIN()
    ASSIGN(*begin, c)
    INCREMENT(begin)
  END()
  ASSIGN(*begin, '\0')
  RESULT(str)
END()

const char* cs_find(
  const char* cs, 
  const char* end, 
  char c)
{
  if (cs == NULL || end == NULL)
    return NULL;

  while (cs != end)
  {
    if (*cs == c)
      break;
    else 
      cs++;
  }

  return cs;
}
