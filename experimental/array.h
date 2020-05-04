#ifndef __blocks_array_h__
#define __blocks_array_h__

#include <stdlib.h>
#include <stdbool.h>


struct iterator
{
	const void *item;
	size_t tsize;
};

typedef struct iterator iterator; 

iterator make_iterator(const void* item, size_t tsize);



iterator next(iterator i);

size_t distance(iterator i1, iterator i2);

bool same(iterator i1, iterator i2);



struct array
{
	const void *b;
	const void *e;
	const size_t tsize;
};

typedef struct array array;

array make_array(const void* b, const void *e, size_t tsize);



size_t len(array a);

bool empty(array a);

iterator begin(array a);

iterator end(array a);



#endif
