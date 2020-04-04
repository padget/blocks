#include "log.h"
#include <stdio.h>
#include <time.h>

bool log_print(llevel lvl, const char *format, va_list args)
{
    time_t now = time(NULL);
    char buf[50];
    strftime(buf, sizeof buf, BLOCKS_LOG_DATE_FORMAT, gmtime(&now));
    printf("[%s] [%s] ", lvl, buf);
    vprintf(format, args);
    printf("\n");
    return true;
}

bool log_info(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    bool r = log_print("INFO", format, args);
    va_end(args);
    return r;
}

bool log_debug(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    bool r = log_print("DEBUG", format, args);
    va_end(args);
    return r;
}

bool log_warn(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    bool r = log_print("WARN", format, args);
    va_end(args);
    return r;
}

bool log_error(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    bool r = log_print("ERROR", format, args);
    va_end(args);
    return r;
}

bool log_fatal(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    bool r = log_print("FATAL", format, args);
    va_end(args);
    return r;
}
