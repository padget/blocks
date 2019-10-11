#include "../command.h"
#include "../macro.h"
#include "../srange.h"
#include <stdbool.h>

bool blocks_match_string(blocks_srange *source, blocks_srange *range) {
  contract_notnull(source);
  contract_notnull(source->begin);
  contract_notnull(source->end);
  contract_notnull(range);

  char *cursor = source->begin;

  if (blocks_is_quote(*cursor)) {
    ++cursor;
  
    while (!blocks_is_eos(*cursor) && !blocks_is_quote(*cursor))
      ++cursor;
  
    if (blocks_is_quote(*cursor)) {
      range->begin = source->begin;
      range->end = cursor;
      source->begin = cursor;
      return true;
    }
  }
  
  return false;
}