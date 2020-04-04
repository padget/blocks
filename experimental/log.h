#ifndef __blocks_log_h__
#define __blocks_log_h__

#include <stdarg.h>
#include <stdbool.h>
#include "config.h"

#ifndef BLOCKS_LOG_DATE_FORMAT
#define BLOCKS_LOG_DATE_FORMAT "%d-%m-%Y %H:%M:%S"
#endif

typedef const char *llevel;

bool log_print(llevel lvl, const char *format, va_list args);
bool log_info(const char *format, ...);
bool log_debug(const char *format, ...);
bool log_warn(const char *format, ...);
bool log_error(const char *format, ...);
bool log_fatal(const char *format, ...);

#endif