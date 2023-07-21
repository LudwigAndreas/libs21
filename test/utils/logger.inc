#ifndef GLOBAL_LOGGER
#define GLOBAL_LOGGER

#include "logger/Logger.h"
#include "logger/LoggerThreading.h"

inline s21::diagnostic::Logger<s21::threading::LoggerProcessLock>
    logger(s21::diagnostic::LogLevel::Trace, "GoogleTest");

#endif

