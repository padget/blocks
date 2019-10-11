#include "../command.h"
#include "../macro.h"
#include "../srange.h"

command_error blocks_detect_commands(blocks_srange *source, commands *cs) {
  contract_notnull(source);
  contract_notnull(source->begin);
  contract_notnull(source->end);
  contract_notnull(cs);
  contract_notnull(cs->begin);
  contract_notnull(cs->end);

  char *cursor = source->begin;
  blocks_srange line;
  command* com = cs->begin;

  while (*cursor != '\0' && com <= cs->end) {
    blocks_readline(source, &line);
    blocks_detect_command(&line, com);
    com++;
  }

  return COMMAND_NO_ERROR;
}