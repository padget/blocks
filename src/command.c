#include "command.h"
#include "macro.h"

bool blocks_is_letter(char c) { return 'a' <= c && c <= 'z'; }
bool blocks_is_digit(char c) { return '0' <= c && c <= '9'; }
bool blocks_is_colon(char c) { return c == ':'; }
bool blocks_is_eol(char c) { return c == '\n'; }
bool blocks_is_space(char c) { return c == ' ' || c == '\t'; }
bool blocks_is_quote(char c) { return c == '\''; }
bool blocks_is_eos(char c) { return c == '\0'; }

/* *** Blocks token api *** */

bool matched(char *begin, char *end) {
  notnull(begin);
  notnull(end);

  return begin != end;
}

void bypass_blank(blocks_srange *source) {
  notnull(source);

  while (blocks_is_space(*source->begin))
    ++(source->begin);
}

bool blocks_match_number(blocks_srange *source, blocks_srange *range) {
  notnull(source);
  notnull(range);

  bypass_blank(source);
  char *cursor = source->begin;
  while (blocks_is_digit(*cursor))
    ++cursor;
  if (matched(source->begin, cursor)) {
    range->begin = source->begin;
    range->end = cursor;
    source->begin = cursor;
    return true;
  }
  return false;
}

bool blocks_match_name(blocks_srange *source, blocks_srange *range) {
  notnull(source);
  notnull(range);

  bypass_blank(source);
  char *cursor = source->begin;
  while (blocks_is_letter(*cursor))
    ++cursor;
  if (matched(source->begin, cursor)) {
    range->begin = source->begin;
    range->end = cursor;
    source->begin = cursor;
    return true;
  }

  return false;
}

bool blocks_match_eol(blocks_srange *source, blocks_srange *range) {
  notnull(source);
  notnull(range);

  bypass_blank(source);
  char *begin = source->begin;
  char *cursor = blocks_is_eol(*begin) ? begin + 1 : begin;
  if (matched(begin, cursor)) {
    range->begin = begin;
    range->end = cursor;
    source->begin = cursor;
    return true;
  }
  return false;
}

bool blocks_match_colon(blocks_srange *source, blocks_srange *range) {
  notnull(source);
  notnull(range);

  bypass_blank(source);
  char *begin = source->begin;
  char *cursor = blocks_is_colon(*begin) ? begin + 1 : begin;
  if (matched(begin, cursor)) {
    range->begin = begin;
    range->end = cursor;
    source->begin = cursor;
    return true;
  }
  return false;
}

bool blocks_match_string(blocks_srange *source, blocks_srange *range) {
  notnull(source);
  notnull(range);

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

bool blocks_match_parameter(blocks_srange *source, blocks_srange *range) {
  return false;
}

bool blocks_match_arg(blocks_srange *source, blocks_srange *range) {
  notnull(source);
  notnull(range);
  notnull(source->begin);
  notnull(source->end);

  range->begin = source->begin;
  range->end = source->end;
  blocks_match_number(source, range) || blocks_match_name(source, range) ||
      blocks_match_parameter(source, range) ||
      blocks_match_string(source, range);

  char *begin = range->begin;
  while (begin != range->end)
    ++begin;

  return false;
}

command_error blocks_detect_command(blocks_srange *line, command *c) {
  notnull(c);
  notnull(c->args.begin);
  notnull(c->args.end);
  notnull(line);
  notnull(line->begin);
  notnull(line->end);

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
    bypass_blank(line);
    argcursor++;
  }
  return COMMAND_NO_ERROR;
}

command_error blocks_detect_commands(blocks_srange *source, commands *cs) {
  notnull(source);
  notnull(source->begin);
  notnull(source->end);
  notnull(cs);
  notnull(cs->cs);
  precond(cs->length == 0);
  precond(cs->limit > cs->length);

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
