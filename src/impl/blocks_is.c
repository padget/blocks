#include "../command.h"
#include <stdbool.h>


bool blocks_is_letter(char c) { return 'a' <= c && c <= 'z'; }
bool blocks_is_digit(char c) { return '0' <= c && c <= '9'; }
bool blocks_is_colon(char c) { return c == ':'; }
bool blocks_is_eol(char c) { return c == '\n'; }
bool blocks_is_space(char c) { return c == ' ' || c == '\t'; }
bool blocks_is_quote(char c) { return c == '\''; }
bool blocks_is_eos(char c) { return c == '\0'; }