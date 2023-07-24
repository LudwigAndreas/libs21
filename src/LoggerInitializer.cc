//
// Created by Ludwig Andreas on 24.07.2023.
//

#include "logger/LoggerInitializer.h"

#include <ios>

namespace s21::diagnostic {

LoggerInitializer::LoggerInitializer() {
 time(&start_time_);
}

time_t LoggerInitializer::GetTime() {
  return GetInstance().start_time_;
}

LoggerInitializer &LoggerInitializer::GetInstance() {
  static LoggerInitializer init;
  return init;
}

}