//
// Created by Ludwig Andreas on 26.07.2023.
//

#ifndef S21_INCLUDE_LOGGER_LOGMANAGER_H_
#define S21_INCLUDE_LOGGER_LOGMANAGER_H_

#include <map>

#include "logger_type.h"

namespace s21::diagnostic {

class Logger;

typedef std::shared_ptr<Logger> LoggerPtr;

class LogManager {
 private:
  static std::map<String, LoggerPtr> logger_repo_;
  static std::shared_ptr<Logger> root;

  LogManager() = default;
//  not copyable or movable

 public:

  static LoggerPtr getLogger(const String& name);

  static std::map<String, LoggerPtr> GetLoggerRepo();

  static LoggerPtr getRootLogger();

};

}

#endif //S21_INCLUDE_LOGGER_LOGMANAGER_H_
