//
// Created by Ludwig Andreas on 25.07.2023.
//

#ifndef S21_INCLUDE_LOGGER_LOGGERCONFIGURATOR_H_
#define S21_INCLUDE_LOGGER_LOGGERCONFIGURATOR_H_


#include "PatternLayout.h"

#include "logger/Logger.h"

namespace s21::diagnostic {

class LoggerConfigurator {

 public:
  static void configure(const PatternLayout &layout = PatternLayout());

};

}

#endif //S21_INCLUDE_LOGGER_LOGGERCONFIGURATOR_H_
