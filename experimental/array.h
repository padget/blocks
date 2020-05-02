#ifndef __blocks_array_h__
# define __blocks_array_h__

#include <stdlib.h>
#include <stdbool.h>

struct array
{
	void * begin;
       	
	size_t tsize;	
	size_t len;
};

typedef struct array array;

typedef void *iterator;
typedef const void *const_iterator;

size_t len(array a);

bool empty(array a);

iterator begin(array a);

iterator end(array a);

iterator next(iterator i);

#endif
