#ifndef __blocks_srange_h__
#define __blocks_srange_h__

#include <stdlib.h>

typedef struct {
  char *begin;
  char *end;
} blocks_srange;

void blocks_slen(blocks_srange *range, size_t *len);
void blocks_readline(blocks_srange *srange, blocks_srange *line);

#endif