#ifndef __blocks_std_memory_h__
#define __blocks_std_memory_h__

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "config.h"

#ifndef BLOCKS_SYSTEM_MEMORY_PAGE_SIZE
#define BLOCKS_SYSTEM_MEMORY_PAGE_SIZE 100
#endif

#define SYSMEMSIZE BLOCKS_SYSTEM_MEMORY_PAGE_SIZE

typedef void (*deallocator)(void *);

struct system_memory_page
{
  void *pointers[SYSMEMSIZE];
  uint64_t curi;
  struct system_memory_page *next;
};

struct system_memory
{
  struct system_memory_page* page;
  struct system_memory_page* curr;

  deallocator dealloc;
};

typedef struct system_memory sysmemory;
typedef struct system_memory_page sysmemorypage;

sysmemory smem_new(deallocator dealloc);
void smem_del(sysmemory *smem);
bool smem_register(sysmemory *mem, void *pointer);

#endif