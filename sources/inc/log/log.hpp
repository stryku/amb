#pragma once

#include "log/details/Logger.hpp"

//#define LOG_TRACE(msg) spdlog::get(Log::details::Logger::LoggerName)->trace(msg)
#ifdef NDEBUG
#define LOG_DEBUG(...)
#define LOG_DEBUG_RECT(...)
#else
#define LOG_DEBUG(msg, ...) Amb::Log::details::Logger::get().log(msg, __VA_ARGS__)
#define LOG_DEBUG_RECT(rect) Amb::Log::details::Logger::get().log("x = {}, y = {}, w = {}, h = {}", rect.x, rect.y, rect.w, rect.h)
#endif
//#define LOG_DEBUG(msg) spdlog::get(Log::details::Logger::LoggerName)->debug(msg)

