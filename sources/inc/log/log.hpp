#pragma once

#include "log/details/Logger.hpp"

//#define LOG_TRACE(msg) spdlog::get(Log::details::Logger::LoggerName)->trace(msg)
#ifdef NDEBUG
#define LOG_DEBUG(msg)
#else
#define LOG_DEBUG(msg, ...) Log::details::Logger::get().log(msg, __VA_ARGS__)
#endif
//#define LOG_DEBUG(msg) spdlog::get(Log::details::Logger::LoggerName)->debug(msg)

