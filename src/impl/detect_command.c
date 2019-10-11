#include "../command.h"
#include "../srange.h"
#include "../macro.h"

command_error blocks_detect_command(blocks_srange *line, command *c) {
  contract_notnull(c);
  contract_notnull(c->args.begin);
  contract_notnull(c->args.end);
  contract_notnull(line);
  contract_notnull(line->begin);
  contract_notnull(line->end);

  blocks_srange range;
  const size_t nb_args_max = c->args.end - c->args.begin;

  if (!blocks_match_name(line, &c->name))
    return COMMAND_NAME_ERROR;

  if (!blocks_match_colon(line, &range))
    return COMMAND_COLON_ERROR;

  blocks_srange *argcursor = c->args.begin;
  blocks_srange *end = c->args.end;
 
  while (argcursor <= end) {
    if (blocks_match_arg(line, &range))
      *argcursor = range;
   
    blocks_bypass_blank(line);
    argcursor++;
  }

  return COMMAND_NO_ERROR;
}