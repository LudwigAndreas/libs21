//
// Created by Ludwig Andreas on 24.07.2023.
//

#ifndef S21_INCLUDE_LOGGER_LOGGERINITIALIZER_H_
#define S21_INCLUDE_LOGGER_LOGGERINITIALIZER_H_

#include <ctime>
#include <unistd.h>
#include <sys/types.h>

namespace s21::diagnostic {
class LoggerInitializer {
 private:

  time_t start_time_;

  pid_t current_pid_;

 public:
  LoggerInitializer();

  ~LoggerInitializer() = default;

  static time_t GetTime();

  static pid_t GetPid();

  static LoggerInitializer &GetInstance();
};
}

#endif //S21_INCLUDE_LOGGER_LOGGERINITIALIZER_H_
