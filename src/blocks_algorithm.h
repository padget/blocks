#ifndef __blocks_algorithm_h__
#define __blocks_algorithm_h__

typedef void (*each_line_function)(char *begin, char* end);

void blocks_foreach_line(char *buffer, each_line_function each);

#endif