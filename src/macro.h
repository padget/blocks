#ifndef __blocks_macro_h__
#define __blocks_macro_h__

#include <assert.h>

#define precond(cond) assert((cond))
#define contract_notnull(ptr) precond((ptr != NULL))
#define contract_null(ptr) precond((ptr == NULL))
#define todo_process_error

#endif