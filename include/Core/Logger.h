#ifndef FIZZLEFRAMEWORK_LOGGER_H
#define FIZZLEFRAMEWORK_LOGGER_H

#include <stdio.h>

typedef enum {
    LOG_TRACE = 0,
    LOG_DEBUG = 1,
    LOG_INFO = 2,
    LOG_WARN = 3,
    LOG_ERROR = 4,
    LOG_CRITICAL = 5
} LogLevel;

typedef struct {
    LogLevel level;
    FILE *file;
    int use_colors;
} Logger;

void Logger_Initialize(LogLevel level);
void Logger_Shutdown(void);
void Logger_Log(LogLevel level, const char *category, const char *format, ...);

#define LOG_TRACE(fmt, ...)    Logger_Log(LOG_TRACE, __FILE__, fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...)    Logger_Log(LOG_DEBUG, __FILE__, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)     Logger_Log(LOG_INFO, __FILE__, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)     Logger_Log(LOG_WARN, __FILE__, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)    Logger_Log(LOG_ERROR, __FILE__, fmt, ##__VA_ARGS__)
#define LOG_CRITICAL(fmt, ...) Logger_Log(LOG_CRITICAL, __FILE__, fmt, ##__VA_ARGS__)

#endif //FIZZLEFRAMEWORK_LOGGER_H
