#ifndef __blocks_algorithm_h__
#define __blocks_algorithm_h__

#include <stdbool.h>
#include <stdlib.h>
#include "array.h"

struct params_predicate
{
    void *params;
    bool (*apply)(iterator i, void *params);
};

typedef struct params_predicate params_predicate;

struct simple_predicate
{
    bool (*apply)(iterator i);
};

typedef struct simple_predicate simple_predicate;

struct generic_predicate
{
    union {
        params_predicate ppred;
        simple_predicate spred;
    };

    bool simple;
};

typedef struct generic_predicate generic_predicate;
typedef generic_predicate gpred;

gpred make_params_predicate(bool (*apply)(iterator, void *), void * param);
gpred make_simple_predicate(bool (*apply)(iterator));

struct iterator_value_equals
{
    bool (*apply)(iterator i, iterator value);
};

typedef struct iterator_value_equals iterator_value_equals;
typedef iterator_value_equals ivalue_equals;

ivalue_equals make_ivalue_equals(bool(*apply)(iterator, iterator));

iterator find_if(iterator b, iterator e, gpred pred);
iterator find_if_not(iterator b, iterator e, gpred pred);

bool all_of(iterator b, iterator e, gpred pred);
bool any_of(iterator b, iterator e, gpred pred);
bool none_of(iterator b, iterator e, gpred pred);

size_t count_if(iterator b, iterator e, gpred pred);

bool start_with(iterator b, iterator e, iterator b2, iterator e2, iterator_value_equals sequals);
bool equals(iterator b, iterator e, iterator b2, iterator e2, iterator_value_equals sequals);

#endif