#pragma once

#include <cstdio>

#ifdef NDEBUG
#define LGL_NDEBUG
#endif

namespace lgl {
namespace detail {
enum class LogLevel {
    Fatal,
    Error,
    Info,
    Warning,
    Debug,
};

void Log(LogLevel level, const char* const __restrict fmt, ...);
} // namespace detail
} // namespace lgl

#ifndef LGL_NDEBUG
#define LGL_USE_FORMAT_CHECK
#endif

#ifdef LGL_USE_FORMAT_CHECK
#ifdef _MSC_VER
// see https://devblogs.microsoft.com/cppblog/format-specifiers-checking/
#define LGL_CHECK_FMT(...)  (0 && ::snprintf(nullptr, 0, __VA_ARGS__))
// MSVC preprocessor quirk: This extra layer of indirection is needed to swallow the
// leading comma when __VA_ARGS__ is empty.
#define LGL_EXPAND(...) __VA_ARGS__
#else
#define LGL_CHECK_FMT(...) ((void)0)
#endif
#endif

#ifndef LGL_NDEBUG
#define LGL_LOGF(fmt, ...) \
    (LGL_CHECK_FMT(fmt, LGL_EXPAND(__VA_ARGS__)), lgl::detail::Log(lgl::detail::LogLevel::Fatal, fmt, __VA_ARGS__))
#define LGL_LOGE(fmt, ...) \
    (LGL_CHECK_FMT(fmt, LGL_EXPAND(__VA_ARGS__)), lgl::detail::Log(lgl::detail::LogLevel::Error, fmt, __VA_ARGS__))
#define LGL_LOGI(fmt, ...) \
    (LGL_CHECK_FMT(fmt, LGL_EXPAND(__VA_ARGS__)), lgl::detail::Log(lgl::detail::LogLevel::Info, fmt, __VA_ARGS__))
#define LGL_LOGW(fmt, ...) \
    (LGL_CHECK_FMT(fmt, LGL_EXPAND(__VA_ARGS__)), lgl::detail::Log(lgl::detail::LogLevel::Warning, fmt, __VA_ARGS__))
#define LGL_LOGD(fmt, ...) \
    (LGL_CHECK_FMT(fmt, LGL_EXPAND(__VA_ARGS__)), lgl::detail::Log(lgl::detail::LogLevel::Debug, fmt, __VA_ARGS__))
#else
#define LGL_LOGF(fmt, ...) ((void)0)
#define LGL_LOGE(fmt, ...) ((void)0)
#define LGL_LOGI(fmt, ...) ((void)0)
#define LGL_LOGW(fmt, ...) ((void)0)
#define LGL_LOGD(fmt, ...) ((void)0)
#endif