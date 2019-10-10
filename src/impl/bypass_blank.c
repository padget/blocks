#include "../command.h"
#include "../macro.h"
#include "../srange.h"

void blocks_bypass_blank(blocks_srange *source) {
  contract_notnull(source);

  while (blocks_is_space(*source->begin))
    ++(source->begin);
}