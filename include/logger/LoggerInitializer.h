//
// Created by Ludwig Andreas on 24.07.2023.
//

#ifndef S21_INCLUDE_LOGGER_LOGGERINITIALIZER_H_
#define S21_INCLUDE_LOGGER_LOGGERINITIALIZER_H_

#include <ctime>

namespace s21::diagnostic {
class LoggerInitializer {
 private:

  time_t start_time_;

 public:
  LoggerInitializer();

  ~LoggerInitializer() = default;

  static time_t GetTime();

  static LoggerInitializer &GetInstance();
};
}

#endif //S21_INCLUDE_LOGGER_LOGGERINITIALIZER_H_
