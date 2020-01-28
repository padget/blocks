#include "string.h"

string s_default()
{
  string s;
  s.bstr = NULL;
  s.estr = NULL;
  return s;
}

string s_construct_from_size(size_t s)
{
  if (s<=0)
    return s_default();
  
  size_t schar = sizeof(char);
  char* buffer = malloc(schar*s);

  if (buffer == NULL)
    return s_default();

  string str;
  str.bstr = buffer;
  str.estr = buffer+s;
  return str;
}

string s_copy(const string str)
{
  if (s_size(str)==0)
    return s_default();
    
  return s_copy_from_bounds(str.bstr, str.estr);
}

string s_copy_from_bounds(const char* b, const char* e)
{
  size_t size = e - b;
  
  string str = s_construct_from_size(size);
  
  if (s_size(str)!=size)
    return s_default();
  
  char* bstr = str.bstr;
  
  while (b!=e)
  {
    *bstr=*b;
    b++;
  }
  
  return str;
}

size_t s_size(const string s)
{
  return s.estr - s.bstr;
}

void s_free(string s)
{
  if (s_size(s)!=0)
    free(s.bstr);
}

string s_construct_from_file(FILE* f)
{
  if (f == NULL)
    return s_default();
    
  fseek(f, 0L, SEEK_END);
  unsigned size = ftell(f);
  fseek(f, 0L, SEEK_SET);    

  string str = s_construct_from_size(size);
  
  if (s_size(str)==0)
    return str;
  
  char* begin = str.bstr;
  int c;
  
  while ((c=getc(f))!=EOF)
  {
    *begin = c;
    begin++;
  }
  
  return str;
}
