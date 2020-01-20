#ifndef __experimental_memory_h__
#define __experimental_memory_h__ 

typedef struct memory 
{
  void** pointers;
  void** epointers;
} memory;


/**
 * Inittialize a memory with a pointers max
 * capacity up to <size> elements
 *
 * @param unsigned size maximal capacity
 * of void* array in the memory buffer.
 * 
 * @return memory the new initialized memory
 */
void mem_init(memory* meme, unsigned size);

/**
 * Returns the current capacity of 
 * the memory mem. If the memory
 * is null, then it returns 0. 
 *
 * @param memory* mem the memory 
 * whose the capacity is queried
 *
 * @return the capacity of mem
 */ 
unsigned mem_capacity(memory* mem);

/**
 * Store a new pointer in the memory
 * buffer. The size of the memory is 
 * incremented by one and maybe the 
 * max capacity of the memory could be
 * also upsize if needed.
 *
 * @param memory* mem memory buffer 
 * to store the pointer
 * @param void* pointer address
 * to store in mem
 * 
 * @return memory* mem with the new pointer
 */
void mem_store(memory* mem, void* pointer);
void mem_free(memory* mem, void* pointer);
void mem_freeall(memory* mem);
void mem_destroy(memory* mem);

#endif 
