#include "memory.h" 
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

void mem_init(memory* mem, unsigned size)
{
  if (mem == NULL)
    return;

  size = size < 10 ? 10 : size;
  mem->pointers = malloc(sizeof(void*)*size);
  
  if (mem->pointers == NULL)
  {
    if (errno == ENOMEM)
      perror("can't allocate memory for garbage collector");
    exit(EXIT_FAILURE);
  }

  mem->epointers = mem->pointers + size;
}


unsigned mem_capacity(memory* mem)
{
  return mem == NULL ? 0 : 
    mem->epointers - mem->pointers;
}


void mem_store(memory* mem, void* pointer)
{
  if (mem == NULL)
    return;

  void** begin = mem->pointers;
  void** end   = mem->epointers;
  
  // the loop are stop at first
  // pointer that is NULL or if
  // there is no NULL pointer
  while (begin != end)
  {
    if (*begin == NULL)
      break;
    begin++;
  }

  // If no NULL pointer was found
  // in the pointers buffer, it will
  // be increased by 20.
  if (begin == end)
  {
    unsigned capacity    = mem_capacity(mem);
    unsigned newcapacity = capacity + 20;
    
    void** tmp = realloc(mem->pointers, newcapacity);
    
    if (tmp == NULL)
    {
      if (errno == ENOMEM)
        perror("can't allocate memory for garbage collector");
      
      free(pointer);
      mem_freeall(mem);
      
      exit(EXIT_FAILURE);
    }  

    mem->pointers = tmp; 
    mem->epointers = tmp + newcapacity;
    begin = tmp + capacity;   
  }

  *begin = pointer;
}


void mem_free(memory* mem, void* pointer)
{
  // if memory doesn't exit
  // then the pointer is freed
  // and mem is returned
  if (mem == NULL)
  {
    free(pointer);
    return;
  }

  void** begin = mem->pointers;
  void** end   = mem->epointers;

  // the pointer is searched
  // and then freed clear from mem
  while (begin != end)
  {
    if (*begin == pointer)
    {
      *begin = NULL;
      free(pointer);
      break;
    }

    begin++;
  }
}


void mem_freeall(memory* mem)
{
  if (mem == NULL)
    return;

  void** begin = mem->pointers;
  void** end   = mem->epointers;
  
  // free each pointer in the 
  // pointers buffer of the mem;
  while (begin != end)
  {
    free(*begin);
    begin++;
  }
}


void mem_destroy(memory* mem)
{
  mem_freeall(mem);
  mem_free(NULL, mem->pointers);
  mem->pointers = NULL;
  mem->epointers = NULL;
}
