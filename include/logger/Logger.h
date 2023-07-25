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

#include "logger/logger_macros.h"
#include "logger/LoggerInitializer.h"
#include "PatternLayout.h"

namespace s21::diagnostic {

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
  Logger(const String& name = "Log4S21",
         s21::diagnostic::LogLevel level = LogLevel::Trace,
         const s21::diagnostic::PatternLayout &
         layout = PatternLayout());

  ~Logger();

  const String &GetName() const;

  static Logger* getLogger(const String& name);

  static std::map<String, Logger*> GetLoggerRepo();

  static Logger* getRootLogger();

  void SetPatternLayout(const PatternLayout &pattern_layout);

  void AddOutputStream(ToStream &os, bool own, LogLevel level);

  void AddOutputStream(ToStream &os, bool own);

  void AddOutputStream(ToStream *os, bool own);

  void AddOutputStream(ToStream *os, bool own, LogLevel level);

  void ClearOutputStream();

  void Log(LogLevel level, String file, int line, String func, String message);

 private:
  static std::map<String, Logger*> logger_repo_;
  static Logger* root;
  LogLevel level_;
  String name_;
  PatternLayout pattern_layout_;
  std::vector<StreamInfo> output_streams_;
  std::mutex threading_protection_;
};
}

#endif //S21_SRC_LOGGER_H_
