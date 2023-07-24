//
// Created by Ludwig Andreas on 17.07.2023.
//

#ifndef S21_SRC_LOGGER_H_
#define S21_SRC_LOGGER_H_

#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "logger/logger-macros.h"
#include "logger/LoggerInitializer.h"
#include "PatternLayout.h"

#define WRITELOG(logObj, level, message) { \
  std::stringstream oss_;                  \
  oss_ << message;                         \
  logObj.Log(level, __FILE__, __LINE__, __FUNCTION__, oss_.str()); }

namespace s21::diagnostic {

// template accepts an IThreading successor
template<class ThreadingProtection>
class Logger {
 private:
  struct StreamInfo {
    ToStream &p_stream;
    bool owned;
    LogLevel level;

    StreamInfo(ToStream &p_stream, bool owned, LogLevel level) :
        p_stream(p_stream),
        owned(owned),
        level(level) {}
  };

 public:
  Logger(s21::diagnostic::LogLevel level,
         String name,
         const s21::diagnostic::PatternLayout &
         layout)
      : level_(level), name_(name), pattern_layout_(layout) {
    LoggerInitializer::GetInstance();
  }

  Logger(s21::diagnostic::LogLevel level, String name)
      : level_(level), name_(name) {
    pattern_layout_ = PatternLayout("%6p %-8.10t --- [%M] %-25.40F : %m%n");
    LoggerInitializer::GetInstance();
  }

  ~Logger() {
//    ClearOutputStream();
  };

  Logger(const Logger<ThreadingProtection> &other) = default;
  Logger<ThreadingProtection> &operator=(const Logger<ThreadingProtection> &other) noexcept = default;

  void AddOutputStream(ToStream &os, bool own, LogLevel level) {
    AddOutputStream(&os, own, level);
  }

  void AddOutputStream(ToStream &os, bool own) {
    AddOutputStream(os, own, level_);
  }

  void AddOutputStream(ToStream *os, bool own) {
    AddOutputStream(os, own, level_);
  }

  void AddOutputStream(ToStream *os, bool own, LogLevel level) {
    StreamInfo stream_info(*os, own, level);
    output_streams_.push_back(stream_info);
  }

  void ClearOutputStream() {
    for (auto iter = output_streams_.begin(); iter != output_streams_.end();
         iter = std::next(iter)) {
      if (iter->owned)
        delete iter->p_stream;
    }
  }

  void Log(LogLevel level, String file, int line, String func, String message) {

    String msg;
    pattern_layout_.format(msg,
                           {
                               level,
                               file,
                               func,
                               line,
                               name_,
                               message
                           }
    );
    threading_protection_.lock();
    for (auto iter = output_streams_.begin(); iter != output_streams_.end();
         iter = std::next(iter)) {
      if (level < iter->level) {
        continue;
      }
      ToStream *p_stream = &iter->p_stream;
      if (!msg.empty()) {
        (*p_stream) << msg;
        p_stream->flush();
      }
    }
    threading_protection_.unlock();
  }

 private:
  LogLevel level_;
  String name_;
  PatternLayout pattern_layout_;
  std::vector<StreamInfo> output_streams_;
  ThreadingProtection threading_protection_;
};
}

#endif //S21_SRC_LOGGER_H_
