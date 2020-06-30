#ifndef __blocks_algorithm_h__
#define __blocks_algorithm_h__

#include <stdbool.h>
#include <stdlib.h>

struct iterator
{
    void *item;
    struct iterator (*incr)(struct iterator i);
    struct iterator (*decr)(struct iterator i);
    bool (*equals)(struct iterator i, struct iterator i2);
};

typedef struct iterator iterator;


iterator iter_incr(iterator i);
iterator iter_decr(iterator i);
bool iter_equals(iterator i1, iterator i2);


iterator iter_new(
    void *item,
    iterator (*incr)(iterator i),
    iterator (*decr)(iterator i),
    bool (*equals)(iterator i, iterator i2));

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

gpred make_params_predicate(bool (*apply)(iterator, void *), void *param);
gpred make_simple_predicate(bool (*apply)(iterator));

iterator find_if(iterator b, iterator e, gpred pred);
iterator find_if_not(iterator b, iterator e, gpred pred);

bool all_of(iterator b, iterator e, gpred pred);
bool any_of(iterator b, iterator e, gpred pred);
bool none_of(iterator b, iterator e, gpred pred);

size_t count_if(iterator b, iterator e, gpred pred);

bool start_with(iterator b, iterator e, iterator b2, iterator e2);
bool end_with(iterator b, iterator e, iterator b2, iterator e2);
bool equals(iterator b, iterator e, iterator b2, iterator e2);

#endif