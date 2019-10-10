#include "../command.h"
#include "../macro.h"
#include "../srange.h"
#include <stdbool.h>

bool blocks_match_parameter(blocks_srange *source, blocks_srange *range) {
  contract_notnull(source);
  contract_notnull(source->begin);
  contract_notnull(source->end);
  contract_notnull(range);
  contract_notnull(range->begin);
  contract_notnull(range->end);

  return false;
}
