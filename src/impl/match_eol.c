#include "../command.h"
#include "../macro.h"
#include "../srange.h"
#include <stdbool.h>

bool blocks_match_eol(blocks_srange *source, blocks_srange *range) {
  contract_notnull(source);
  contract_notnull(source->begin);
  contract_notnull(source->end);
  contract_notnull(range);

  blocks_bypass_blank(source);
  
  char *begin = source->begin;
  char *cursor = blocks_is_eol(*begin) ? begin + 1 : begin;
  
  if (begin != cursor) {
    range->begin = begin;
    range->end = cursor;
    source->begin = cursor;
    return true;
  }
  
  return false;
}