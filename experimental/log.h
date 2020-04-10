#ifndef __blocks_log_h__
#define __blocks_log_h__

#include <stdarg.h>

#include "config.h"


#define BLOCKS_LOG_LEVEL_DEBUG 0
#define BLOCKS_LOG_LEVEL_INFO 1
#define BLOCKS_LOG_LEVEL_WARN 2
#define BLOCKS_LOG_LEVEL_ERROR 3
#define BLOCKS_LOG_LEVEL_FATAL 4

#ifndef BLOCKS_LOG_LEVEL
#define BLOCKS_LOG_LEVEL 1
#endif

#ifndef BLOCKS_LOG_DATE_FORMAT
#define BLOCKS_LOG_DATE_FORMAT "%d-%m-%Y %H:%M:%S"
#endif

typedef const char *llevel;

void log_print(llevel lvl, const char *format, va_list args);
void log_info(const char *format, ...);
void log_debug(const char *format, ...);
void log_warn(const char *format, ...);
void log_error(const char *format, ...);
void log_fatal(const char *format, ...);

#endif