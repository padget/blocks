#ifndef __blocks_command_h__
#define __blocks_command_h__

#include "srange.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
  blocks_srange *begin;
  blocks_srange* end;
} arguments;

typedef struct {
  blocks_srange name;
  uint8_t depth;
  arguments args;
} command;

typedef struct {
  command *begin;
  command *end;
} commands;

typedef enum {
  COMMAND_NO_ERROR = 0,
  COMMAND_NAME_ERROR,
  COMMAND_ARGS_ERROR,
  COMMAND_TOO_MANY_ARGS_ERROR,
  COMMAND_COLON_ERROR,
} command_error;

bool blocks_is_letter(char c);
bool blocks_is_digit(char c);
bool blocks_is_colon(char c);
bool blocks_is_eol(char c);
bool blocks_is_space(char c);
bool blocks_is_quote(char c);
bool blocks_is_eos(char c);

bool blocks_match_number(blocks_srange *source, blocks_srange *range);
bool blocks_match_name(blocks_srange *source, blocks_srange *range);
bool blocks_match_eol(blocks_srange *source, blocks_srange *range);
bool blocks_match_colon(blocks_srange *source, blocks_srange *range);
bool blocks_match_string(blocks_srange *source, blocks_srange *range);
bool blocks_match_parameter(blocks_srange *source, blocks_srange *range);
bool blocks_match_arg(blocks_srange *source, blocks_srange *range);

command_error blocks_detect_command(blocks_srange *line, command *c);
command_error blocks_detect_commands(blocks_srange *source, commands *cs);

#endif