#include "log.h"
#include <stdio.h>
#include <time.h>

#define log_print2(lvl, format, ...)

void log_print(llevel lvl, const char *format, va_list args)
{
    time_t now = time(NULL);
    char buf[50];
    strftime(buf, sizeof buf, BLOCKS_LOG_DATE_FORMAT, gmtime(&now));
    printf("[%s] [%s] ", lvl, buf);
    vprintf(format, args);
    printf("\n");
}

void log_debug(__attribute__((unused)) const char *format, ...)
{
#if BLOCKS_LOG_LEVEL <= 0
    va_list args;
    va_start(args, format);
    log_print("DEBUG", format, args);
    va_end(args);
#endif
}

void log_info(__attribute__((unused)) const char *format, ...)
{
#if BLOCKS_LOG_LEVEL <= 1
    va_list args;
    va_start(args, format);
    log_print("INFO", format, args);
    va_end(args);
#endif
}

void log_warn(__attribute__((unused)) const char *format, ...)
{
#if BLOCKS_LOG_LEVEL <= 2
    va_list args;
    va_start(args, format);
    log_print("WARN", format, args);
    va_end(args);
#endif
}

void log_error(__attribute__((unused)) const char *format, ...)
{
#if BLOCKS_LOG_LEVEL <= 3
    va_list args;
    va_start(args, format);
    log_print("ERROR", format, args);
    va_end(args);
#endif
}

void log_fatal(__attribute__((unused)) const char *format, ...)
{
#if BLOCKS_LOG_LEVEL <= 4
    va_list args;
    va_start(args, format);
    log_print("FATAL", format, args);
    va_end(args);
#endif
}
