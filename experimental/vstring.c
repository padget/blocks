#include "vstring.h"
#include <string.h>

vstring vstrbds ( char* begin, char* end )
{
  vstring s;
  s.view = begin;
  s.size = end - begin;
  return s;
}

vstring vstrlen ( char* begin, size_t size )
{
  return vstrbds ( begin, begin + size );
}

int vstrcmp ( vstring* s1, vstring* s2 ) 
{
  size_t s1len = vstrlen ( s1 );
  size_t s2len = vstrlen ( s2 );
  
  char* v1 = s1->view;
  char* v2 = s2->view;

  if ( s1len == s2len )
    return strncmp ( v1, v2, s1len );   
  else if ( s1len < s2len )
    return -1;
  else
    return 1;
}

size_t vstrlen ( vstring* s )
{
  return s->size;
}
