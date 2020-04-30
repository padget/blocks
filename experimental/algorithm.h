#ifndef __blocks_algorithm_h__
#define __blocks_algorithm_h__

#include <stdbool.h>
#include <stdlib.h>

struct algorithm_ctxt
{
    void *(*next)(void *);
    bool (*equals)(const void *, const void *);
};

typedef struct algorithm_ctxt alctxt_t;

void *find(void *b, void *e, const void *value, alctxt_t ctxt);
void *find_if(void *b, void *e, bool (*pred)(void*), alctxt_t ctxt);
void *find_if_not(void *b, void *e, bool (*pred)(void *), alctxt_t ctxt);
bool all_of(void *b, void *e, bool (*pred)(void *), alctxt_t ctxt);
bool any_of(void *b, void *e, bool (*pred)(void *), alctxt_t ctxt);
bool none_of(void *b, void *e, bool (*pred)(void *), alctxt_t ctxt);
size_t count_if(void *b, void *e, bool (*pred)(void *), alctxt_t ctxt);
bool start_with(void *b, void *e, void *b2, void *e2, alctxt_t ctxt);

#endif