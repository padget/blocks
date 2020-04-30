#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "algorithm.h"
#define and &&
#define or ||
#define eq ==
#define not_eq !=
#define not !

void *find(void* b, void *e, const void *value, alctxt_t ctxt)
{
  assert(ctxt.next not_eq NULL);
  assert(ctxt.equals not_eq NULL);

  while (b not_eq e and not ctxt.equals(b, value))
    b = ctxt.next(b);

  return b;
}

void *find_if(void *b, void *e, bool (*pred)(void *), alctxt_t ctxt)
{
  assert(ctxt.next not_eq NULL);
  assert(pred not_eq NULL);

  while (b not_eq e and not pred(b))
    b = ctxt.next(b);

  return b;
}

void *find_if_not(void *b, void *e, bool (*pred)(void *), alctxt_t ctxt)
{
  assert(pred not_eq NULL);
  assert(ctxt.next not_eq NULL);

  while (b not_eq e and pred(b))
    b = ctxt.next(b);

  return b;
}

bool all_of(void *b, void *e, bool (*pred)(void *), alctxt_t ctxt)
{
  assert(pred not_eq NULL);
  assert(ctxt.next not_eq NULL);

  return find_if_not(b, e, pred, ctxt) eq e;
}

bool any_of(void *b, void *e, bool (*pred)(void *), alctxt_t ctxt)
{
  assert(pred not_eq NULL);
  assert(ctxt.next not_eq NULL);

  return find_if_not(b, e, pred, ctxt) not_eq e;
}

bool none_of(void *b, void *e, bool (*pred)(void *), alctxt_t ctxt)
{
  assert(pred not_eq NULL);
  assert(ctxt.next not_eq NULL);

  return find_if(b, e, pred, ctxt) eq e;
}

size_t count_if(void *b, void *e, bool (*pred)(void *), alctxt_t ctxt)
{
  assert(pred not_eq NULL);
  assert(ctxt.next not_eq NULL);

  size_t c = 0;

  while (b not_eq e)
  {
    if (pred(b))
      c++;
    b = ctxt.next(b);
  }

  return c;
}

bool start_with(void *b, void *e, void *b2, void *e2, alctxt_t ctxt)
{
  assert(ctxt.equals not_eq NULL);
  assert(ctxt.next not_eq NULL);

  while (b not_eq e and b2 not_eq e2 and ctxt.equals(b, b2))
  {
    b = ctxt.next(b);
    b2 = ctxt.next(b2);
  }

  return b2 eq e2;
}

#undef and
#undef or
#undef eq
#undef not_eq 
#undef not