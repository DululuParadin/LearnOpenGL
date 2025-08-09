#include <cstdarg>
#include "mlog.h"

namespace lgl {
namespace detail {
void PutsColorByLevel(LogLevel level)
{
    switch (level) {
    case LogLevel::Fatal:
        printf("\033[0;31m");
        break;
    case LogLevel::Error:
        printf("\033[1;31m");
        break;
    case LogLevel::Warning:
        printf("\033[1;33m");
        break;
    case LogLevel::Info:
        printf("\033[0;33m");
        break;
    case LogLevel::Debug:
        printf("\033[0;32m");
        break;
    default:
        break;
    }
}

void PutsResetColor()
{
    puts("\033[0m");
}

void Log(LogLevel level, const char* const __restrict fmt, ...) {
    PutsColorByLevel(level);
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    PutsResetColor();
}
} // namespace detail
} // namespace lgl