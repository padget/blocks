#include "blocks_algorithm.h"

#include <stdio.h>

void blocks_foreach_line(char *buffer, each_line_function online) {
  char *begin = buffer;
  char *end = begin;

  while (*end != '\0') {
    if (*end == '\n') {
      online(begin, end);
      end++;
      begin = end;
    } else
      end++;
  }

  if (end - begin > 1)
    online(begin, end);
}