#include "array.h"

size_t len(array a)
{
	return a.len;
}

bool empty(array a)
{
	return len(a) == 0;
}

iterator begin(array a)
{
	return a.begin;
}

iterator end(array a)
{
	return ((char*)a.begin)+(a.tsize*a.len);
}

iterator next(iterator i)
{
	return ((char*)i)+1;
}

