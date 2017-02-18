#pragma once

#include "log/details/Logger.hpp"

//#define LOG_TRACE(msg) spdlog::get(Log::details::Logger::LoggerName)->trace(msg)
#ifdef NDEBUG
#define LOG_DEBUG(...)
#else
#define LOG_DEBUG(msg, ...) Amb::Log::details::Logger::get().log(msg, __VA_ARGS__)
#define LOG_DEBUG_RECT(rect) Amb::Log::details::Logger::get().log("x = %d, y = %d, w = %d, h = %d", rect.x, rect.y, rect.w, rect.h)
#endif
//#define LOG_DEBUG(msg) spdlog::get(Log::details::Logger::LoggerName)->debug(msg)

