#include "command.h"
#include "macro.h"

/* *** Blocks token api *** */






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

command_error blocks_detect_commands(blocks_srange *source, commands *cs) {
  contract_notnull(source);
  contract_notnull(source->begin);
  contract_notnull(source->end);
  contract_notnull(cs);
  contract_notnull(cs->begin);
  contract_notnull(cs->end);

  char *cursor = source->begin;
  blocks_srange line;
  while (*cursor != '\0') {
    size_t index = 0;
    blocks_readline(source, &line);
    blocks_detect_command(&line, cs + index);
    ++index;
  }

  return COMMAND_NO_ERROR;
}
