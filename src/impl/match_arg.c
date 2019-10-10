#include "../command.h"
#include "../macro.h"
#include "../srange.h"
#include <stdbool.h>

bool blocks_match_arg(blocks_srange *source, blocks_srange *range) {
  contract_notnull(source);
  contract_notnull(source->begin);
  contract_notnull(source->end);
  contract_notnull(range);

  range->begin = source->begin;
  range->end = source->end;
  
  blocks_match_number(source, range) || 
  blocks_match_name(source, range) ||
  blocks_match_parameter(source, range) ||
  blocks_match_string(source, range);

  char *begin = range->begin;
  while (begin != range->end)
    ++begin;

  return false;
}