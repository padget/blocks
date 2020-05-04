#include "array.h"
#include "keyword.h"

array make_array(const void *b, const void *e, size_t tsize)
{
	return (array){
			.b = b,
			.e = e,
			.tsize = tsize};
}

iterator make_iterator(const void *item, size_t tsize)
{
	return (iterator){
			.item = item,
			.tsize = tsize};
}

size_t len(array a)
{
	char *b = a.b;
	char *e = a.e;
	return (e - b) / a.tsize;
}

bool empty(array a)
{
	return len(a) eq 0;
}

iterator begin(array a)
{
	return make_iterator(a.b, a.tsize);
}

iterator end(array a)
{
	return make_iterator(a.e, a.tsize);
}

iterator next(iterator i)
{
	const char *ptr = i.item;
	const char *nptr = ptr + i.tsize;
	return make_iterator(nptr, i.tsize);
}

size_t distance(iterator i1, iterator i2)
{
	const char* item1 = i1.item;
	const char* item2 = i2.item;
	size_t dist = (item2 - item1) / i1.tsize; 
	return dist;
}

bool same(iterator i1, iterator i2)
{
	return i1.item eq i2.item;
}

