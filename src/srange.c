#include "srange.h"
#include "macro.h"

void blocks_slen(blocks_srange *range, size_t *len) {
  notnull(range);
  notnull(range->begin);
  notnull(range->end);

  *len = range->end - range->begin;
}

void blocks_readline(blocks_srange *srange, blocks_srange *line) {
  notnull(srange);
  notnull(srange->begin);
  notnull(srange->end);
  notnull(line);

  char *cursor = srange->begin;
  while (cursor != srange->end)
    if (*cursor != '\n')
      cursor++;
    else
      break;
  line->begin = srange->begin;
  line->end = cursor;
  srange->begin = cursor;
}
