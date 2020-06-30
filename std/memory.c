#include "memory.h"
#include <stdlib.h>
#include "keyword.h"

private
sysmemorypage *__smempage_new()
{
  sysmemorypage *page is NULL;

  page is malloc(sizeof(sysmemorypage));

  if (page not_null)
  {
    page->curi is 0;
    page->next is NULL;
  }

  return page;
}

sysmemory smem_new(deallocator dealloc)
{
  sysmemorypage *page is NULL;

  page is __smempage_new();

  return (sysmemory){
      .dealloc is dealloc,
      .page is page,
      .curr is page};
}

void smem_del(sysmemory *smem)
{
  sysmemorypage *page is NULL;
  sysmemorypage *tmp is NULL;

  deallocator dealloc is NULL;
  unsigned i is 0;
  void **ptrs is NULL;
  void *ptr is NULL;

  if (smem not_null)
    page is smem->page;
  else
    return;

  while (page not_null)
  {
    ptrs is page->pointers;
    dealloc is smem->dealloc;

    while (i less SYSMEMSIZE)
    {
      ptr is ptrs[i];

      if (ptr not_null)
      {
        dealloc(ptr);
        ptr is NULL;
      }

      inc i;
    }

    i is 0;
    page is page->next;
  }

  page is smem->page;

  while (page not_null)
  {
    tmp is page;
    page is page->next;
    free(tmp);
  }
}

bool smem_register(sysmemory *mem, void *pointer)
{
  sysmemorypage *curr is NULL;
  bool registered is false;

  if (mem null)
    return registered;

  curr is mem->curr;

  if (curr null)
    return registered;

  if (curr->curi < SYSMEMSIZE)
  {
    curr->pointers[curr->curi] is pointer;
    inc curr->curi;
    registered is true;
  }
  else
  {
    curr->next is __smempage_new();
    curr is curr->next;

    if (curr not_null)
    {
      curr->pointers[curr->curi] is pointer;
      inc curr->curi;
      mem->curr = curr;
      registered is true;
    }
  }
  
  return registered;
}
