#include "vstring.h"
#include <string.h>

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

vstring vs_from_cstring(char* cstr)
{
  size_t cstrlen = strlen(cstr);
  vstring vs;
  vs.bstr = cstr;
  vs.estr = cstr+cstrlen;
  return vs;
}

size_t vs_size(const vstring vs)
{
  return vs.estr - vs.bstr;
}

bool vs_isequal(vstring v1, vstring v2)
{
  size_t sz1 = vs_size(v1);
  size_t sz2 = vs_size(v2);

  if (sz1 != sz2)
    return false;

  while(v1.bstr != v1.estr)
  {
    if (*v1.bstr != *v2.bstr)
      break;

    v1.bstr++;
    v2.bstr++;
  }

  return v1.bstr == v1.estr;
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

bool cvs_isequal(cvstring v1, cvstring v2)
{
  size_t sz1 = cvs_size(v1);
  size_t sz2 = cvs_size(v2);

  if (sz1 != sz2)
    return false;

  while(v1.bstr != v1.estr)
  {
    if (*v1.bstr != *v2.bstr)
      break;

    v1.bstr++;
    v2.bstr++;
  }

  return v1.bstr == v1.estr;
}


