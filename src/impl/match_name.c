#include "../command.h"
#include "../macro.h"
#include "../srange.h"
#include <stdbool.h>

bool blocks_match_name(blocks_srange *source, blocks_srange *range) {
  contract_notnull(source);
  contract_notnull(source->begin);
  contract_notnull(source->end);
  contract_notnull(range);

  blocks_bypass_blank(source);

  char *cursor = source->begin;

  while (blocks_is_letter(*cursor))
    ++cursor;

  if (source->begin != cursor) {
    range->begin = source->begin;
    range->end = cursor;
    source->begin = cursor;
    return true;
  }

  return false;
}