//
// Created by Ludwig Andreas on 22.07.2023.
//

#ifndef S21_INCLUDE_LOGGER_PARSE_CONVERTERS_LOGGINGEVENT_H_
#define S21_INCLUDE_LOGGER_PARSE_CONVERTERS_LOGGINGEVENT_H_

#include <ctime>

#include "logger/logger_type.h"

namespace s21::parse {

class LoggingEvent {
 private:

  s21::diagnostic::LogLevel level_;

  String file_;

  int line_;

  String logger_name_;

  String message_;

  String method_;

  String short_file_name_;

  String thread_name_;

 public:

  LoggingEvent(s21::diagnostic::LogLevel level,
               String file,
               String func_name,
               int line,
               String logger_name,
               String message);

  LoggingEvent();

  const String GetThreadName() const;

  const String getClassName() const;

  const String &GetShortFileName() const;

  const String &GetMethodName() const;

  s21::diagnostic::LogLevel GetLevel() const;

  const String &GetFileName() const;

  int getLine() const;

  const String &getLoggerName() const;

  const String &getMessage() const;

  static int GetPid();

  static time_t GetStartTime();

  time_t GetTimeStamp() const;

};
}
#endif //S21_INCLUDE_LOGGER_PARSE_CONVERTERS_LOGGINGEVENT_H_
