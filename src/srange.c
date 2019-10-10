#include "srange.h"
#include "macro.h"

void blocks_slen(blocks_srange *range, size_t *len) {
  contract_notnull(range);
  contract_notnull(range->begin);
  contract_notnull(range->end);

  *len = range->end - range->begin;
}

void blocks_readline(blocks_srange *srange, blocks_srange *line) {
  contract_notnull(srange);
  contract_notnull(srange->begin);
  contract_notnull(srange->end);
  contract_notnull(line);

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
