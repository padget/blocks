#include "vstring.h"

void vs_foreach(vstring vs, vs_foreach_fn fn)
{
  char* begin = vs.bstr;
  char* end   = vs.estr;
  
  while (begin != end)
  {
    fn(begin);
    begin++;
   }
}

vstring vs_default() 
{
  vstring vs;
  vs.bstr = NULL;
  vs.estr = NULL;
  return vs;
}

vstring vs_construct(char* begin, char* end)
{
  vstring vs;
  vs.bstr = begin;
  vs.estr = end; 
  return vs;
}

size_t vs_size(const vstring vs)
{
  return vs.estr - vs.bstr;
}

void cvs_foreach(cvstring vs, cvs_foreach_fn fn)
{
  const char* begin = vs.bstr; 
  const char* end = vs.estr;
  
  while (begin != end)
  {
    fn(begin);
    begin++;
  }
}

cvstring cvs_default()
{
  cvstring vs;
  vs.bstr = NULL;
  vs.estr = NULL;
  return vs;
}

cvstring cvs_construct(const char* begin, const char* end)
{
  cvstring vs;
  vs.bstr = begin; 
  vs.estr = end;
  return vs;
}

size_t cvs_size(const cvstring vs)
{
  return vs.estr - vs.bstr;
}

