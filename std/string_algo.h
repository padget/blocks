#ifndef __blocks_std_string_algo_h__
#define __blocks_std_string_algo_h__

#include <stdint.h>
#include "string.h"

/// //////////////// ///
/// STRING READ ONLY ///
/// //////////////// ///

strr_iterator strr_find(string_r strr, char c);
strr_iterator strr_find_if(string_r strr, char_predicate pred);
strr_iterator strr_find_if_not(string_r strr, char_predicate pred);

size_t strr_count(string_r strr, char c);
size_t strr_count_if(string_r strr, char_predicate pred);

bool strr_all_of(string_r strr, char_predicate pred);
bool strr_any_of(string_r strr, char_predicate pred);
bool strr_none_of(string_r strr, char_predicate pred);

bool strr_equals(string_r l, string_r r);
bool strr_start_with(string_r l, string_r r);
bool strr_end_with(string_r l, string_r r);
bool strr_in(string_r s, const char c);
bool strr_contains_only(string_r s, string_r onlys);

/// ///////////////// ///
/// STRING READ WRITE ///
/// ///////////////// ///

strrw_iterator strrw_find(string_rw strr, char c);
strrw_iterator strrw_find_if(string_rw strr, char_predicate pred);
strrw_iterator strrw_find_if_not(string_rw strr, char_predicate pred);

size_t strrw_count(string_rw strr, char c);
size_t strrw_count_if(string_rw strr, char_predicate pred);

bool strrw_all_of(string_rw strr, char_predicate pred);
bool strrw_any_of(string_rw strr, char_predicate pred);
bool strrw_none_of(string_rw strr, char_predicate pred);

bool strrw_equals(string_rw l, string_r r);
bool strrw_start_with(string_rw l, string_r r);
bool strrw_end_with(string_rw l, string_r r);
bool strrw_in(string_rw s, const char c);
bool strrw_contains_only(string_rw s, string_r onlys);

void strrw_replace(string_rw s, const char old, const char neo);
// TODO TO IMPLEMENT
void strrw_trim(string_rw s);

/// ///////////////// ///
/// STRING TO INTEGER ///
/// ///////////////// ///

struct uint8_result
{
  uint8_t value;
  bool valid;
};

typedef struct uint8_result uint8_r;

struct uint16_result
{
  uint16_t value;
  bool valid;
};

typedef struct uint16_result uint16_r;

struct uint32_result
{
  uint32_t value;
  bool valid;
};

typedef struct uint32_result uint32_r;

struct uint64_result
{
  uint64_t value;
  bool valid;
};

typedef struct uint64_result uint64_r;

uint8_r strr_to_u8(string_r strr);
uint16_r strr_to_u16(string_r strr);
uint32_r strr_to_u32(string_r strr);
uint64_r strr_to_u64(string_r strr);

#endif