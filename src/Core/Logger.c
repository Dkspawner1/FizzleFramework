#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <Core/Logger.h>

#define COLOR_RESET   "\x1b[0m"
#define COLOR_TRACE   "\x1b[36m"
#define COLOR_DEBUG   "\x1b[34m"
#define COLOR_INFO    "\x1b[32m"
#define COLOR_WARN    "\x1b[33m"
#define COLOR_ERROR   "\x1b[31m"
#define COLOR_CRITICAL "\x1b[35m"

static Logger g_logger = {
    .level = LOG_DEBUG,
    .file = NULL,
    .use_colors = 1
};

static const char *Log_LevelToString(const LogLevel level) {
    switch (level) {
        case LOG_TRACE: return "TRACE";
        case LOG_DEBUG: return "DEBUG";
        case LOG_INFO: return "INFO ";
        case LOG_WARN: return "WARN ";
        case LOG_ERROR: return "ERROR";
        case LOG_CRITICAL: return "CRIT ";
        default: return "UNKNOWN";
    }
}

static const char *Log_LevelToColor(const LogLevel level) {
    if (!g_logger.use_colors) return "";

    switch (level) {
        case LOG_TRACE: return COLOR_TRACE;
        case LOG_DEBUG: return COLOR_DEBUG;
        case LOG_INFO: return COLOR_INFO;
        case LOG_WARN: return COLOR_WARN;
        case LOG_ERROR: return COLOR_ERROR;
        case LOG_CRITICAL: return COLOR_CRITICAL;
        default: return COLOR_RESET;
    }
}

static char *Log_GetBasename(const char *path) {
    const char *basename = path;
    for (size_t i = 0; path[i]; i++) {
        if (path[i] == '/' || path[i] == '\\') {
            basename = &path[i + 1];
        }
    }
    return (char *) basename;
}

void Logger_Initialize(const LogLevel level) {
    g_logger.level = level;
    g_logger.file = stdout;
    g_logger.use_colors = 1;
    setvbuf(stdout, NULL, _IONBF, 0);

    fprintf(stdout, "%s[Logger] Logger initialized with level: %s%s\n",
            Log_LevelToColor(LOG_INFO),
            Log_LevelToString(level),
            COLOR_RESET);
}

void Logger_Shutdown(void) {
    fprintf(stdout, "%s[Logger] Logger shutdown%s\n",
            Log_LevelToColor(LOG_INFO),
            COLOR_RESET);

    if (g_logger.file && g_logger.file != stdout && g_logger.file != stderr) {
        fclose(g_logger.file);
    }
    g_logger.file = NULL;
}

void Logger_Log(const LogLevel level, const char *category, const char *format, ...) {
    if (level < g_logger.level) return;
    if (!g_logger.file) g_logger.file = stdout;

    const time_t now = time(NULL);
    const struct tm *timeinfo = localtime(&now);
    char time_buffer[20];
    strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", timeinfo);

    const char *basename = Log_GetBasename(category);

    fprintf(g_logger.file, "%s%s %s [%s]%s ",
            Log_LevelToColor(level),
            time_buffer,
            Log_LevelToString(level),
            basename,
            COLOR_RESET);

    va_list args;
    va_start(args, format);
    vfprintf(g_logger.file, format, args);
    va_end(args);

    fprintf(g_logger.file, "\n");
    fflush(g_logger.file);
}
