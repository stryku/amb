#pragma once

#include "log/details/Logger.hpp"

//#define LOG_TRACE(msg) spdlog::get(Log::details::Logger::LoggerName)->trace(msg)
#define LOG_DEBUG(msg) Log::details::Logger::get().log(msg)
//#define LOG_DEBUG(msg) spdlog::get(Log::details::Logger::LoggerName)->debug(msg)

